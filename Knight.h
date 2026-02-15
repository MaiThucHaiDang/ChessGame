#pragma once
#include "Piece.h"

class Knight : public Piece
{
public:
	char print() override { return color == WHITE ? 'N' : 'n'; }
	Knight();

	std::vector<std::pair<int, int>> getPseudoLegalMoves(const Board& board, int x, int y) const override;
};