#ifndef COMPUTER_H
#define COMPUTER_H

#include <vector>

// forward declaration
class Board;

class Computer
{
public:
    Computer(Board *board);

    int computerSelectMove();

private:
    int negamax(int depth, int alpha, int beta, int perspective, Board *board);
    std::vector<std::pair<int, std::vector<int>>> orderMoves(std::vector<std::pair<int, std::vector<int>>> moves);

    int evaluateBoard(const Board* board);

    Board *m_board;

    int m_weight_map[100] = {
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,  99, -20,  10,   8,   8,  10, -20,  99,   0,
        0, -20, -25,   1,   1,   1,   1, -25, -20,   0,
        0,  10,   1,   6,   3,   3,   6,   1,  10,   0,
        0,   8,   1,   3,   3,   3,   3,   1,   8,   0,
        0,   8,   1,   3,   3,   3,   3,   1,   8,   0,
        0,  10,   1,   6,   3,   3,   6,   1,  10,   0,
        0, -20, -25,   1,   1,   1,   1, -25, -20,   0,
        0,  99, -20,  10,   8,   8,  10, -20,  99,   0,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0
    };
};

#endif
