#pragma once
#include "Piece.h"

class Rook : public Piece
{
public:
	Rook();

	std::vector<std::pair<int, int>> getPseudoLegalMoves(const Board& board, int x, int y) const override;
};