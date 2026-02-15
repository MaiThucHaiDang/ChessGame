#include "Bishop.h"
#include "Board.h"

Bishop::Bishop() : Piece(NONE, PieceType::BISHOP) {}

std::vector<std::pair<int, int>> Bishop::getPseudoLegalMoves(const Board& board, int x, int y) const
{
	std::vector<std::pair<int, int>> pseudoLegalMoves;
	for (int i = -1; i <= 1; i += 2)
		for (int j = -1; j <= 1; j += 2)
			for (int k = 1; std::min(x + k * i, y + k * j) >= 0 && std::max(x + k * i, y + k * j) < 8; k++)
				if (!board.getPieceAt(x + k * i, y + k * j))
					pseudoLegalMoves.push_back({ x + k * i, y + k * j });
				else
				{
					if (board.getPieceAt(x + k * i, y + k * j)->getColor() != color)
						pseudoLegalMoves.push_back({ x + k * i, y + k * j });
					break;
				}

	return pseudoLegalMoves;
}