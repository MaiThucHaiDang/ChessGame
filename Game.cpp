#include "Game.h"
#include <Windows.h>
#include <iostream>
#include "Utils.h"
#include <algorithm>

Game::Game()
{
	gameBoard.resetBoard();
}

std::pair<int, int> Game::processInput()
{
	std::string str;
	std::cin >> str;
	return Utils::stringToCoord(str);
}

void Game::run()
{
	while (1)
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if (gameBoard.getPieceAt(i, j))
					std::cout << gameBoard.getPieceAt(i, j)->print() << ' ';
				else
					std::cout << "0 ";
			}
			std::cout << std::endl;
		}

		bool isGameOver = 0;
		if (gameBoard.isCheckmate() && (isGameOver = 1))
			std::cout << "Ben " << (gameBoard.getCurrentTurn() == WHITE ? "Trang" : "Den") << " da bi chieu het!\n";
		else if (gameBoard.isStalemate() && (isGameOver = 1))
			std::cout << "Hoa do ben " << (gameBoard.getCurrentTurn() == WHITE ? "Trang" : "Den") << " het nuoc di!!\n";
		else if (gameBoard.getHalfMoveClock() == 100 && (isGameOver = 1))
			std::cout << "Hoa do luat 50 nuoc!\n";
		else if (gameBoard.isThreefoldRepetition() && (isGameOver = 1))
			std::cout << "Hoa do lap lai the co 3 lan!\n";
		else if (gameBoard.isInsufficientMaterial() && (isGameOver = 1))
			std::cout << "Hoa do luat khong du quan!\n";

		int choose;
		std::cout << "\n	Menu:\n";
		if (!isGameOver)
			std::cout << "0: Di chuyen quan.\n";
		std::cout << "1: Undo Move.\n";
		std::cout << "2. Choi lai.\n";
		std::cout << "3: Ket thuc game.\n";
		std::cout << "Ban muon lam gi: ";
		std::cin >> choose;
		switch (choose)
		{
		case 0:
		{
			if (isGameOver)
				break;
			std::string start, end;
			std::cout << "\nChon vi tri ban muon di chuyen quan: ";
			std::cin >> start;
			auto coordStart = Utils::stringToCoord(start);
			std::vector<std::pair<int, int>> legalMoves;
			while (!gameBoard.getPieceAt(coordStart.first, coordStart.second) || gameBoard.getPieceAt(coordStart.first, coordStart.second)->getColor() != gameBoard.getCurrentTurn() || (legalMoves = gameBoard.getLegalMoves(coordStart.first, coordStart.second)).empty())
			{
				if (!gameBoard.getPieceAt(coordStart.first, coordStart.second))
					std::cout << "Khong co quan o vi tri " << start << ". Moi ban chon lai: ";
				else if (gameBoard.getPieceAt(coordStart.first, coordStart.second)->getColor() != gameBoard.getCurrentTurn())
					std::cout << "Quan o vi tri " << start << " khong dung luot. Moi ban chon lai: ";
				else
					std::cout << "Quan o vi tri " << start << " khong con nuoc di nao hop le. Moi ban chon lai: ";
				std::cin >> start;
				coordStart = Utils::stringToCoord(start);
			}

			std::cout << "\nNuoc di hop le la: ";
			for (const auto& move : legalMoves)
			{
				std::cout << Utils::coordToString(move);
				if (move == legalMoves.back())
					std::cout << ". Ban muon chon vi tri nao (chon 0 neu khong muon di quan nay nua): ";
				else
					std::cout << ", ";
			}
			std::cin >> end;
			while (end != "0" && std::find(legalMoves.begin(), legalMoves.end(), Utils::stringToCoord(end)) == legalMoves.end())
			{
				std::cout << "Vi tri khong hop le. Moi ban chon lai: ";
				std::cin >> end;
			}

			if (end != "0")
			{
				auto coordEnd = Utils::stringToCoord(end);
				auto promoteTo = PieceType::QUEEN;
				if (gameBoard.getPieceAt(coordStart.first, coordStart.second)->getType() == PieceType::PAWN && (coordEnd.first == 0 || coordEnd.first == 7))
				{
					int promotionNumber;
					std::cout << "Ban muon phong cap thanh quan gi (1: Hau, 2: Xe, 3: Tuong, 4: Ma): ";
					std::cin >> promotionNumber;
					while (promotionNumber < 1 || promotionNumber > 4)
					{
						std::cout << "Nhap khong hop le. Moi ban nhap lai: ";
						std::cin >> promotionNumber;
					}

					switch (promotionNumber)
					{
					case 2:
						promoteTo = PieceType::ROOK;
						break;
					case 3:
						promoteTo = PieceType::BISHOP;
						break;
					case 4:
						promoteTo = PieceType::KNIGHT;
						break;
					}
				}
				gameBoard.makeMove(coordStart.first, coordStart.second, coordEnd.first, coordEnd.second, promoteTo);
			}
			break;
		}
		case 1:
			gameBoard.undoMove();
			break;
		case 2:
			gameBoard.resetBoard();
			break;
		case 3:
			return;
		}

		std::cout << "\033[2J\033[1;1H";
	}
}