#include "Controller.h"
#include "Board.h"
#include "Logger.h"

Controller::Controller(int player_count) : m_player_count(player_count)
{
	m_logger = new Logger(this);
}

Controller::~Controller()
{
	delete m_logger;
	if (m_board)
		delete m_board;
}

void Controller::startGame()
{
	this->initializeGame(); // Initializes the game

	this->runGame(); // Calls the game function

	this->postGameScreen(); // Displays the post-game screen
}

std::string Controller::returnName(bool is_player_1)
{
	return is_player_1 ? m_player1_name : m_player2_name;
}

void Controller::initializeGame()
{ // Initializes all important values and lets the player set the parameters for the game.

	m_player1_name = nameInput(1); // reads the name of player 1

	if (m_player_count == 2)
	{
		m_player2_name = nameInput(2); // reads the name of player 2 in case of player vs player
		m_is_vs_computer = false;
	}
	else
	{
		m_player2_name = "Computer";
		m_is_vs_computer = true;
	}

	m_board = new Board(m_logger, this, m_is_vs_computer); // Initializes the board

	system("clear");
}

void Controller::runGame()
{
	int move = rand() % 2;
	if (move == 1)
		m_board->nextPlayer();

	if (!m_is_vs_computer)
	{
		while (true)
		{
			if (!m_board->completeMove())
				break;
		}
	}
	else
	{
		while (true)
		{
			if (!(move++ % 2 == 0 ? m_board->completeMove() : m_board->computerMove()))
				break;
		}
	}
	system("clear");
	std::cout << std::endl;
}

std::string Controller::nameInput(int player)
{
	std::cout << std::endl << "Player " << player << ", please enter your name: " << std::endl << " > ";
	
	std::string name;
	getline(std::cin, name);

	std::cout << std::endl
			  << "You have chosen \"" << name << "\"!" << std::endl
			  << std::endl
			  << "-----------------------------------" << std::endl;
	return name;
}

// Displays winner etc. and contains the option to view the log file
void Controller::postGameScreen()
{
	std::cout << std::endl
			  << "-----------------------------------" << std::endl
			  << std::endl;

	int points_player1 = m_board->countPoints(1);
	int points_player2 = m_board->countPoints(2);

	if (points_player1 == points_player2)
		std::cout << "With " << points_player1 << " points each, the game ends in a draw!" << std::endl;
	else
	{
		std::string winner = points_player1 > points_player2 ? m_player1_name : m_player2_name;
		int points = points_player1 > points_player2 ? points_player1 : points_player2;

		std::cout << "With " << points << " points, the winner is " << winner << "!" << std::endl;
	}
	std::cout << std::endl
			  << "-----------------------------------" << std::endl
			  << std::endl;

	while (true)
	{
		std::cout << "Would you like to view the log file? [Y/N]" << std::endl;
		char input;
		std::cin >> input;
		std::cout << std::endl;
		std::cin.ignore();

		switch (input)
		{
		case 'Y':
		case 'y':
			std::cout << "Opening log file..." << std::endl
					  << "--------------------------------------------" << std::endl
					  << std::endl;

			m_logger->displayLogs(); // Calls the log file display

			std::cout << std::endl
					  << "--------------------------------------------" << std::endl;
			std::cout << "Press any key to close logs." << std::endl;
			std::cin.get();
			break;

		case 'N':
		case 'n':
			break;

		default:
			std::cout << "Invalid input, please enter 'Y' for Yes or 'N' for No." << std::endl
					  << std::endl;
			continue;
		}
		break;
	}

	system("clear");
}
