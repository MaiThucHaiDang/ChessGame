#pragma once
#include "Piece.h"

class Pawn : public Piece
{
public:
	Pawn();

	std::vector<std::pair<int, int>> getPseudoLegalMoves(const Board& board, int x, int y) const override;
};