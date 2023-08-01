#pragma once

#include "types.hpp"
#include "misc.hpp"

namespace Search
{
    struct TimeMan
    {
        int movestogo = -1;

        Time wtime = TIME_UNSET;
        Time btime = TIME_UNSET;

        Time winc = 0;
        Time binc = 0;

        Time movetime = TIME_UNSET;

        Time start_time = 0;
        Time end_time = 0;
        Time stoptime_max = 0;
        Time stoptime_opt = 0;
        Time average_time = 0;

        void set_time(chess::Color side)
        {
            constexpr int safety_overhead = 50;
            Time uci_time = (side == chess::Color::WHITE ? wtime : btime);

            if (movestogo != TIME_UNSET)
            {

                uci_time -= safety_overhead;

                Time time_slot = average_time = uci_time / (double)movestogo;

                stoptime_max = time_slot;
                stoptime_opt = time_slot;
            }
            else if (movetime == TIME_UNSET)
            {
                Time inc = (side == chess::Color::WHITE ? winc : binc);
                uci_time -= safety_overhead;

                Time time_slot = average_time = uci_time / 20 + inc;
                Time basetime = (time_slot);

                Time optime = basetime * 0.6;

                Time maxtime = std::min<Time>(uci_time, basetime * 2);
                stoptime_max = maxtime;
                stoptime_opt = optime;
            }
            else if (movetime != TIME_UNSET)
            {
                movetime -= safety_overhead;
                stoptime_max = stoptime_opt = average_time = movetime;
            }
        }

        bool check_time() { return (misc::tick() > (start_time + stoptime_max)); }
        bool stop_search() { return (misc::tick() > (start_time + stoptime_opt)); }
    };
}