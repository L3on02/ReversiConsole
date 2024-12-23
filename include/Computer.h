#ifndef COMPUTER_H
#define COMPUTER_H

#include <string>
#include <iostream>

// forward declaration
class Board;

class Computer
{
public:
	Computer(Board *board);

	int computerSelectMove();

	int determineBestMove();

	int checkForFlips(int index, int board[]);

	void checkForFlipsRek(int index, int direction, int board[]);

private:
	int m_local_counter = 0;

	int m_counter_comp = 0;

	Board *m_board;
};

#endif