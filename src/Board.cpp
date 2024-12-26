#include "Board.h"
#include "DefaultBoards.h"

Board::Board(int board)
{
	selectBoard(board);
}

void Board::selectBoard(int board)
{
	switch (board)
	{
	case 1:
		loadBoard(test_board_1);
		break;
	case 2:
		loadBoard(test_board_2);
		break;
	case 3:
		loadBoard(test_board_3);
		break;
	case 4:
		loadBoard(test_board_4);
		break;
	case 5:
		loadBoard(test_board_5);
		break;
	default:
		loadBoard(default_board);
		break;
	}

	m_is_player1 = rand() % 2; // Randomly select the starting player
	nextPlayer();
}

void Board::loadBoard(int board[])
{
	for (int i = 0; i < 100; i++)
	{
		m_board[i] = board[i];
	}
}

std::vector<move> Board::getMoves()
{
	std::vector<move> moves;
	for (move mv : m_possible_moves)
	{
		moves.push_back(mv);
	}
	return moves;
}

void Board::nextPlayer()
{
	m_is_player1 = !m_is_player1;
	checkForMoves();

	if (m_possible_moves.empty())
	{
		m_move_not_possible++;

		m_is_player1 = !m_is_player1;
		checkForMoves();

		if (m_possible_moves.empty()) // Both players have no moves
		{
			m_game_end = true; // End the game
		}
		else if (m_move_not_possible >= 3) // Current player missed 3 turns
		{
			m_game_end = true; // End the game
		}
	}
	else
	{
		m_move_not_possible = 0; // Reset missed turn counter
	}
}

std::pair<int, int> Board::countPoints()
{
	int points_a = 0;
	int points_b = 0;
	for (int i = 0; i < 100; i++)
	{
		if (m_board[i] == 1)
			points_a++;
		else if (m_board[i] == 2)
			points_b++;
	}
	return std::make_pair(points_a, points_b);
}

int Board::getNextPlayer()
{
	return m_is_player1 ? 1 : 2;
}

void Board::getBoard(int board_copy[], bool highlight)
{
	for (int i = 0; i < 100; i++)
	{
		board_copy[i] = m_board[i];
	}

	if (highlight)
	{
		for (move mv : m_possible_moves)
		{
			board_copy[mv.first] = 3;
		}

		if (m_index_last_move != -1)
		{
			board_copy[m_index_last_move] += 4; // if the last move was made by player 1, the field is marked with 5, if it was made by player 2, the field is marked with 6
		}
	}
}

void Board::checkForMoves()
{
	m_possible_moves.clear();
	int which_player = m_is_player1 ? 1 : 2;

	for (int i = 1; i < m_rows - 1; i++) // Exclude borders of the board
	{
		for (int j = 1; j < m_cols - 1; j++)
		{
			int index = i * m_cols + j;

			if (m_board[index] == 0) // Check only empty spaces
			{
				std::vector<int> move_flips;
				for (int direction : {-11, -10, -9, -1, 1, 9, 10, 11}) // Check all 8 directions
				{
					std::vector<int> flip_candidates;
					int current_index = index + direction;

					while (m_board[current_index] != 4) // Stop at the border
					{
						if (m_board[current_index] == 0)
							break;

						// If the current field is the player's own color and there are flips in between, a valid move was found
						if (m_board[current_index] == which_player)
						{
							if (!flip_candidates.empty())
								move_flips.insert(move_flips.end(), flip_candidates.begin(), flip_candidates.end());
							break;
						}

						flip_candidates.push_back(current_index);
						current_index += direction;
					}
				}

				if (!move_flips.empty()) // If any valid flips were found, this is a valid move
				{
					m_possible_moves[index] = move_flips;
				}
			}
		}
	}
}

bool Board::makeMove(int index)
{
	if (m_game_end || m_possible_moves.find(index) == m_possible_moves.end())
	{
		return false;
	}

	m_board[index] = m_is_player1 ? 1 : 2;

	for (int flip_index : m_possible_moves[index])
	{
		m_board[flip_index] = m_is_player1 ? 1 : 2;
	}

	m_index_last_move = index;
	nextPlayer();
	return true;
}

bool Board::gameEnd()
{
	return m_game_end;
}
