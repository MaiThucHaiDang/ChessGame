#pragma once
#include "Piece.h"

class Queen : public Piece
{
public:
	Queen();

	std::vector<std::pair<int, int>> getPseudoLegalMoves(const Board& board, int x, int y) const override;
};