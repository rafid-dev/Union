#include "uci.hpp"
#include "types.hpp"
#include "search.hpp"

#include <iostream>
#include <sstream>
#include <memory>

namespace UCI
{
    void SendId()
    {
        std::cout << "id name " << NAME << std::endl;
        std::cout << "id author " << AUTHOR << std::endl;
    }
    void Start(int argv, char **argc)
    {
        std::cout << "Union Chess Engine" << std::endl;

        Search::Limits limits;
        auto searchThread = std::make_unique<Search::SearchThread>(limits);

        if (argv > 1 && std::string{argc[1]} == "bench")
        {
            // info.depth = 13;
            // info.timeset = false;
            // StartBenchmark(*searchThread);
            exit(0);
        }

        std::string command;
        std::string token;

        while (std::getline(std::cin, command))
        {
            std::istringstream is(command);

            token.clear();
            is >> std::skipws >> token;

            if (token == "stop")
            {
            }
            else if (token == "quit")
            {

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
            }else if (token == "print"){
                std::cout << searchThread->board << std::endl;
            }
        }
    }
}