#include "Board.h"
#include <sstream>
#include "PieceFactory.h"
#include <string>
#include "Utils.h"

constexpr auto START_FEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"; 
// Chữ thường là quân đen, chữ HOA là quân trắng, số là số ô không có quân liên tiếp
// w là lượt quân trắng, b là lượt quân đen
// Quyền nhập thành: Kk là nhập cánh vua, Qq là nhập cánh hậu, dùng - nếu không ai còn quyền nhập thành
// Mục tiêu En Passant: nếu có con tốt nào vừa đi 2 bước lên thì hiện vị trí mà quân còn lại có thể ăn vào, ví dụ e3, a6, dùng - nếu không có quân tốt nào vừa nhảy 2 bước
// Luật 50 nước hòa: biến đếm số nước đi kể từ lần cuối cùng một con tốt di chuyển hoặc 1 quân bị ăn, đủ 100 là hòa
// Đếm số lượt chơi: bắt đầu từ 1, sẽ tăng lên sau nước đi của quân Đen

Board::Board() : currentTurn(NONE), KCastle(0), QCastle(0), kCastle(0), qCastle(0), enPassantTarget({ -1, -1 }), halfMoveClock(0), fullMoveNumber(0)
{
	for (int i = 0; i < BOARD_SIZE; i++)
		for (int j = 0; j < BOARD_SIZE; j++)
			board[i][j] = nullptr;
}

Piece* Board::getPieceAt(int x, int y) const
{
	if (x < 0 || x > 7 || y < 0 || y > 7) 
		return nullptr;

	return board[x][y].get();
}
std::vector<std::pair<int, int>> Board::getPseudoLegalMoves(int x, int y) const { return board[x][y]->getPseudoLegalMoves(*this, x, y); }
Color Board::getCurrentTurn() const { return currentTurn; }
bool Board::getKCastle() const { return KCastle; }
bool Board::getQCastle() const { return QCastle; }
bool Board::getkCastle() const { return kCastle; }
bool Board::getqCastle() const { return qCastle; }
std::pair<int, int> Board::getEnPassantTarget() const { return enPassantTarget; }
int Board::getHalfMoveClock() const { return halfMoveClock; }
int Board::getFullMoveNumber() const { return fullMoveNumber; }

void Board::resetBoard()
{
	loadFEN(START_FEN);
}
void Board::loadFEN(const std::string& fen)
{
	std::stringstream ss(fen);
	std::string data;
	for (int x = 0; x < 7; x++)
	{
		std::getline(ss, data, '/');
		int y = 0;
		for (const auto piece : data)
			if (piece >= 'a' && piece <= 'z')
				(board[x][y++] = PieceFactory::createPiece(piece))->setColor(BLACK);
			else if (piece >= 'A' && piece <= 'Z')
				(board[x][y++] = PieceFactory::createPiece(tolower(piece)))->setColor(WHITE);
			else
				y += piece - '0';
	}
	std::getline(ss, data, ' ');
	int y = 0;
	for (const auto piece : data)
		if (piece >= 'a' && piece <= 'z')
			(board[7][y++] = PieceFactory::createPiece(piece))->setColor(BLACK);
		else if (piece >= 'A' && piece <= 'Z')
			(board[7][y++] = PieceFactory::createPiece(tolower(piece)))->setColor(WHITE);
		else
			y += piece - '0';

	std::getline(ss, data, ' ');
	if (data == "w")
		currentTurn = WHITE;
	else
		currentTurn = BLACK;

	std::getline(ss, data, ' ');
	KCastle = QCastle = kCastle = qCastle = 0;
	for (const auto c : data)
		switch (c)
		{
		case 'K':
			KCastle = 1;
			break;
		case 'Q':
			QCastle = 1;
			break;
		case 'k':
			kCastle = 1;
			break;
		case 'q':
			qCastle = 1;
			break;
		}

	std::getline(ss, data, ' ');
	if (data == "-")
		enPassantTarget = { -1,-1 };
	else
		enPassantTarget = Utils::stringToCoord(data);

	ss >> halfMoveClock >> fullMoveNumber;
}
void Board::makeMove(int x1, int y1, int x2, int y2, PieceType promoteTo = PieceType::QUEEN)
{
	board[x2][y2] = std::move(board[x1][y1]);
}