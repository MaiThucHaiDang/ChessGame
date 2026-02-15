#include "PieceFactory.h"
#include "Piece.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"

std::unique_ptr<Piece> PieceFactory::createPiece(const char type)
{
	switch (type)
	{
	case 'p': return std::make_unique<Pawn>();
	case 'r': return std::make_unique<Rook>();
	case 'n': return std::make_unique<Knight>();
	case 'b': return std::make_unique<Bishop>();
	case 'q': return std::make_unique<Queen>();
	case 'k': return std::make_unique<King>();
	default: return nullptr;
	}
}