#pragma once
#include "Piece.h"

class Pawn : public Piece
{
public:
	char print() override { return color == WHITE ? 'P' : 'p'; }
	Pawn();

	std::vector<std::pair<int, int>> getPseudoLegalMoves(const Board& board, int x, int y) const override;
};