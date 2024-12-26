#ifndef GAMEMASTER_H
#define GAMEMASTER_H

#include <iostream>
#include <string>

// forward declarations
class Board;
class Computer;
class Interface;

class Controller
{
public:
	Controller();
	~Controller();
	
	void start();
	std::string returnName(bool is_player_1);

private:
	void initializeGame();
	void runGame();
	void evaluateGame();

	void cleanUp();

	int m_player_count;
	bool m_is_vs_computer;
	
	std::string m_player1_name;
	std::string m_player2_name;

	Board *m_board = nullptr;
	Computer *m_computer = nullptr;
	Interface *m_interface;
};

#endif
