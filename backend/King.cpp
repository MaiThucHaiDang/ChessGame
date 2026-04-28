#include "King.h"
#include "Board.h"

King::King() : Piece(NONE, PieceType::KING) {}

std::vector<std::pair<int, int>> King::getPseudoLegalMoves(const Board& board, int x, int y) const
{
	std::vector<std::pair<int, int>> pseudoLegalMoves;
	int dx[] = { 0,-1,-1,-1,0,1,1,1 };
	int dy[] = { 1,1,0,-1,-1,-1,0,1 };
	for (int i = 0; i < 8; i++)
		if (std::max(x + dx[i], y + dy[i]) < 8 &&
			std::min(x + dx[i], y + dy[i]) >= 0 &&
			(!board.getPieceAt(x + dx[i], y + dy[i]) || board.getPieceAt(x + dx[i], y + dy[i])->getColor() != color))
			pseudoLegalMoves.push_back({ x + dx[i], y + dy[i] });

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