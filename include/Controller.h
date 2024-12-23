#ifndef GAMEMASTER_H
#define GAMEMASTER_H

#include <iostream>
#include <string>

// forward declarations
class Board;
class Logger;

class Controller
{
public:
	Controller(int player_count);
	~Controller();
	
	void startGame();
	std::string returnName(bool is_player_1);

private:
	void initializeGame();
	void runGame();

	std::string nameInput(int player);
	void postGameScreen();

	int m_player_count;
	std::string m_player1_name;
	std::string m_player2_name;
	bool m_is_vs_computer;

	Logger *m_logger;
	Board *m_board;
};

#endif
