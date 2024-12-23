#include <iostream>
#include <string>
#include <cstdlib> // for rand(), srand(), ...
#include <ctime>

#include "Controller.h"

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

// The menu allows the selection of the desired game mode and then calls the "Controller," which controls the actual game
int menu()
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
		std::cout << "    (1) -> Player vs. Computer " << std::endl;
		std::cout << "    (2) -> Player vs. Player " << std::endl;
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
		case '0':
			std::cout << "The game will be closed!" << std::endl;
			std::cout << std::endl;
		case '1':
		case '2':
			return selection - '0';
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

bool queryPlayAgain()
{
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
}

int main()
{
	srand(time(0)); // since we will need a random generator later

	do
	{
		int selection = menu();

		if (selection == 0)
			break;

		Controller controller(selection);
		controller.startGame();

	} while (queryPlayAgain());

	return 0;
}