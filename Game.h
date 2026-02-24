#pragma once
#include "Board.h"

class Game
{
private:
	Board gameBoard;
public:
	Game();

	std::pair<int, int> processInput(); 
	void run();
};

