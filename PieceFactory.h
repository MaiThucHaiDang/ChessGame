#pragma once
#include <memory>
#include "Piece.h"

class PieceFactory
{
public:
	static std::unique_ptr<Piece> createPiece(const char type);
	static std::unique_ptr<Piece> createPiece(const PieceType type);
};