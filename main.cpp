#include <iostream>
#include "Board.h"
#include "Utils.h"

void print(Board& board)
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (board.getPieceAt(i, j))
				std::cout << board.getPieceAt(i, j)->print() << ' ';
			else
				std::cout << "0 ";
		}
		std::cout << std::endl;
	}
}

int main()
{
	auto testFEN1 = "2nbk2r/p3p3/rP3q1P/6pP/6P1/Rp3Q1p/P3P3/2NBK2R w Kk g6 1 1";
	auto testFEN2 = "2nbk2r/p3p3/rP3q1P/6p1/6Pp/Rp3Q1p/P3P3/2NBK2R b Kk g3 1 1";
	Board board;
	board.loadFEN(testFEN1);
	print(board);
	std::string x;
	while (std::cin >> x)
	for (auto move : board.getPieceAt(Utils::stringToCoord(x).first, Utils::stringToCoord(x).second)->getPseudoLegalMoves(board, Utils::stringToCoord(x).first, Utils::stringToCoord(x).second))
		std::cout << Utils::coordToString(move) << ' ';

	return 0;
}