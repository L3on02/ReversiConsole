#include "Computer.h"
#include "Board.h"
#include <algorithm>
#include <cmath>

Computer::Computer(Board *board) : m_board(board) {};

int Computer::computerSelectMove()
{
	std::vector<std::pair<int, std::vector<int>>> moves = m_board->getMoves();

	if (moves.size() == 1)
	{
		return moves[0].first;
	}

	int best_move = moves[0].first;
	int best_value = -1000;

	int search_depth = 6;

	for (auto &mv : moves)
	{
		Board *board_copy = new Board(*m_board);
		board_copy->makeMove(mv.first);
		int value = negamax(search_depth, -1000, 1000, 1, board_copy);
		if (value > best_value)
		{
			best_value = value;
			best_move = mv.first;
		}
		delete board_copy;
	}
	return best_move;
}

// negamax is a variation of minmax that uses the property that the value of a node is the negative of the value of its children
int Computer::negamax(int depth, int alpha, int beta, int perspective, Board *board) 
{
	if (depth == 0 || board->gameEnd())
	{
		return perspective * evaluateBoard(board); // perspective is 1 if it is the computer's turn and -1 if it is the player's turn
	}

	int best_value = -1000;
	for (auto &mv : orderMoves(board->getMoves()))
	{
		Board *board_copy = new Board(*board);
		board_copy->makeMove(mv.first);

		int value = -negamax(depth - 1, -beta, -alpha, -perspective, board_copy); // switches and negates alpha and beta since they are now from the perspective of the other player
		best_value = std::max(best_value, value);
		alpha = std::max(alpha, value);

		delete board_copy;
		if (alpha >= beta) // if this is true, the current branch is not worth exploring
			break;
	}
	return best_value;
}

std::vector<std::pair<int, std::vector<int>>> Computer::orderMoves(std::vector<std::pair<int, std::vector<int>>> moves)
{
	std::sort(moves.begin(), moves.end(), [&](const std::pair<int, std::vector<int>> &a, const std::pair<int, std::vector<int>> &b) {
		return (m_weight_map[a.first] + 3 * a.second.size()) > (m_weight_map[b.first] + 3 * b.second.size());
	});
	return moves;
}

// score is positive if the board is in favor of player 2
int Computer::evaluateBoard(const Board *board)
{
	if (board->gameEnd())
	{
		std::pair<int, int> points = board->countPoints();
		if (points.first == points.second)
			return 0;
		else
			return 1000 * (points.second - points.first);
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