#pragma once
#include "Piece.h"

class Queen : public Piece
{
public:
	char print() override { return color == WHITE ? 'Q' : 'q'; }
	Queen();

	std::vector<std::pair<int, int>> getPseudoLegalMoves(const Board& board, int x, int y) const override;
};