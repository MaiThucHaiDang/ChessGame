#include "Rook.h"
#include "Board.h"

Rook::Rook() : Piece(NONE, PieceType::ROOK) {}

std::vector<std::pair<int, int>> Rook::getPseudoLegalMoves(const Board& board, int x, int y) const
{
	std::vector<std::pair<int, int>> pseudoLegalMoves;
	for (int i = -1; i <= 1; i++)
		for (int k = 1; x + k * i >= 0 && x + k * i < 8; k++)
			if (!board.getPieceAt(x + k * i, y))
				pseudoLegalMoves.push_back({ x + k * i, y });
			else
			{
				if (board.getPieceAt(x + k * i, y)->getColor() != color)
					pseudoLegalMoves.push_back({ x + k * i, y });
				break;
			}
	for (int i = -1; i <= 1; i++)
		for (int k = 1; y + k * i >= 0 && y + k * i < 8; k++)
			if (!board.getPieceAt(x, y + k * i))
				pseudoLegalMoves.push_back({ x, y + k * i });
			else
			{
				if (board.getPieceAt(x, y + k * i)->getColor() != color)
					pseudoLegalMoves.push_back({ x, y + k * i });
				break;
			}

	return pseudoLegalMoves;
}