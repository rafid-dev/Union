#include "evaluate.hpp"

using namespace chess;
using namespace builtin;

namespace Evaluation
{

    Value BishopPairBonus = 30;

    Value evaluateMaterial(const Board &board)
    {
        Value material = 0;

        Color us = board.sideToMove();
        Color them = ~us;

        material += popcount(board.pieces(PieceType::PAWN, us)) * VALUE_PAWN;
        material += popcount(board.pieces(PieceType::KNIGHT, us)) * VALUE_KNIGHT;
        material += popcount(board.pieces(PieceType::BISHOP, us)) * VALUE_BISHOP;
        material += popcount(board.pieces(PieceType::ROOK, us)) * VALUE_ROOK;
        material += popcount(board.pieces(PieceType::QUEEN, us)) * VALUE_QUEEN;

        material -= popcount(board.pieces(PieceType::PAWN, them)) * VALUE_PAWN;
        material -= popcount(board.pieces(PieceType::KNIGHT, them)) * VALUE_KNIGHT;
        material -= popcount(board.pieces(PieceType::BISHOP, them)) * VALUE_BISHOP;
        material -= popcount(board.pieces(PieceType::ROOK, them)) * VALUE_ROOK;
        material -= popcount(board.pieces(PieceType::QUEEN, them)) * VALUE_QUEEN;

        return material;
    }

    Value evaluateMobilitySide(const Board &board, const Color side)
    {
        Value mobility = 0;

        Bitboard bishops = board.pieces(PieceType::BISHOP, side);
        Bitboard rooks = board.pieces(PieceType::ROOK, side);
        Bitboard queens = board.pieces(PieceType::QUEEN, side);

        while (bishops)
        {
            Square sq = poplsb(bishops);
            mobility += popcount(movegen::attacks::bishop(sq, board.occ())) * 2;
        }

        while (rooks)
        {
            Square sq = poplsb(rooks);
            mobility += popcount(movegen::attacks::rook(sq, board.occ())) * 3;
        }

        while (queens)
        {
            Square sq = poplsb(queens);
            mobility += popcount(movegen::attacks::queen(sq, board.occ())) * 4;
        }

        return mobility;
    }

    Value evaluateMobility(const Board &board)
    {
        Value mobility = 0;

        mobility += evaluateMobilitySide(board, Color::WHITE);
        mobility -= evaluateMobilitySide(board, Color::BLACK);

        return mobility;
    }

    Value evaluate(Board &board)
    {
        return evaluateMaterial(board) + evaluateMobility(board);
    }
} // namespace Evaluation