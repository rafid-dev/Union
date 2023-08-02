#include "search.hpp"
#include "evaluate.hpp"

using namespace chess;
using namespace Evaluation;

namespace Search
{
    void scoreMoves(const Board &board, Movelist &list, SearchStack *ss)
    {
        for (int i = 0; i < list.size(); i++)
        {
            Move &move = list[i];

            const Piece attacker = board.at(move.from());
            const Color pieceColor = board.color(attacker);
            const Piece victim = board.at(move.to());
            const bool capture = board.isCapture(move);

            if (capture)
            {
                move.setScore(CaptureScore + PieceValues[(int)victim] * 1000 - PieceValues[(int)attacker]);
            }
            
            if (move.move() == ss->killers[0].move()){
                move.setScore(Killer1Score);
            }
            else if (move.move() == ss->killers[1].move()){
                move.setScore(Killer2Score);
            }

        }
    }

    void pickNextMove(const int moveNum, Movelist &list)
    {
        Move temp = Move();
        int index = 0;
        int bestscore = 0;
        int bestnum = moveNum;

        for (index = moveNum; index < list.size(); ++index)
        {

            if (list[index].score() > bestscore)
            {
                bestscore = list[index].score();
                bestnum = index;
            }
        }

        temp = list[moveNum];
        list[moveNum] = list[bestnum]; // Sort the highest score move to highest.
        list[bestnum] = temp;
    }

    void SearchThread::iterativeDeepening()
    {

        init();

        Value score = VALUE_NONE;

        Time startingTime = startTime();
        tm.set_time(board.sideToMove());

        Move bestmove = Move();

        SearchStack stack[DEPTH_MAX + 10], *ss = stack + 7;


        for (Depth depth = 1; depth <= limits.depth; depth++)
        {
            if (limits.stopped || stopEarly())
            {
                break;
            }

            score = negamax<NodeType::PV>(-VALUE_INFINITE, VALUE_INFINITE, depth, ss);

            bestmove = pvTable.pvArray[0][0];

            uint64_t NPS = (uint64_t)(nodes_reached / ((misc::tick() - startingTime) / 1000.0));

            std::cout << "info depth " << depth << " score cp " << score << " time " << (misc::tick() - startingTime) << " nps " << NPS << " nodes " << nodes_reached << " pv ";

            for (int i = 0; i < pvTable.pvLength[0]; i++)
            {
                std::cout << uci::moveToUci(pvTable.pvArray[0][i]) << " ";
            }
            std::cout << std::endl;
        }

        std::cout << "bestmove " << uci::moveToUci(bestmove) << std::endl;
    }

    // Explicit Template Instantiation for SearchThread::negamax
    template Value SearchThread::negamax<NodeType::ROOT>(Value alpha, Value beta, Depth depth, SearchStack *ss);
    template Value SearchThread::negamax<NodeType::PV>(Value alpha, Value beta, Depth depth, SearchStack *ss);
    template Value SearchThread::negamax<NodeType::NON_PV>(Value alpha, Value beta, Depth depth, SearchStack *ss);

    // Explicit Template Instantiation for SearchThread::qsearch
    template Value SearchThread::qsearch<NodeType::NON_PV>(Value alpha, Value beta, SearchStack *ss);
    template Value SearchThread::qsearch<NodeType::PV>(Value alpha, Value beta, SearchStack *ss);

    template<NodeType NT>
    Value SearchThread::qsearch(Value alpha, Value beta, SearchStack *ss){

        if (!(nodes_reached & 1024))
        {
            checkTime();
        }

        if (board.isRepetition())
        {
            return 0;
        }

        Value eval = Evaluation::evaluate(board);

        if (ss->ply >= DEPTH_MAX){
            return eval;
        }

        if (eval >= beta){
            return eval;
        }

        if (eval > alpha){
            alpha = eval;
        }

        Value bestValue = eval;
        Value value = -VALUE_INFINITE;

        Movelist list;
        movegen::legalmoves<MoveGenType::CAPTURE>(list, board);

        scoreMoves(board, list, ss);

        for (int i = 0; i < list.size(); i++){

            pickNextMove(i, list);
            
            const Move& move = list[i];

            board.makeMove(move);
            nodes_reached++;
            (ss + 1)->ply = ss->ply + 1;
            ss->move = move;

            value = -qsearch<NT>(-beta, -alpha, ss + 1);

            board.unmakeMove(move);

            if (limits.stopped){
                return 0;
            }

            if (value > bestValue){
                bestValue = value;

                if (value > alpha){
                    alpha = value;

                    if (value >= beta){
                        return beta;
                    }
                }
            }
        }

        return bestValue;
    }

