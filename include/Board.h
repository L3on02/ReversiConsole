#ifndef BOARD_H
#define BOARD_H

#include <string>
#include <vector>
#include <unordered_map>

class Board
{
public:
	/**
	 * @brief Construct a new Board object
	 * 
	 * @param board The starting board to use (0-5) where 0 is the default board
	 */
	Board(int board);

	/**
	 * @brief Construct a new Board object by copying another board
	 * 
	 * @param other The board to copy
	 */
	Board(const Board &other);

	/**
	 * @brief Get all possible moves for the current player
	 * 
	 * @param get_estimations If the function should return the estimated moves for the player not at turn (used for board evaluation)
	 * 
	 * @return A `vector` of all possible moves for the current player
	 * A `move` is a pair of an index and a vector of indices that said move would flip
	 */
	std::vector<std::pair<int, std::vector<int>>> getMoves(bool get_estimations = false) const;

	/**
	 * @brief Tries to make a move at the given index
	 * 
	 * @return returns `true` if the move was successful and `false` if it the move was not allowed
	 */
	bool makeMove(int index);

	/**
	 * @brief Checks if the game has ended
	 * 
	 * @return `true` if the game has ended and `false` if it has not
	 */
	bool gameEnd() const;

	/**
	 * @brief Gets a copy of the current board
	 * 
	 * @param copyBoard An 1D array with 100 elements representing the board to copy the current board to
	 * @param highlight If the returned board will highlight the possible moves for the current player by setting the value to 3
	 * 					Adiitionaly, the last move will be highlighted by setting the value to 5 for player 1 or 6 for player 2
	 */
	void copyBoard(int copyBoard[], bool highlight = false) const;

	/**
	 * @brief Gets the current board
	 * 
	 * @return A const pointer to the current board (1D array with 100 ints: `int[100]`)
	 */
	const int* getBoard() const;

	/**
	 * @brief Counts the points of the current game
	 * 
	 * @return A pair of integers representing the points of player 1 and player 2
	 */
	std::pair<int, int> countPoints() const;

	/**
	 * @brief Gets the total amount of stones on the board
	 * 
	 * @return An integer representing the total amount of stones on the board
	 */
	int totalStones() const;

	/**
	 * @brief Gets the next player
	 * 
	 * @return An integer representing the next player (1 or 2)
	 */
	int getCurrentPlayer() const;

private:
	void selectBoard(int board);
	void loadBoard(int board[]);

	void nextPlayer();
	inline void togglePlayer();

	void checkForMoves();

	int m_current_player, m_other_player;
	bool m_game_end = false;

	int m_move_not_possible = 0; // Stores how many times in a row any player could not move
	int m_index_last_move = -1; // Stores the index of the last move

	int m_stone_counts[3]; // Stores the total amount of stones and the stones for each player (0 = total, 1 = player 1, 2 = player 2)

	std::unordered_map<int, std::vector<int>> m_possible_moves;
	std::unordered_map<int, std::vector<int>> m_estimated_moves; // Stores the possible moves that the other player could make, would it be their turn (used for board evaluation)	

	int m_board[100];
};

#endif
