#pragma once
#include "Piece.h"

class Bishop : public Piece
{
public:
	char print() override { return color == WHITE ? 'B' : 'b'; }
	Bishop();

	std::vector<std::pair<int, int>> getPseudoLegalMoves(const Board& board, int x, int y) const override;
};