#include "Board.h"
#include <sstream>
#include "PieceFactory.h"
#include <string>
#include "Utils.h"
#include "Pawn.h"
#include "Rook.h"
#include "King.h"

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

Color Board::getCurrentTurn() const { return currentTurn; }
bool Board::getKCastle() const { return KCastle; }
bool Board::getQCastle() const { return QCastle; }
bool Board::getkCastle() const { return kCastle; }
bool Board::getqCastle() const { return qCastle; }
std::pair<int, int> Board::getEnPassantTarget() const { return enPassantTarget; }
int Board::getHalfMoveClock() const { return halfMoveClock; }
int Board::getFullMoveNumber() const { return fullMoveNumber; }
Piece* Board::getPieceAt(int x, int y) const
{
	if (x < 0 || x > 7 || y < 0 || y > 7)
		return nullptr;

	return board[x][y].get();
}
std::vector<std::pair<int, int>> Board::getPseudoLegalMoves(int x, int y) const { return board[x][y]->getPseudoLegalMoves(*this, x, y); }
std::vector<std::pair<int, int>> Board::getLegalMoves(int x, int y)
{
	std::pair<int, int>& kingPos = board[x][y]->getColor() == WHITE ? whiteKingPos : blackKingPos;
	bool isKing = board[x][y]->getType() == PieceType::KING;
	bool isKingInCheck = isInCheck();
	std::vector<std::pair<int, int>> legalMoves;
	auto pseudoLegalMoves = getPseudoLegalMoves(x, y);
	auto currentPiece = std::move(board[x][y]);
	std::unique_ptr<Piece> targetPiece = nullptr;
	for (const auto& coord : pseudoLegalMoves)
	{
		if (isKing)
		{
			if (abs(y - coord.second) == 2 && (isKingInCheck || std::find(legalMoves.begin(), legalMoves.end(), std::make_pair(x, (y + coord.second) / 2)) == legalMoves.end()))
				continue;
			kingPos = { coord.first, coord.second };
		}
		targetPiece = std::move(board[coord.first][coord.second]);
		board[coord.first][coord.second] = std::move(currentPiece);
		if (!isInCheck())
			legalMoves.push_back(coord);

		currentPiece = std::move(board[coord.first][coord.second]);
		board[coord.first][coord.second] = std::move(targetPiece);
	}
	board[x][y] = std::move(currentPiece);
	if (isKing)
		kingPos = { x, y };

	return legalMoves;
}

