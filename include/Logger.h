#ifndef LOGFILE_H
#define LOGFILE_H

#include <iostream>
#include <fstream>
#include <string>

// forward declaration
class Controller;

class Logger
{
public:
	Logger(Controller *controller);
	~Logger();

	void writeToLog(bool player1, char reihe, int spalte);

	void displayLog();

private:
	std::ifstream m_file_in;
	std::ofstream m_file_out;
	int m_move_num;
	std::string m_line;

	Controller *m_controller;
};

#endif
