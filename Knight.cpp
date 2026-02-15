#include "Knight.h"
#include "Board.h"

Knight::Knight() : Piece(NONE, PieceType::KNIGHT) {}

std::vector<std::pair<int, int>> Knight::getPseudoLegalMoves(const Board& board, int x, int y) const
{
	std::vector<std::pair<int, int>> pseudoLegalMoves;
	for (int i = -2; i <= 2; i += 4)
		for (int j = -1; j <= 1; j += 2)
		{
			if (std::max(x + i, y + j) < 8 &&
				std::min(x + i, y + j) >= 0 &&
				(!board.getPieceAt(x + i, y + j) ||
					board.getPieceAt(x + i, y + j)->getColor() != color))
				pseudoLegalMoves.push_back({ x + i, y + j });
			if (std::max(x + j, y + i) < 8 &&
				std::min(x + j, y + i) >= 0 &&
				(!board.getPieceAt(x + j, y + i) ||
					board.getPieceAt(x + j, y + i)->getColor() != color))
				pseudoLegalMoves.push_back({ x + j, y + i });
		}

	return pseudoLegalMoves;
}