    template<NodeType NT>
    Value SearchThread::negamax(Value alpha, Value beta, Depth depth, SearchStack *ss)
    {
        if (limits.stopped)
        {
            return 0;
        }

        pvTable.pvLength[ss->ply] = ss->ply;

        if (depth <= 0)
        {
            // return qsearch<NT>(alpha, beta, ss);
            return Evaluation::evaluate(board);
        }

        if (!(nodes_reached & 1024))
        {
            checkTime();
        }

        constexpr bool isRoot = (NT == NodeType::ROOT);
        const bool inCheck = board.inCheck();

        Value bestValue = -VALUE_INFINITE;
        Value oldAlpha = alpha;
        Value value = -VALUE_INFINITE;
        Value eval = Evaluation::evaluate(board);

        if (!isRoot)
        {
            if (board.isRepetition())
            {
                return 0;
            }

            if (ss->ply >= DEPTH_MAX){
                return eval;
            }
        }

        // Null Move Pruning
        if (!isRoot && depth >= 3 && !inCheck && eval >= beta && hasNonPawnMaterials(board) && (ss - 1)->move.move() != Move::NULL_MOVE)
        {
            board.makeNullMove();
            nodes_reached++;
            ss->move = Move(Move::NULL_MOVE);

            (ss + 1)->ply = ss->ply + 1;

            const Depth R = 2 + depth / 4 + (eval - beta)/200;

            Value nullValue = -negamax<NodeType::NON_PV>(-beta, -beta + 1, depth - 1 - R, ss + 1);

            board.unmakeNullMove();

            if (limits.stopped)
            {
                return 0;
            }

            if (nullValue >= beta)
            {
                if (nullValue > VALUE_IS_MATE){
                    nullValue = beta;
                }
                
                return nullValue;
            }
        }


        Movelist list;
        movegen::legalmoves<MoveGenType::ALL>(list, board);
        scoreMoves(board, list, ss);

        Move bestmove = Move();
        int movesSearched = 0;

        for (int i = 0; i < list.size(); i++)
        {
            pickNextMove(i, list);

            const Move &move = list[i];
            const bool isQuiet = !board.isCapture(move) && move.typeOf() != Move::PROMOTION;

            board.makeMove(move);
            nodes_reached++;
            movesSearched++;
            ss->move = move;

            (ss + 1)->ply = ss->ply + 1;

            value = -negamax<NodeType::PV>(-beta, -alpha, depth - 1, ss + 1);

            board.unmakeMove(move);

            if (limits.stopped)
            {
                return 0;
            }

            if (value >= bestValue)
            {
                bestValue = value;

                if (value >= alpha)
                {
                    alpha = value;
                    bestmove = move;

                    pvTable.pvArray[ss->ply][ss->ply] = move;

                    for (int i = ss->ply + 1; i < pvTable.pvLength[ss->ply + 1]; i++)
                    {
                        pvTable.pvArray[ss->ply][i] = pvTable.pvArray[ss->ply + 1][i];
                    }

                    pvTable.pvLength[ss->ply] = pvTable.pvLength[ss->ply + 1];

                    if (value >= beta)
                    {
                        if (isQuiet){
                            ss->killers[1] = ss->killers[0];
                            ss->killers[0] = move;
                        }

                        break;
                    }
                }
            }
        }

        if (movesSearched == 0)
        {
            if (board.inCheck())
            {
                return -VALUE_IS_MATE + ss->ply;
            }
            else
            {
                return 0;
            }
        }

        return bestValue;
    }
} // namespace Search