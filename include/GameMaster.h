#ifndef GAMEMASTER_H
#define GAMEMASTER_H

#include <iostream>
#include <string>

#include "Board.h"
#include "LogFile.h"
#include "Computer.h"
class LogFile;
class Board;

class GameMaster {
public:
	GameMaster();

	void Game(Board &board, LogFile& log, GameMaster& GM);

	void initializeGame(int player_count, Board& board, LogFile &log, GameMaster& GM);

	std::string nameInput(int player);

	std::string returnName(bool player1);

	bool boolTestgame();

private:
	std::string m_player1_name;
	std::string m_player2_name;
	bool m_is_testgame = false;
	bool m_is_vs_computer = false;
};
#endif
