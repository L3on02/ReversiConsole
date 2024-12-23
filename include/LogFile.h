#ifndef LOGFILE_H
#define LOGFILE_H

#include <iostream>
#include <fstream>
#include <string>

#include "GameMaster.h"
class GameMaster;

class LogFile {
public:
	LogFile();
	~LogFile();

	void writeToLog(bool player1, char reihe, int spalte, GameMaster &GM);

	void displayLog();


private:
	std::ifstream m_file_in;
	std::ofstream m_file_out;
	int m_move_num;
	std::string m_line;
};
#endif
