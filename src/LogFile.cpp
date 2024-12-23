#include "LogFile.h"

LogFile::LogFile()
{
	m_move_num = 1;

	m_file_out.open("log.txt");

	if (!m_file_out)
		std::cout << "Error occured while trying to open 'log.txt'" << std::endl;
	else
		std::cout << "log file opened successfully" << std::endl;
}

LogFile::~LogFile()
{ // closes the log file

	m_file_out.close();
	std::cout << "log file closed" << std::endl;
}

void LogFile::writeToLog(bool is_player_1, char row, int col, GameMaster &GM)
{
	m_file_out << std::setw(2) << std::right << m_move_num << ". " << std::setw(8) << std::left << GM.returnName(is_player_1) << " makes move: " << row << col << std::endl;
	m_move_num += 1;
}

void LogFile::displayLog()
{
	std::ifstream m_file_in("log.txt");

	while (getline(m_file_in, m_line))
	{
		std::cout << m_line << std::endl;
	}
}