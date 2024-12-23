#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>

// forward declarations
class Logger;
class Computer;
class Controller;

class Board
{
public:
	Board(Logger *logger, Controller *controller, bool is_vs_computer);
	~Board();

	bool completeMove();
	bool computerMove();

	void nextPlayer();
	void displayBoard();
	void returnBoard(int copyBoard[]);
	void makeMove(int index);
	void selectBoard();
	int countPoints(int player);

private:
	void loadBoard(int board[]);
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

	int m_counter = 0; // Important for CheckForMoves / CheckForFlips

	int m_move_not_possible = 0; // Stores how many times in a row a player could not move

	int m_board[100];

	bool m_is_player_1 = true;

	int m_index_last_move = 0; // Stores the last move

	Logger *m_logger;
	Controller *m_controller;
	Computer *m_computer;
};

#endif
