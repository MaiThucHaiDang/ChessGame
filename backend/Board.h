#pragma once
#include <memory>
#include <vector>
#include <utility>
#include <string>
#include "Piece.h"
#include "Common.h"
#include "Move.h"

constexpr size_t BOARD_SIZE = 8;

class Board
{
private:
	std::unique_ptr<Piece> board[BOARD_SIZE][BOARD_SIZE];
	Color currentTurn;

	bool KCastle;
	bool QCastle;
	bool kCastle;
	bool qCastle;

	std::pair<int, int> enPassantTarget;
	int halfMoveClock;
	int fullMoveNumber;

	std::pair<int, int> whiteKingPos;
	std::pair<int, int> blackKingPos;

	std::vector<Move> history;
	std::vector<std::string> fenHistory;
public:
	Board();

	Color getCurrentTurn() const;
	bool getKCastle() const;
	bool getQCastle() const;
	bool getkCastle() const;
	bool getqCastle() const;
	std::pair<int, int> getEnPassantTarget() const;
	int getHalfMoveClock() const;
	int getFullMoveNumber() const;
	Piece* getPieceAt(int x, int y) const;
	std::vector<std::pair<int, int>> getPseudoLegalMoves(int x, int y) const;
	std::vector<std::pair<int, int>> getLegalMoves(int x, int y);

	void resetBoard();
	void loadFEN(const std::string& fen);
	std::string makeFEN() const;
	std::string getFenBoardState(std::string fen) const;
	bool isThreefoldRepetition() const;
	bool isInsufficientMaterial() const;
	bool isInCheck() const;
	bool hasAnyLegalMoves();
	bool isStalemate();
	bool isCheckmate();
	void makeMove(int x1, int y1, int x2, int y2, PieceType promoteTo);
	void undoMove();
};