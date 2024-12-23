#include "Computer.h"
#include "Board.h"

Computer::Computer(Board *board) : m_board(board) {};

int Computer::computerSelectMove()
{
	return determineBestMove();
}

int Computer::determineBestMove()
{
	int board_copy[100];
	m_board->getBoard(board_copy);

	int indexBestMove = 0;
	int currentBestMove = -10; // eliminates the unlikely case that if the computer only has one stone as a possible move next to a corner stone,
							   // it places a stone on the edge.

	// The following block ensures that whenever possible a corner is occupied, as these are more important than any number of flipped stones
	if (board_copy[18] == 3)
		return 18;
	else if (board_copy[11] == 3)
		return 11;
	else if (board_copy[88] == 3)
		return 88;
	else if (board_copy[81] == 3)
		return 81;
	// If no corner can be occupied, the computer selects the move that flips the most opponent stones
	else
	{
		for (int j = 0; j < 100; j++)
		{
			if (board_copy[j] == 3)
			{
				int currentMove = checkForFlips(j, board_copy);

				// This makes the computer "unpredictable" as it randomly selects one of the moves if there are multiple equivalent moves
				if ((rand() % (2)))
				{ // randomly outputs 0 or 1, i.e., true or false

					if (currentMove > currentBestMove)
					{
						indexBestMove = j;
						currentBestMove = currentMove;
					}
				}
				else
				{
					if (currentMove >= currentBestMove)
					{
						indexBestMove = j;
						currentBestMove = currentMove;
					}
				}
			}
		}
		return indexBestMove;
	}
}

int Computer::checkForFlips(int index, int board[])
{
	m_counter_comp = 0;

	// possible weighting of the fields
	// Stones adjacent to the corners are suboptimal, as the opponent has the opportunity to occupy a corner stone,
	// they are therefore only selected if no other move is possible.
	switch (index)
	{
	case 12:
	case 21:
	case 22:
	case 17:
	case 27:
	case 28:
	case 71:
	case 72:
	case 82:
	case 77:
	case 78:
	case 87:
		return -9; // By returning -9, one of these moves is only chosen if no other move with one or more flips is found

	// Stones on the edge of the board are "more valuable" than stones in the middle.
	case 13:
	case 14:
	case 15:
	case 16:
	case 31:
	case 41:
	case 51:
	case 61:
	case 38:
	case 48:
	case 58:
	case 68:
	case 83:
	case 84:
	case 85:
	case 86:
		m_counter_comp = 2; // The counter for possible flips starts at 2 instead of 0, so 2 additional virtual flips are added to them when calculating
		break;				// the best possible move.
	}

	for (int dir : {-11,-10,-9,-1,1,9,10,11})
	{
		checkForFlipsRek(index, dir, board);
	}

	return m_counter_comp;
}

void Computer::checkForFlipsRek(int index, int direction, int board[])
{
	switch (board[index + direction])
	{
	case 1:
		m_local_counter++;
		checkForFlipsRek((index + direction), direction, board);
		break;

	case 2:
		m_counter_comp += m_local_counter;
		m_local_counter = 0;
		break;

	default:
		m_local_counter = 0;
		break;
	}
}
