#pragma once

#include "types.hpp"
#include "limits.hpp"
#include "timeman.hpp"

namespace Search
{
    constexpr int CaptureScore = 9000000;
    constexpr int Killer1Score = 8000000;
    constexpr int Killer2Score = 7000000;

    enum class NodeType : uint8_t { ROOT, PV, NON_PV };

    struct PvTable {
        std::array<int, DEPTH_MAX> pvLength;
        chess::Move pvArray[DEPTH_MAX][DEPTH_MAX];
    };

    struct SearchStack {
        chess::Move move;
        chess::Move killers[2];
        Depth ply = 0;
    };

    struct SearchThread
    {
        chess::Board board;
        Limits& limits;
        TimeMan tm;

        uint64_t nodes_reached = 0;

        PvTable pvTable;

        SearchThread(Limits& limits) : limits{limits} {}

        Time startTime();
        void checkTime();

        void applyFen(std::string fen);

        void makeMove(chess::Move& move);
        void makeMove(std::string& move);
        
        bool stopEarly();

        void clear();
        void init();

        // Search functions //

        template<NodeType NT>
        Value negamax(Value alpha, Value beta, Depth depth, SearchStack *ss);

        template<NodeType NT>
        Value qsearch(Value alpha, Value beta, SearchStack *ss);

        void iterativeDeepening();
    };

    inline void SearchThread::makeMove(chess::Move &move)
    {
        board.makeMove(move);
    }

    inline void SearchThread::makeMove(std::string &moveStr)
    {
        chess::Move move = chess::uci::uciToMove(board, moveStr);
        board.makeMove(move);
    }

    inline void SearchThread::applyFen(std::string fen)
    {
        board.setFen(fen);
    }

    inline Time SearchThread::startTime()
    {
        return tm.start_time;
    }

    inline bool SearchThread::stopEarly()
    {
        if (limits.timeset && (tm.stop_search() || limits.stopped))
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    inline void SearchThread::checkTime()
    {
        if ((limits.timeset && tm.check_time()) || (limits.nodeset && nodes_reached >= limits.nodes))
        {
            limits.stopped = true;
        }
    }

    inline void SearchThread::clear(){
        nodes_reached = 0;
    }

    inline void SearchThread::init(){
        clear();
        tm.start_time = misc::tick();
    }
} // namespace Search