#include "Bishop.h"
#include "Board.h"

Bishop::Bishop() : Piece(NONE, PieceType::BISHOP) {}

std::vector<std::pair<int, int>> Bishop::getPseudoLegalMoves(const Board& board, int x, int y) const
{
	std::vector<std::pair<int, int>> pseudoLegalMoves;
	int dx[] = { -1, -1, 1, 1 };
	int dy[] = { 1, -1, -1, 1 };
	for (int i = 0; i < 4; i++)
		for (int j = 1; std::max(x + j * dx[i], y + j * dy[i]) < 8 && std::min(x + j * dx[i], y + j * dy[i]) >= 0; j++)
			if (!board.getPieceAt(x + j * dx[i], y + j * dy[i]))
				pseudoLegalMoves.push_back({ x + j * dx[i], y + j * dy[i] });
			else
			{
				if (board.getPieceAt(x + j * dx[i], y + j * dy[i])->getColor() != color)
					pseudoLegalMoves.push_back({ x + j * dx[i], y + j * dy[i] });
				break;
			}

	return pseudoLegalMoves;
}