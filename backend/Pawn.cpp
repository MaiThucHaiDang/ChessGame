#include "Pawn.h"
#include "Board.h"

Pawn::Pawn() : Piece(NONE ,PieceType::PAWN) {}

std::vector<std::pair<int, int>> Pawn::getPseudoLegalMoves(const Board& board, int x, int y) const
{
	std::vector<std::pair<int, int>> pseudoLegalMoves;
	if (color == WHITE)
	{
		if (!board.getPieceAt(x - 1, y)) 
		{
			pseudoLegalMoves.push_back({ x - 1, y });
			if (x == 6 && !board.getPieceAt(4, y)) pseudoLegalMoves.push_back({ 4, y });
		}

		if (auto piece = board.getPieceAt(x - 1, y - 1))
			if (piece->getColor() == BLACK) pseudoLegalMoves.push_back({ x - 1, y - 1 });
		if (auto piece = board.getPieceAt(x - 1, y + 1))
			if (piece->getColor() == BLACK) pseudoLegalMoves.push_back({ x - 1, y + 1 });

		auto enPassant = board.getEnPassantTarget();
		if (enPassant.first == x - 1 && (enPassant.second == y - 1 || enPassant.second == y + 1))
			pseudoLegalMoves.push_back(enPassant);
	}
	else
	{
		if (!board.getPieceAt(x + 1, y))
		{
			pseudoLegalMoves.push_back({ x + 1, y });
			if (x == 1 && !board.getPieceAt(3, y)) pseudoLegalMoves.push_back({ 3, y });
		}

		if (auto piece = board.getPieceAt(x + 1, y - 1))
			if (piece->getColor() == WHITE) pseudoLegalMoves.push_back({ x + 1, y - 1 });
		if (auto piece = board.getPieceAt(x + 1, y + 1))
			if (piece->getColor() == WHITE) pseudoLegalMoves.push_back({ x + 1, y + 1 });

		auto enPassant = board.getEnPassantTarget();
		if (enPassant.first == x + 1 && (enPassant.second == y - 1 || enPassant.second == y + 1))
			pseudoLegalMoves.push_back(enPassant);
	}

	return pseudoLegalMoves;
}