#ifndef COMPUTER_H
#define COMPUTER_H

// forward declaration
class Board;

class Computer
{
public:
	Computer(Board *board);

	int computerSelectMove();

private:
	int determineBestMove();

    int evaluateBoard(const Board* board);

	int m_total_moves = 0;

    Board *m_board;

	int m_weight_map[100] = {
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,  50, -20,  10,   8,   8,  10, -20,  50,   0,
        0, -20, -25,   1,   1,   1,   1, -25, -20,   0,
        0,  10,   1,   6,   3,   3,   6,   1,  10,   0,
        0,   8,   1,   3,   3,   3,   3,   1,   8,   0,
        0,   8,   1,   3,   3,   3,   3,   1,   8,   0,
        0,  10,   1,   6,   3,   3,   6,   1,  10,   0,
        0, -20, -25,   1,   1,   1,   1, -25, -20,   0,
        0,  50, -20,  10,   8,   8,  10, -20,  50,   0,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0
    };
};
#endif