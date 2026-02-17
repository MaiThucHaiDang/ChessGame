#include "Queen.h"
#include "Board.h"

Queen::Queen() : Piece(NONE, PieceType::QUEEN) {}

std::vector<std::pair<int, int>> Queen::getPseudoLegalMoves(const Board& board, int x, int y) const
{
	std::vector<std::pair<int, int>> pseudoLegalMoves;
	int dx[] = { 0,-1,-1,-1,0,1,1,1 };
	int dy[] = { 1,1,0,-1,-1,-1,0,1 };
	for (int i = 0; i < 8; i++)
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