#include "Knight.h"
#include "Board.h"

Knight::Knight() : Piece(NONE, PieceType::KNIGHT) {}

std::vector<std::pair<int, int>> Knight::getPseudoLegalMoves(const Board& board, int x, int y) const
{
	std::vector<std::pair<int, int>> pseudoLegalMoves;
	int dx[] = { -1, -2,-2,-1,1,2,2,1 };
	int dy[] = { 2,1,-1,-2,-2,-1,1,2 };
	for (int i = 0; i < 8; i++)
		if (std::max(x + dx[i], y + dy[i]) < 8 &&
			std::min(x + dx[i], y + dy[i]) >= 0 &&
			(!board.getPieceAt(x + dx[i], y + dy[i]) ||	board.getPieceAt(x + dx[i], y + dy[i])->getColor() != color))
			pseudoLegalMoves.push_back({ x + dx[i], y + dy[i] });

	return pseudoLegalMoves;
}