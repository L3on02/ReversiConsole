#include "Logger.h"
#include "Controller.h"

#include <iomanip>

Logger::Logger(Controller *controller) : m_controller(controller)
{
	m_move_num = 1;
	m_file_out.open("log.txt");

	if (!m_file_out)
		std::cout << "Error occured while trying to open 'log.txt'" << std::endl;
	else
		std::cout << "log file opened successfully" << std::endl;
}

Logger::~Logger()
{
	m_file_out.close();
}

void Logger::writeToLog(bool is_player_1, char row, int col)
{
	m_file_out << std::setw(2) << std::right << m_move_num << ". " << std::setw(8) << std::left << m_controller->returnName(is_player_1) << " makes move: " << row << col << std::endl;
	m_move_num += 1;
}

void Logger::displayLogs()
{
	std::ifstream m_file_in("log.txt");

	while (getline(m_file_in, m_line))
	{
		std::cout << m_line << std::endl;
	}
}