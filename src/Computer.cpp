#include "Computer.h"
#include "Board.h"

Computer::Computer(Board *board) : m_board(board) {};

int Computer::computerSelectMove()
{
	return determineBestMove();
}

int Computer::determineBestMove()
{
	int best_score = -10;
	int best_move = -1;
	for(move mv : m_board->getMoves())
	{
		int index = mv.first;
		int score = mv.second.size() + m_weight_map[index];

		if(score > best_score)
		{
			best_score = score;
			best_move = index;
		}
	}
	return best_move;
}