void Board::resetBoard()
{
	loadFEN(START_FEN);
}
void Board::loadFEN(const std::string& fen)
{
	fenHistory.clear();
	fenHistory.push_back(fen);
	std::stringstream ss(fen);
	std::string data;
	for (int x = 0; x < 7; x++)
	{
		std::getline(ss, data, '/');
		int y = 0;
		for (const auto piece : data)
			if (piece >= 'a' && piece <= 'z')
			{
				if (piece == 'k')
					blackKingPos = { x, y };
				(board[x][y++] = PieceFactory::createPiece(piece))->setColor(BLACK);
			}
			else if (piece >= 'A' && piece <= 'Z')
			{
				if (piece == 'K')
					whiteKingPos = { x, y };
				(board[x][y++] = PieceFactory::createPiece(tolower(piece)))->setColor(WHITE);
			}
			else
			{
				for (int i = 0; i < piece - '0'; ++i)
					board[x][y + i] = nullptr;
				y += piece - '0';
			}
	}
	std::getline(ss, data, ' ');
	int y = 0;
	for (const auto piece : data)
		if (piece >= 'a' && piece <= 'z')
		{
			if (piece == 'k')
				blackKingPos = { 7, y };
			(board[7][y++] = PieceFactory::createPiece(piece))->setColor(BLACK);
		}
		else if (piece >= 'A' && piece <= 'Z')
		{
			if (piece == 'K')
				whiteKingPos = { 7, y };
			(board[7][y++] = PieceFactory::createPiece(tolower(piece)))->setColor(WHITE);
		}
		else
		{
			for (int i = 0; i < piece - '0'; ++i)
				board[7][y + i] = nullptr;
			y += piece - '0';
		}

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
std::string Board::makeFEN() const
{
	std::string fen;
	for (int i = 0; i < 8; i++)
	{
		int count = 0;
		for (int j = 0; j < 8; j++)
			if (!board[i][j])
				count++;
			else
			{
				if (count)
				{
					fen += std::to_string(count);
					count = 0;
				}

				switch (board[i][j]->getType())
				{
				case PieceType::PAWN:
					if (board[i][j]->getColor() == WHITE)
						fen += "P";
					else
						fen += "p";
					break;
				case PieceType::ROOK:
					if (board[i][j]->getColor() == WHITE)
						fen += "R";
					else
						fen += "r";
					break;
				case PieceType::KNIGHT:
					if (board[i][j]->getColor() == WHITE)
						fen += "N";
					else
						fen += "n";
					break;
				case PieceType::BISHOP:
					if (board[i][j]->getColor() == WHITE)
						fen += "B";
					else
						fen += "b";
					break;
				case PieceType::QUEEN:
					if (board[i][j]->getColor() == WHITE)
						fen += "Q";
					else
						fen += "q";
					break;
				case PieceType::KING:
					if (board[i][j]->getColor() == WHITE)
						fen += "K";
					else
						fen += "k";
					break;
				}
			}

		if (count)
			fen += std::to_string(count);
		if (i != 7)
			fen += "/";
	}

	if (currentTurn == WHITE)
		fen += " w ";
	else
		fen += " b ";
	if (!KCastle && !QCastle && !kCastle && !qCastle)
		fen += "-";
	else
	{
		if (KCastle)
			fen += "K";
		if (QCastle)
			fen += "Q";
		if (kCastle)
			fen += "k";
		if (qCastle)
			fen += "q";
	}

	if (enPassantTarget == std::make_pair(-1, -1))
		fen += " - ";
	else
		fen += " " + Utils::coordToString(enPassantTarget) + " ";

	return fen + std::to_string(halfMoveClock) + " " + std::to_string(fullMoveNumber);
}
std::string Board::getFenBoardState(std::string fen) const
{
	return fen.substr(0, fen.rfind(' ', fen.rfind(' ') - 1));
}
bool Board::isThreefoldRepetition() const
{
	auto currentFenBoardState = getFenBoardState(fenHistory.back());
	int count = 0;
	for (auto it = fenHistory.rbegin(); it != fenHistory.rend(); ++it)
		if (currentFenBoardState == getFenBoardState(*it) && ++count == 3)
			return 1;

	return 0;
}
bool Board::isInsufficientMaterial() const
{
	bool hasMinorPieces = 0;
	for (int x = 0; x < 8; x++)
		for (int y = 0; y < 8; y++)
		{
			if (!board[x][y])
				continue;

			switch (board[x][y]->getType())
			{
			case PieceType::PAWN:
			case PieceType::ROOK:
			case PieceType::QUEEN:
				return 0;
			case PieceType::KNIGHT:
			case PieceType::BISHOP:
				if (!hasMinorPieces)
					hasMinorPieces = 1;
				else
					return 0;
			}
		}

	return 1;
}
bool Board::isInCheck() const
{
	std::pair<int, int> kingPos;
	if (currentTurn == WHITE)
		kingPos = whiteKingPos;
	else
		kingPos = blackKingPos;

	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			if (board[i][j] && board[i][j]->getColor() != currentTurn)
			{
				for (const auto& coord : getPseudoLegalMoves(i, j))
					if (coord == kingPos)
						return 1;
			}

	return 0;
}
bool Board::hasAnyLegalMoves()
{
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			if (board[i][j] && board[i][j]->getColor() == currentTurn && !getLegalMoves(i, j).empty())
				return 1;

	return 0;
}
bool Board::isStalemate()
{
	if (!hasAnyLegalMoves() && !isInCheck())
		return 1;

	return 0;
}
bool Board::isCheckmate()
{
	if (!hasAnyLegalMoves() && isInCheck())
		return 1;

	return 0;
}
void Board::makeMove(int x1, int y1, int x2, int y2, PieceType promoteTo = PieceType::QUEEN)
{
	bool isPromotion = board[x1][y1]->getType() == PieceType::PAWN && (x2 == 0 || x2 == 7);
	history.push_back(Move({ x1, y1 }, { x2, y2 }, board[x2][y2] ? board[x2][y2]->getType() : PieceType::EMPTY, KCastle, QCastle, kCastle, qCastle, currentTurn, enPassantTarget, isPromotion, halfMoveClock, fullMoveNumber));

	if (!board[x2][y2] && board[x1][y1]->getType() != PieceType::PAWN)
		halfMoveClock++;
	else
		halfMoveClock = 0;

	board[x2][y2] = std::move(board[x1][y1]);

	switch (board[x2][y2]->getType())
	{
	case PieceType::KING:
		if (y1 == 4)
		{
			if (currentTurn == WHITE)
			{
				if (x1 == 7)
					KCastle = QCastle = 0;
			}
			else
			{
				if (x1 == 0)
					kCastle = qCastle = 0;
			}

			if (y2 == 6)
				board[x1][5] = std::move(board[x1][7]);
			else if (y2 == 2)
				board[x1][3] = std::move(board[x1][0]);
		}

		if (currentTurn == WHITE)
			whiteKingPos = { x2, y2 };
		else
			blackKingPos = { x2, y2 };

		break;
	case PieceType::ROOK:
		if (currentTurn == WHITE)
		{
			if (KCastle && y1 == 7)
				KCastle = 0;
			if (QCastle && y1 == 0)
				QCastle = 0;
		}
		else
		{
			if (kCastle && y1 == 7)
				kCastle = 0;
			if (qCastle && y1 == 0)
				qCastle = 0;
		}
		break;
	case PieceType::PAWN:
		if (std::make_pair(x2, y2) == enPassantTarget)
			board[x1][y2] = nullptr;

		enPassantTarget = (abs(x1 - x2) == 2) ? std::make_pair((x1 + x2) / 2, y2) : std::make_pair(-1, -1);
		if (isPromotion)
			(board[x2][y2] = PieceFactory::createPiece(promoteTo))->setColor(currentTurn);
		break;
	}

	if (currentTurn == WHITE)
		currentTurn = BLACK;
	else
	{
		currentTurn = WHITE;
		fullMoveNumber++;
	}

	fenHistory.push_back(makeFEN());
}

void Board::undoMove()
{
	if (history.empty())
		return;

	Move lastMove = history.back();
	history.pop_back();
	fenHistory.pop_back();

	if (board[lastMove.secondPos.first][lastMove.secondPos.second]->getType() == PieceType::KING)
	{
		if (lastMove.turnBefore == WHITE)
			whiteKingPos = lastMove.firstPos;
		else
			blackKingPos = lastMove.firstPos;

		if (lastMove.firstPos.second == 4)
		{
			if (lastMove.secondPos.second == 6)
				board[lastMove.firstPos.first][7] = std::move(board[lastMove.firstPos.first][5]);
			else if (lastMove.secondPos.second == 2)
				board[lastMove.firstPos.first][0] = std::move(board[lastMove.firstPos.first][3]);
		}
	}

	if (board[lastMove.secondPos.first][lastMove.secondPos.second]->getType() == PieceType::PAWN && lastMove.secondPos == lastMove.enPassantTargetBefore)
		(board[lastMove.firstPos.first][lastMove.secondPos.second] = PieceFactory::createPiece(PieceType::PAWN))->setColor(currentTurn);

	if (lastMove.isPromotion)
		(board[lastMove.firstPos.first][lastMove.firstPos.second] = PieceFactory::createPiece(PieceType::PAWN))->setColor(lastMove.turnBefore);
	else
		board[lastMove.firstPos.first][lastMove.firstPos.second] = std::move(board[lastMove.secondPos.first][lastMove.secondPos.second]);
	board[lastMove.secondPos.first][lastMove.secondPos.second] = PieceFactory::createPiece(lastMove.takenPiece);
	if (board[lastMove.secondPos.first][lastMove.secondPos.second])
		board[lastMove.secondPos.first][lastMove.secondPos.second]->setColor(currentTurn);
	currentTurn = lastMove.turnBefore;

	KCastle = lastMove.KCastleBefore;
	QCastle = lastMove.QCastleBefore;
	kCastle = lastMove.kCastleBefore;
	qCastle = lastMove.qCastleBefore;

	enPassantTarget = lastMove.enPassantTargetBefore;
	halfMoveClock = lastMove.halfMoveClockBefore;
	fullMoveNumber = lastMove.fullMoveNumberBefore;
}