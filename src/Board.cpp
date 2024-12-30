#include "Board.h"
#include "DefaultBoards.h"

Board::Board(int board)
{
	selectBoard(board);
}

Board::Board(const Board &other)
	: m_current_player(other.m_current_player),
	  m_other_player(other.m_other_player),
	  m_game_end(other.m_game_end),
	  m_move_not_possible(other.m_move_not_possible),
	  m_index_last_move(other.m_index_last_move),
	  m_possible_moves(other.m_possible_moves)
{
	for (int i = 0; i < 100; ++i)
	{
		m_board[i] = other.m_board[i];
	}
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

	m_current_player = (rand() % 2) + 1; // Randomly select the starting player
	m_other_player = m_current_player ^ 0b11;
	nextPlayer();
}

void Board::loadBoard(int board[])
{
	for (int i = 0; i < 100; i++)
	{
		m_board[i] = board[i];

		if (board[i] == 1 || board[i] == 2)
		{
			m_stone_counts[board[i]]++;
			m_stone_counts[0]++;
		}
	}
}

std::vector<std::pair<int, std::vector<int>>> Board::getMoves(bool get_estimations) const
{
	std::vector<std::pair<int, std::vector<int>>> moves;
	if (get_estimations)
	{
		for (auto &mv : m_estimated_moves)
		{
			moves.push_back(mv);
		}
	}
	else
	{
		for (auto &mv : m_possible_moves)
		{
			moves.push_back(mv);
		}
	}
	return moves;
}

void Board::nextPlayer()
{
	togglePlayer();
	checkForMoves();

	if (m_possible_moves.empty())
	{
		m_move_not_possible++;

		togglePlayer();
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

inline void Board::togglePlayer()
{
	m_current_player = m_other_player;
	m_other_player ^= 0b11;  // xor turns the player 1 into player 2 and vice versa
}

std::pair<int, int> Board::countPoints() const
{
	return std::make_pair(m_stone_counts[1], m_stone_counts[2]);
}

int Board::getCurrentPlayer() const
{
	return m_current_player;
}

void Board::copyBoard(int board_copy[], bool highlight) const
{
	for (int i = 0; i < 100; i++)
	{
		board_copy[i] = m_board[i];
	}

	if (highlight)
	{
		for (auto &mv : m_possible_moves)
		{
			board_copy[mv.first] = 3;
		}

		if (m_index_last_move != -1)
		{
			board_copy[m_index_last_move] += 4; // if the last move was made by player 1, the field is marked with 5, if it was made by player 2, the field is marked with 6
		}
	}
}

const int *Board::getBoard() const
{
    return m_board;
}

void Board::checkForMoves()
{
	m_possible_moves.clear();
	m_estimated_moves.clear();

	for (int i = 1; i < 10 - 1; i++) // Exclude borders of the board
	{
		for (int j = 1; j < 10 - 1; j++)
		{
			int index = i * 10 + j;

			if (m_board[index] == 0) // Check only empty spaces
			{
				std::vector<int> move_flips_current;
				std::vector<int> move_flips_other;

				auto checkDirection = [&](int direction, int player, std::vector<int> &result) -> bool
				{
					std::vector<int> flip_candidates;
					int current_index = index + direction;

					while (m_board[current_index] != 4) // Stop at the border
					{
						if (m_board[current_index] == 0)
							return false;

						// If the current field is the player's own color and there are flips in between, a valid move was found
						if (m_board[current_index] == player)
						{
							if (!flip_candidates.empty())
							{
								result.insert(result.end(), flip_candidates.begin(), flip_candidates.end());
								return true;
							}
							return false;
						}

						flip_candidates.push_back(current_index);
						current_index += direction;
					}
					return false;
				};

				for (int direction : {-11, -10, -9, -1, 1, 9, 10, 11}) // Check all 8 directions
				{
					if (!checkDirection(direction, m_current_player, move_flips_current)) // If there is no move for the first player, try the second
						checkDirection(direction, m_other_player, move_flips_other);
				}

				if (!move_flips_current.empty()) // If any valid flips were found, this is a valid move
					m_possible_moves[index] = move_flips_current;

				if (!move_flips_other.empty()) // also store the estimated flips for the other player (disregarding the current player's move)
					m_estimated_moves[index] = move_flips_other;
			}
		}
	}
}

bool Board::makeMove(int index)
{
	if (m_game_end || m_possible_moves.find(index) == m_possible_moves.end())
		return false;

	m_board[index] = m_current_player;

	// Update stone counts
	m_stone_counts[m_current_player]++;
	m_stone_counts[0]++;

	for (int flip_index : m_possible_moves[index])
	{
		m_board[flip_index] = m_current_player;

		// Update stone counts for the flipped stones
		m_stone_counts[m_current_player]++;
		m_stone_counts[m_other_player]--;
	}

	m_index_last_move = index;
	nextPlayer();
	return true;
}

bool Board::gameEnd() const
{
	return m_game_end;
}
