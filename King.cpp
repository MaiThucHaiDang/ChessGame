#include "King.h"
#include "Board.h"

King::King() : Piece(NONE, PieceType::KING) {}

std::vector<std::pair<int, int>> King::getPseudoLegalMoves(const Board& board, int x, int y) const
{
	std::vector<std::pair<int, int>> pseudoLegalMoves;
	for (int i = -1; i <= 1; i++)
		for (int j = -1; j <= 1; j++)
			if ((i || j) &&
				std::min(x + i, y + j) >= 0 &&
				std::max(x + i, y + j) < 8 &&
				(!board.getPieceAt(x + i, y + j) ||
				board.getPieceAt(x + i, y + j)->getColor() != color))
				pseudoLegalMoves.push_back({ x + i, y + j });
	if (color == WHITE)
	{
		if (board.getKCastle() && !board.getPieceAt(7, 5) && !board.getPieceAt(7, 6))
			pseudoLegalMoves.push_back({ 7, 6 });
		if (board.getQCastle() && !board.getPieceAt(7, 3) && !board.getPieceAt(7, 2) && !board.getPieceAt(7, 1))
			pseudoLegalMoves.push_back({ 7, 2 });
	}
	else
	{
		if (board.getkCastle() && !board.getPieceAt(0, 5) && !board.getPieceAt(0, 6))
			pseudoLegalMoves.push_back({ 0, 6 });
		if (board.getqCastle() && !board.getPieceAt(0, 3) && !board.getPieceAt(0, 2) && !board.getPieceAt(0, 1))
			pseudoLegalMoves.push_back({ 0, 2 });
	}

	return pseudoLegalMoves;
}