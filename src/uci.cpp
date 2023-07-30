#include "uci.hpp"
#include "types.hpp"
#include "search.hpp"
#include "evaluate.hpp"

#include <iostream>
#include <sstream>
#include <memory>
#include <thread>

namespace UCI
{
    std::thread mainthread;

    void JoinThreads(){
        if (mainthread.joinable()){
            mainthread.join();
        }
    }

    void SendId()
    {
        std::cout << "id name " << NAME << std::endl;
        std::cout << "id author " << AUTHOR << std::endl;
        std::cout << "uciok" << std::endl;
    }

    void Start(int argv, char **argc)
    {
        std::cout << "Union Chess Engine" << std::endl;

        Search::Limits limits;
        auto searchThread = std::make_unique<Search::SearchThread>(limits);

        // if (argv > 1 && std::string{argc[1]} == "bench")
        // {
        //     info.depth = 13;
        //     info.timeset = false;
        //     StartBenchmark(*searchThread);
        //     exit(0);
        // }

        std::string command;
        std::string token;

        while (std::getline(std::cin, command))
        {
            std::istringstream is(command);

            token.clear();
            is >> std::skipws >> token;

            if (token == "stop")
            {
                limits.stopped = true;
                JoinThreads();
            }
            else if (token == "quit")
            {
                limits.stopped = true;
                JoinThreads();
                break;
            }
            else if (token == "isready")
            {
                std::cout << "readyok" << std::endl;
                continue;
            }
            else if (token == "ucinewgame")
            {
                continue;
            }
            else if (token == "uci")
            {
                SendId();
                continue;
            }

            /* Handle UCI position command */
            else if (token == "position")
            {
                std::string option;
                is >> std::skipws >> option;
                if (option == "startpos")
                {
                    searchThread->applyFen(chess::STARTPOS);
                }
                else if (option == "fen")
                {
                    std::string final_fen;
                    is >> std::skipws >> option;
                    final_fen = option;

                    // Record side to move
                    final_fen.push_back(' ');
                    is >> std::skipws >> option;
                    final_fen += option;

                    // Record castling
                    final_fen.push_back(' ');
                    is >> std::skipws >> option;
                    final_fen += option;

                    // record enpassant square
                    final_fen.push_back(' ');
                    is >> std::skipws >> option;
                    final_fen += option;

                    // record fifty move conter
                    final_fen.push_back(' ');
                    is >> std::skipws >> option;
                    final_fen += option;

                    final_fen.push_back(' ');
                    is >> std::skipws >> option;
                    final_fen += option;

                    // Finally, apply the fen.
                    searchThread->applyFen(final_fen);
                }
                is >> std::skipws >> option;
                if (option == "moves")
                {
                    std::string moveString;

                    while (is >> moveString)
                    {
                        searchThread->makeMove(moveString);
                    }
                }
                continue;
            }
            else if (token == "print")
            {
                std::cout << searchThread->board << std::endl;
                std::cout << "Evaluation: " << Evaluation::evaluate(searchThread->board) << std::endl;
            }
            else if (token == "go")
            {
                is >> std::skipws >> token;

                // Initialize variables
                int depth = -1;

                uint64_t nodes = -1;

                while (token != "none")
                {
                    if (token == "infinite")
                    {
                        depth = -1;
                        break;
                    }
                    if (token == "movestogo")
                    {
                        is >> std::skipws >> token;
                        searchThread->tm.movestogo = stoi(token);
                        is >> std::skipws >> token;
                        continue;
                    }

                    // Depth
                    if (token == "depth")
                    {
                        is >> std::skipws >> token;
                        depth = std::stoi(token);
                        is >> std::skipws >> token;
                        continue;
                    }

                    // Time
                    if (token == "wtime")
                    {
                        is >> std::skipws >> token;
                        searchThread->tm.wtime = std::stod(token);
                        is >> std::skipws >> token;
                        continue;
                    }
                    if (token == "btime")
                    {
                        is >> std::skipws >> token;
                        searchThread->tm.btime = std::stod(token);
                        is >> std::skipws >> token;
                        continue;
                    }

                    // Increment
                    if (token == "winc")
                    {
                        is >> std::skipws >> token;
                        searchThread->tm.winc = std::stod(token);
                        is >> std::skipws >> token;
                        continue;
                    }
                    if (token == "binc")
                    {
                        is >> std::skipws >> token;
                        searchThread->tm.binc = std::stod(token);
                        is >> std::skipws >> token;
                        continue;
                    }

                    if (token == "movetime")
                    {
                        is >> std::skipws >> token;
                        searchThread->tm.movetime = stod(token);
                        is >> std::skipws >> token;
                        continue;
                    }
                    if (token == "nodes")
                    {
                        is >> std::skipws >> token;
                        nodes = stoi(token);
                        is >> std::skipws >> token;
                    }
                    token = "none";
                }

                if (nodes != -1)
                {
                    limits.nodes = nodes;
                    limits.nodeset = true;
                }

                limits.depth = depth;

                if (searchThread->tm.wtime != -1 || searchThread->tm.btime != -1 || searchThread->tm.movetime != -1)
                {
                    limits.timeset = true;
                }

                if (depth == -1)
                {
                    limits.depth = DEPTH_MAX;
                }

                limits.stopped = false;

                searchThread->iterativeDeepening();
            }
        }
    }
}