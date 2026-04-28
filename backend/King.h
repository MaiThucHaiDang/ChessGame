#pragma once
#include "Piece.h"

class King : public Piece
{
public:
	King();

	std::vector<std::pair<int, int>> getPseudoLegalMoves(const Board& board, int x, int y) const override;
};