#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>

#include "LogFile.h"
#include "GameMaster.h"
#include "Computer.h"

class LogFile;
class GameMaster;
class Computer;

class Board {
public:
	Board(bool is_player_1) : m_is_player_1(is_player_1) {};

	bool completeMove(LogFile& log, GameMaster& GM);
	bool computerMove(Board &board, Computer &computer, LogFile &log, GameMaster &GM);

	void nextPlayer();
	void displayBoard(GameMaster &GM);
	void returnBoard(int *copyBoard);
	void makeMove(int index, LogFile &log, GameMaster &GM);
	void testBoard();
	int countPoints(int player);

private:
	void revertHighlights();

	int fieldCheck(int index, int direction);
	int checkForMoves();
	void highlightPossibleMoves(int index);

	void flip(int index, int direction, int amount);
	void checkForFlips(int index);
	void checkForFlipsRek(int index, int direction);

	int getPosition();
	void printError();
	std::string getColorCode(int colorCode);

	const int m_rows = 10;
	const int m_cols = 10; 

	int m_counter = 0;  // Important for CheckForMoves / CheckForFlips

	int m_move_not_possible = 0; // Stores how many times in a row a player could not move

	int m_board[100] = { // The starting board, which changes during the game.
	4,4,4,4,4,4,4,4,4,4,
	4,0,0,0,0,0,0,0,0,4,
	4,0,0,0,0,0,0,0,0,4,
	4,0,0,0,0,0,0,0,0,4,
	4,0,0,0,1,2,0,0,0,4,
	4,0,0,0,2,1,0,0,0,4,
	4,0,0,0,0,0,0,0,0,4,
	4,0,0,0,0,0,0,0,0,4,
	4,0,0,0,0,0,0,0,0,4,
	4,4,4,4,4,4,4,4,4,4,
	};

	bool m_is_player_1;

	int m_index_last_move = 0; // Stores the last move

	const int m_directions[8] = { // Stores the directions top left/middle/right, left/right, bottom left/middle/right "index"+"ArrayForDirection"
		-11,-10,-9,-1,1,9,10,11
	};
};

#endif
