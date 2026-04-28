#include "Piece.h"

Piece::Piece(Color c, PieceType t) : color(c), type(t) {}

void Piece::setColor(Color c) { color = c; }
Color Piece::getColor() const { return color; }
PieceType Piece::getType() const { return type; }