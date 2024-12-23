#ifndef COMPUTER_H
#define COMPUTER_H

#include <string>
#include <iostream>

#include "Board.h"
#include "GameMaster.h"

class Board;

class Computer {
public:
	Computer() {};

	int computerMove(Board &brett);

	int determineBestMove();

	int checkForFlips(int index);

	void checkForFlipsRek(int index, int direction);

private:
	int m_copy_board[100] = { 0 };
	
	int m_local_counter = 0;
	
	int m_counter_comp = 0;

	const int m_directions[8] = {
	-11,-10,-9,-1,1,9,10,11
	};
};

#endif