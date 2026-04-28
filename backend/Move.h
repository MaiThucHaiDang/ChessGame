#pragma once
#include "Piece.h"

struct Move
{
	std::pair<int, int> firstPos;
	std::pair<int, int> secondPos;
	PieceType takenPiece;

	bool KCastleBefore;
	bool QCastleBefore;
	bool kCastleBefore;
	bool qCastleBefore;

	Color turnBefore;
	std::pair<int, int> enPassantTargetBefore;
	bool isPromotion;

	int halfMoveClockBefore;
	int fullMoveNumberBefore;

	Move(std::pair<int, int> firstPos, std::pair<int, int> secondPos, PieceType takenPiece,
		bool KCastleBefore, bool QCastleBefore, bool kCastleBefore, bool qCastleBefore,
		Color turnBefore, std::pair<int, int> enPassantTargetBefore, bool isPromotion,
		int halfMoveClockBefore, int fullMoveNumberBefore) :
		firstPos(firstPos), secondPos(secondPos), takenPiece(takenPiece),
		KCastleBefore(KCastleBefore), QCastleBefore(QCastleBefore), kCastleBefore(kCastleBefore), qCastleBefore(qCastleBefore), 
		turnBefore(turnBefore), enPassantTargetBefore(enPassantTargetBefore), isPromotion(isPromotion),
		halfMoveClockBefore(halfMoveClockBefore), fullMoveNumberBefore(fullMoveNumberBefore) {	}
};