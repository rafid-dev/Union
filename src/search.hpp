#pragma once

#include "types.hpp"
#include "limits.hpp"
#include "timeman.hpp"

namespace Search
{

    struct SearchThread
    {
        chess::Board board;
        Search::Limits& limits;
        Search::TimeMan tm;

        uint64_t nodes_reached = 0;

        SearchThread(Limits& limits) : limits{limits} {}

        Time startTime();
        void checkTime();

        void applyFen(std::string fen);

        void makeMove(chess::Move& move);
        void makeMove(std::string& move);
        
        bool stopEarly();
    };

    inline void SearchThread::makeMove(chess::Move& move){
        board.makeMove(move);
    }

    inline void SearchThread::makeMove(std::string& moveStr){
        chess::Move move = chess::uci::uciToMove(board, moveStr);
        board.makeMove(move);
    }

    inline void SearchThread::applyFen(std::string fen){
        board.setFen(fen);
    }

    inline Time SearchThread::startTime(){
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

} // namespace Search