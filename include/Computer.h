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

private:
	int determineBestMove();

	Board *m_board;

	int m_weight_map[100] = { 
		4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
		4, 5,-8, 2, 2, 2, 2,-8, 5, 4,
		4,-8,-8, 1, 1, 1, 1,-8,-8, 4,
		4, 2, 1, 1, 1, 1, 1, 1, 2, 4,
		4, 2, 1, 1, 1, 1, 1, 1, 2, 4,
		4, 2, 1, 1, 1, 1, 1, 1, 2, 4,
		4, 2, 1, 1, 1, 1, 1, 1, 2, 4,
		4,-8,-8, 1, 1, 1, 1,-8,-8, 4,
		4, 5,-8, 2, 2, 2, 2,-8, 5, 4,
		4, 4, 4, 4, 4, 4, 4, 4, 4, 4
	};
};
#endif