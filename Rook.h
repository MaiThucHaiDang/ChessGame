#pragma once
#include "Piece.h"

class Rook : public Piece
{
public:
	char print() override { return color == WHITE ? 'R' : 'r'; }
	Rook();

	std::vector<std::pair<int, int>> getPseudoLegalMoves(const Board& board, int x, int y) const override;
};