#include "types.hpp"

namespace Evaluation {
    
    constexpr Value VALUE_PAWN = 100;
    constexpr Value VALUE_KNIGHT = 320;
    constexpr Value VALUE_BISHOP = 330;
    constexpr Value VALUE_ROOK = 500;
    constexpr Value VALUE_QUEEN = 900;

    constexpr std::array<Value, 6> PieceValues = {VALUE_PAWN, VALUE_KNIGHT, VALUE_BISHOP, VALUE_ROOK, VALUE_QUEEN, 0};

    Value evaluate(chess::Board& board);
}