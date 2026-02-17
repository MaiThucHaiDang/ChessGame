#pragma once
#include <utility>
#include <vector>
#include <string>
#include "Common.h"

class Board;

class Piece
{
protected:
	Color color;
	PieceType type;
public:
	virtual char print() = 0; // test
	Piece(Color c, PieceType t);

	void setColor(Color c);

	Color getColor() const;
	PieceType getType() const;
	virtual std::vector<std::pair<int, int>> getPseudoLegalMoves(const Board& board, int x, int y) const = 0;
};