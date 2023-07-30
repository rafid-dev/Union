#include "types.hpp"

namespace Evaluation {
    constexpr std::array<Value, 6> PieceValues = {100, 320, 330, 500, 900, 0};
    
    constexpr Value VALUE_PAWN = 100;
    constexpr Value VALUE_KNIGHT = 320;
    constexpr Value VALUE_BISHOP = 330;
    constexpr Value VALUE_ROOK = 500;
    constexpr Value VALUE_QUEEN = 900;

    Value evaluate(chess::Board& board);
}