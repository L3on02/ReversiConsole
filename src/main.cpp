#include <iostream>
#include <string>
#include <cstdlib> // for rand(), srand(), ...
#include <ctime>

#include "Board.h"
#include "LogFile.h"
#include "GameMaster.h"

// Counts the points from the board
int countPoints(bool player1, Board &board)
{
	if (player1)
		return board.countPoints(1);
	else
		return board.countPoints(2);
}

// Determines the winner by counting points
bool determineWinner(Board &board)
{ // true -> Player 1 won; false -> Player 2 won
	if (countPoints(true, board) > countPoints(false, board))
	{
		return true;
	}
	else
		return false;
}

void rules()
{
	std::cout << std::endl;
	std::cout << "------------------------ Rules ------------------------" << std::endl;
	std::cout << " - Players take turns; the start is determined randomly." << std::endl;
	std::cout << " - Each player has pieces in their assigned color." << std::endl;
	std::cout << " - A piece must be placed on an empty field adjacent to a field occupied" << std::endl;
	std::cout << "   by a piece of the other color (horizontally, vertically, or diagonally)." << std::endl;
	std::cout << " - If a player cannot place a piece, the other player takes the turn." << std::endl;
	std::cout << " - Plastd::cing a piece that encloses one or more rows at both ends" << std::endl;
	std::cout << "   with pieces of your own color allows you to flip all pieces" << std::endl;
	std::cout << "   of the opponent's color in between to your own color." << std::endl;
	std::cout << " - The game ends when all fields are occupied or" << std::endl;
	std::cout << "   neither player can make a move." << std::endl;
	std::cout << " - The winner is the player with the most pieces in their color." << std::endl;
	std::cout << "-------------------------------------------------------" << std::endl;
	std::cout << std::endl;
}

// The menu allows the selection of the desired game mode and then calls the "GameMaster," which controls the actual game
bool menu(GameMaster &game_master, LogFile &log, Board &board)
{
	system("clear");
	std::cout << std::endl;
	std::cout << "-----------------------------------" << std::endl;
	std::cout << std::endl;
	std::cout << "Welcome to Reversi!!!" << std::endl;
	std::cout << std::endl;
	std::cout << "-----------------------------------" << std::endl;
	std::cout << std::endl;

	while (true)
	{
		std::cout << "Please select the desired game mode: " << std::endl;
		std::cout << std::endl;
		std::cout << "    (1) -> Player vs. Player " << std::endl;
		std::cout << "    (2) -> Player vs. Computer " << std::endl;
		std::cout << "    (3) -> Display game rules " << std::endl;
		std::cout << std::endl;
		std::cout << "To exit, please enter '0'. " << std::endl;

		char selection;
		std::cout << " > ";
		std::cin >> selection;
		std::cout << std::endl;
		std::cin.ignore();

		if (selection == '0')
		{
			std::cout << "The game will be closed!" << std::endl;
			std::cout << std::endl;
			return false;
		}

		system("clear");

		switch (selection)
		{
		case '1':
			game_master.initializeGame(2, board, log, game_master); // Calls the initialization function of the "Game" class and passes that 2 players play against each other
			board.displayBoard(game_master);
			return true;

		case '2':
			game_master.initializeGame(1, board, log, game_master); // Calls the initialization function of the "Game" class and passes that 1 player plays (vs. Computer)
			board.displayBoard(game_master);
			return true;

		case '3':
			rules();
			break;

		default:
			std::cout << "Invalid input! [Please enter 0, 1, 2, or 3]" << std::endl;
			std::cout << std::endl;
			std::cout << "------------------------------------------------" << std::endl;
			std::cout << std::endl;
			continue;
		}
	}
}

// Displays winner etc. and contains the option to view the log file
bool postGameScreen(std::string winner, int points, LogFile &log)
{ // Returns true for a desired rematch

	switch (points)
	{
	case 32:
		std::cout << std::endl;
		std::cout << "-----------------------------------" << std::endl;
		std::cout << std::endl;
		std::cout << "With 32 points each, the game ends in a draw!" << std::endl;
		std::cout << std::endl;
		std::cout << "-----------------------------------" << std::endl;
		std::cout << std::endl;
		break;

	default:
		std::cout << std::endl;
		std::cout << "-----------------------------------" << std::endl;
		std::cout << std::endl;
		std::cout << "With " << points << " points, the winner is " << winner << "!" << std::endl;
		std::cout << std::endl;
		std::cout << "-----------------------------------" << std::endl;
		std::cout << std::endl;
		break;
	}

	while (true)
	{ // To repeat on incorrect input

		std::cout << "Would you like to view the log file? [Y/N]" << std::endl;
		char input;
		std::cin >> input;
		std::cout << std::endl;
		std::cin.ignore();

		switch (input)
		{
		case 'Y':
		case 'y':
			std::cout << "Opening log file..." << std::endl;
			std::cout << "--------------------------------------------" << std::endl;
			std::cout << std::endl;

			log.displayLog(); // Calls the log file display

			std::cout << std::endl;
			std::cout << "--------------------------------------------" << std::endl;

			log.~LogFile(); // Calls the destructor of the logFile class since we no longer need it

			break;

		case 'N':
		case 'n':
			break;

		default:
			std::cout << "Invalid input, please enter 'Y' for Yes or 'N' for No." << std::endl;
			std::cout << std::endl;
			continue;
		}

		break;
	}

	std::cout << std::endl;

	while (true)
	{ // To loop back on case default
		std::cout << "Would you like to play again? [Y/N]" << std::endl;
		char input;
		std::cin >> input;
		std::cout << std::endl;
		std::cin.ignore();

		switch (input)
		{
		case 'Y':
		case 'y':
			std::cout << "Starting a new game." << std::endl;
			std::cout << std::endl;
			std::cout << "--------------------------------------------" << std::endl;
			std::cout << std::endl;
			return true;

		case 'N':
		case 'n':
			std::cout << "The game will end, see you next time!" << std::endl;
			return false;

		default:
			std::cout << "Invalid input, please enter 'Y' for Yes or 'N' for No." << std::endl;
			std::cout << std::endl;
			continue;
		}
	}
	system("clear");
}

int main()
{
	srand(time(0)); // since we will need a random generator later

	while (true)
	{

		Board board(true);
		LogFile log;
		GameMaster game_master;

		if (!(menu(game_master, log, board))) // If "end game" is selected in the menu, menu returns false, and the while loop is exited
			break;

		bool Player1Wins = determineWinner(board); // Stores whether Player1 won

		if (!(postGameScreen(game_master.returnName(Player1Wins), countPoints(Player1Wins, board), log)))
		{ // If a new game is not started, the while loop is exited
			break;
		}
	}
}