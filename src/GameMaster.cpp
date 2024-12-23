#include "GameMaster.h"

GameMaster::GameMaster() {}

void GameMaster::initializeGame(int player_count, Board &brett, LogFile &log, GameMaster &GM)
{ // Initializes all important values and lets the player set the parameters for the game.

	m_player1_name = nameInput(1); // reads the name of player 1

	if (player_count == 2)
	{
		m_player2_name = nameInput(2); // reads the name of player 2 in case of player vs player
		m_is_vs_computer = false;
	}
	else
	{
		m_player2_name = "Computer";
		m_is_vs_computer = true;
	}

	m_is_testgame = boolTestgame();

	system("clear");

	Game(brett, log, GM);
}

void GameMaster::Game(Board &brett, LogFile &log, GameMaster &GM)
{

	if (m_is_testgame)
	{
		brett.testBoard();
	}

	if (!m_is_vs_computer)
	{

		if ((rand() % (2)))
		{ // randomly decides whether player 1 or player 2 starts
			brett.nextPlayer();
		}

		while (true)
		{
			if (brett.completeMove(log, GM))
				continue;
			break;
		}
	}
	else
	{
		Computer *computer = new Computer(); // New object of the Computer class

		if ((rand() % (2)))
		{ // randomly decides whether player 1 or player 2 starts
			while (true)
			{

				if (!brett.completeMove(log, GM))
					break;

				if (!brett.computerMove(brett, *computer, log, GM))
					break;
			}
		}
		else
		{
			brett.nextPlayer(); // Board starts by default with player 1, so a player change must occur here

			while (true)
			{

				if (!brett.computerMove(brett, *computer, log, GM))
					break;

				if (!brett.completeMove(log, GM))
					break;
			}
		}

		delete computer;
	}
	system("clear");
	std::cout << std::endl;
}

std::string GameMaster::returnName(bool player1)
{
	if (player1)
		return m_player1_name;
	else
		return m_player2_name;
}

std::string GameMaster::nameInput(int player)
{

	std::cout << std::endl;
	std::cout << "Player " << player << ", please enter your name: " << std::endl;
	std::string name;
	std::cout << " > ";
	getline(std::cin, name);
	std::cout << std::endl;
	std::cout << "You have chosen \"" << name << "\"!" << std::endl;
	std::cout << std::endl;
	std::cout << "-----------------------------------" << std::endl;
	return name;
}

bool GameMaster::boolTestgame()
{
	while (true)
	{
		std::cout << std::endl;
		std::cout << "Do you want to start the game as a test game? -> [Y/N]" << std::endl;
		char input;
		std::cin >> input;
		std::cin.ignore();

		switch (input)
		{
		case 'Y':
		case 'y':
			return true;

		case 'N':
		case 'n':
			return false;

		default:
			std::cout << "Invalid input, please enter 'Y' for Yes or 'N' for No." << std::endl;
			std::cout << std::endl;
			continue;
		}
	}
}