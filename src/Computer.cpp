#include "Computer.h"
#include "Board.h"

Computer::Computer(Board *board) : m_board(board) {};

int Computer::computerSelectMove()
{
	m_total_moves++;
	return determineBestMove();
}

int Computer::determineBestMove()
{
	int best_score = -1000;
	int best_move = -1;
	for (auto &mv : m_board->getMoves())
	{
		Board *board_copy = new Board(*m_board);
		
		board_copy->makeMove(mv.first);
		int score = evaluateBoard(board_copy);
		
		delete board_copy;

		if (score > best_score)
		{
			best_score = score;
			best_move = mv.first;
		}
	}
	return best_move;
}

// score is positive if the board is in favor of player 2
int Computer::evaluateBoard(const Board *board)
{
	if (board->gameEnd())
	{
		std::pair<int, int> points = board->countPoints();
		if (points.first == points.second)
		{
			return 0;
		}
		else
		{
			return 1000 * (points.second - points.first);
		}
	}
	
	const int *cur_board = board->getBoard();

	// Evaluate board state though positional score (includes piece count)
	int positional_score = 0;
	for (int i = 1; i < 10; i++)
	{
		for (int j = 1; j < 10; j++)
		{
			int idx = i * 10 + j;
			if (cur_board[idx] == 2)
			{
				positional_score += m_weight_map[idx];
			}
			else if (cur_board[idx] == 1)
			{
				positional_score -= m_weight_map[idx];
			}
		}
	}

	// get mobility
	int opponent_mobility = board->getMoves(false).size();
	int own_mobility = board->getMoves(true).size();

	return positional_score + 3 * (own_mobility - opponent_mobility);
}