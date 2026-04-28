#pragma once
#include "Piece.h"

class Bishop : public Piece
{
public:
	Bishop();

	std::vector<std::pair<int, int>> getPseudoLegalMoves(const Board& board, int x, int y) const override;
};