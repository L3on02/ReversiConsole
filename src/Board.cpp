#include "Board.h"
#include "TestBoards.h"

#include <unistd.h>


bool Board::completeMove(LogFile &log, GameMaster &GM)
{ // Calls the individual sub-functions, which together represent a complete move

	if (m_move_not_possible < 2)
	{
		if (checkForMoves() == 0)
		{
			m_move_not_possible += 1; // If moveNotPossible reaches 2, the game should end and the stones should be counted
			system("clear");
			std::cout << "No possible moves, the next player is up" << std::endl;
		}
		else
		{
			m_move_not_possible = 0; // As soon as one of the players can make a move, the counter is reset, as only 2 "non" moves in a row are relevant

			displayBoard(GM);

			int eingabe = getPosition();

			m_index_last_move = eingabe; // enables highlighting of the last move

			system("clear");

			makeMove(eingabe, log, GM);

			revertHighlights();

			checkForFlips(eingabe);
		}

		nextPlayer();

		return true;
	}
	m_index_last_move = 99; // So that there is no highlighting on the last output of the complete board
	return false;
}

bool Board::computerMove(Board &brett, Computer &computer, LogFile &log, GameMaster &GM)
{
	if (m_move_not_possible < 2)
	{
		if (checkForMoves() == 0)
		{
			m_move_not_possible += 1; // If moveNotPossible reaches 2, the game should end and the stones should be counted
			system("clear");
			std::cout << "No possible moves, the next player is up" << std::endl;
		}
		else
		{
			m_move_not_possible = 0; // As soon as one of the players can make a move, the counter is reset, as only 2 "non" moves in a row are relevant

			displayBoard(GM);

			sleep(1.5); // Simulates "thinking" of the computer and gives the player time to see the field and the possible moves of the computer

			int eingabe = computer.computerMove(brett);

			m_index_last_move = eingabe; // enables highlighting of the last move

			system("clear");

			makeMove(eingabe, log, GM);

			revertHighlights();

			checkForFlips(eingabe);
		}

		nextPlayer();

		return true;
	}
	m_index_last_move = 99; // So that there is no highlighting on the last output of the complete board
	return false;
}

void Board::revertHighlights()
{ // Resets the highlighted possible moves on the board
	for (int i = 0; i < m_rows; i++)
	{
		for (int j = 0; j < m_cols; j++)
		{
			int index = i * m_cols + j;
			if (m_board[index] == 3)
				m_board[index] = 0;
		}
	}
}

void Board::nextPlayer()
{ // Switches the current player
	if (m_is_player_1)
		m_is_player_1 = false;
	else
		m_is_player_1 = true;
}

int Board::countPoints(int player)
{
	int points = 0;
	for (int i = 0; i < 100; i++)
	{
		if (m_board[i] == player)
			points += 1;
	}
	return points;
}

void Board::testBoard()
{

	std::cout << std::endl;
	std::cout << "Which game board would you like to use? (Enter 1 - 5, otherwise random)" << std::endl;
	std::cout << " > ";
	char x;
	std::cin >> x;
	std::cin.ignore();

	switch (x)
	{
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
		break;
	default:
		x = rand() % 5 + 1;
		break;
	}

	switch (x)
	{ // Selects one of the 5 available game boards
	case '1':
		for (int i = 0; i < 100; i++)
		{
			m_board[i] = test_board_1[i];
		}
		break;

	case '2':
		for (int i = 0; i < 100; i++)
		{
			m_board[i] = test_board_2[i];
		}
		break;

	case '3':
		for (int i = 0; i < 100; i++)
		{
			m_board[i] = test_board_3[i];
		}
		break;

	case '4':
		for (int i = 0; i < 100; i++)
		{
			m_board[i] = test_board_4[i];
		}
		break;

	case '5':
		for (int i = 0; i < 100; i++)
		{
			m_board[i] = test_board_5[i];
		}
	}

	std::cout << "--------------------------------------------" << std::endl;
	std::cout << "Test game board " << x << " was selected" << std::endl;
	std::cout << "--------------------------------------------" << std::endl;

	sleep(1.2);
	system("clear");
}

void Board::returnBoard(int *copySpielbrett)
{
	for (int i = 0; i < 100; i++)
	{
		copySpielbrett[i] = m_board[i];
	}
}

void Board::displayBoard(GameMaster &GM)
{
	// system("clear");
	int counter = 0;
	int number = 1;

	std::cout << std::endl;
	if (m_is_player_1)
	{ // Displays player in color
		std::cout << getColorCode(6);
		std::cout << "  ---------- " << std::setw(6) << std::left << GM.returnName(true) << " ----------" << std::endl;
		std::cout << std::endl;
	}
	else
	{
		std::cout << getColorCode(5);
		std::cout << "  ---------- " << std::setw(6) << std::left << GM.returnName(false) << " ----------" << std::endl;
		std::cout << std::endl;
	}

	if (m_index_last_move == 99)
	{ // Clears the display of the name when displaying the board at the end of the game
		system("clear");
	}

	std::cout << getColorCode(7);

	std::cout << "   ";

	for (int a = 65; a <= 72; a++)
	{
		std::cout << std::right << " " << std::setw(1) << char(a) << " ";
	}
	std::cout << std::endl;

	for (int i = 0; i < m_rows; i++)
	{

		for (int j = 0; j < m_cols; j++)
		{

			int index = i * m_cols + j;

			if ((index == m_index_last_move) && (index != 0) && (index != 99))
			{
				std::cout << getColorCode(4); // Highlights the last move of the respective other player in red
			}
			else
			{

				switch (m_board[index])
				{
				case 1:
					std::cout << getColorCode(6);
					break;

				case 2:
					std::cout << getColorCode(5);
					break;

				case 3:
					std::cout << getColorCode(2);
					break;

				default:
					std::cout << getColorCode(15);
					break;
				}
			}

			switch (m_board[index])
			{
			case 0:
				std::cout << std::right << std::setw(1) << "|";

				std::cout << getColorCode(0);
				std::cout << m_board[index];
				std::cout << getColorCode(7);

				std::cout << "|";
				break;

			case 1:
				std::cout << std::right << std::setw(1) << "|X|";
				break;

			case 2:
				std::cout << std::right << std::setw(1) << "|O|";
				break;

			case 3:
				std::cout << std::right << std::setw(1) << "|+|";
				break;

			case 4:
				std::cout << std::right << std::setw(1) << "   ";
				break;

			default:
				break;
			}

			counter++;

			if (counter == 10)
			{

				if (number > 1 && number < 10)
					std::cout << " " << number - 1 << std::endl;
				else
					std::cout << "  " << std::endl;

				number++;
			}
		}

		counter = 0;
	}

	number = 1;
}

void Board::highlightPossibleMoves(int index)
{
	if (m_board[index] == 0)
		m_board[index] = 3;
}

int Board::fieldCheck(int index, int direction)
{

	switch (m_board[index + direction])
	{
	case 0:
		if (m_counter >= 1)
		{
			m_counter = -1;
			highlightPossibleMoves(index + direction);
			break; // possible move
		}
		m_counter = 0;
		break; // no possible move

	case 1:
		if (m_is_player_1)
		{ // flips case 1 / 2 depending on whether player 1 is up
			break;
		}
		else
		{
			m_counter++;
			fieldCheck((index + direction), direction);
			break;
		}

	case 2:
		if (m_is_player_1)
		{
			m_counter++;
			fieldCheck((index + direction), direction);
			break;
		}
		else
		{
			break;
		}

	default:
		m_counter = 0;
		break;
	}

	return m_counter;
}

void Board::flip(int index, int direction, int amount)
{
	if (m_is_player_1)
	{
		for (int i = 1; i <= amount; i++)
		{
			m_board[index + (i * direction)] = 1; // flips all in the given direction for the current player stored in bool mPlayer1
		}
	}
	else
	{
		for (int i = 1; i <= amount; i++)
		{
			m_board[index + (i * direction)] = 2; // flips all in the given direction for the current player stored in bool mPlayer1
		}
	}
}

void Board::checkForFlips(int index)
{

	for (int n = 0; n < 8; n++)
	{
		m_counter = 1;
		checkForFlipsRek(index, m_directions[n]);
	}
	m_counter = 0;
}

void Board::checkForFlipsRek(int index, int direction)
{

	switch (m_board[index + direction])
	{

	case 1:
		if (m_is_player_1)
		{ // flips case 1 / 2 depending on whether player 1 is up
			flip(index - ((m_counter - 1) * direction), direction, m_counter);
			break;
		}
		else
		{
			m_counter++;
			checkForFlipsRek((index + direction), direction);
			break;
		}

	case 2:
		if (m_is_player_1)
		{
			m_counter++;
			checkForFlipsRek((index + direction), direction);
			break;
		}
		else
		{
			flip(index - ((m_counter - 1) * direction), direction, m_counter);
			break;
		}

	default:
		break;
	}
}

int Board::checkForMoves()
{
	int numberOfPossibleMoves = 0;
	int whichPlayer;

	if (m_is_player_1)
	{ // Reads from mPlayer1 who is currently up and assigns the corresponding number (1 or 2) to whichPlayer
		whichPlayer = 1;
	}
	else
	{
		whichPlayer = 2;
	}

	for (int i = 1; i < m_rows - 1; i++)
	{ // -1, because the fours (edge) are only relevant later and are therefore ignored

		for (int j = 1; j < m_cols - 1; j++)
		{ // "
			int index = i * m_cols + j;

			if (m_board[index] == whichPlayer)
			{ // Searches for fields

				for (int n = 0; n < 8; n++)
				{
					m_counter = 0;
					int x = fieldCheck(index, m_directions[n]); // in x it is simultaneously passed whether the move is possible with x = -1||0,
																// or with x > 0 how many stones need to be flipped in the given direction

					switch (x)
					{
					case -1: // possible move
						numberOfPossibleMoves += 1;
						break;

					case 0: // no possible move
						break;

					default:
						break;
					}
				}
			}
		}
	}

	return numberOfPossibleMoves;
}

int Board::getPosition()
{

	int spalte = 0;
	std::string feld;

	while (true)
	{

		// get user input
		std::cout << " Enter a field position:\n";
		std::cout << "  > ";

		getline(std::cin, feld);
		std::cout << std::endl;

		// Check user input
		// checks if input is 2 characters long
		if (feld.length() != 2)
		{
			std::cout << "Number of characters incorrect\n";
			printError();
			continue;
		}

		switch (feld[0])
		{ // Checks first character of input, converts letters to column number
		case 'A':
		case 'a':
			spalte = 1;
			break;

		case 'B':
		case 'b':
			spalte = 2;
			break;

		case 'C':
		case 'c':
			spalte = 3;
			break;

		case 'D':
		case 'd':
			spalte = 4;
			break;

		case 'E':
		case 'e':
			spalte = 5;
			break;

		case 'F':
		case 'f':
			spalte = 6;
			break;

		case 'G':
		case 'g':
			spalte = 7;
			break;

		case 'H':
		case 'h':
			spalte = 8;
			break; // Entered column accepted, switch case ends

		default:
			std::cout << "Column incorrect\n";
			printError();
			continue; // invalid input, returns to the beginning of the while loop
		}

		switch (feld[1])
		{ // Checks second character of input
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
			break; // Entered column accepted, switch case ends
		default:
			std::cout << "Row incorrect\n";
			printError();
			continue; // invalid input, returns to the beginning of the while loop
		}

		int index = spalte + 10 * (feld[1] - 48);

		if (m_board[index] == 3)
		{
			std::cout << "Input successful" << std::endl;
			return (index);
		}
		else
		{
			std::cout << "The entered move is not rule-compliant" << std::endl;
			std::cout << "Please choose one of the fields highlighted in green" << std::endl;
			continue;
		}
	}
}

void Board::makeMove(int index, LogFile &log, GameMaster &GM)
{

	if (m_is_player_1)
	{
		m_board[index] = 1;
	}
	else
	{
		m_board[index] = 2;
	}

	int x = index % 10; // Converts the index back to rows and columns
	char reihe = ' ';

	switch (x)
	{
	case 1:
		reihe = 'A';
		break;
	case 2:
		reihe = 'B';
		break;
	case 3:
		reihe = 'C';
		break;
	case 4:
		reihe = 'D';
		break;
	case 5:
		reihe = 'E';
		break;
	case 6:
		reihe = 'F';
		break;
	case 7:
		reihe = 'G';
		break;
	case 8:
		reihe = 'H';
		break;
	}
	int spalte = index / 10;

	std::cout << "Opponent's move: " << reihe << spalte << std::endl;

	log.writeToLog(m_is_player_1, reihe, spalte, GM); // writes the current move to the log file
}

void Board::printError()
{
	std::cout << "Enter fields in the following form: Letter for the column, number for the row\n";
	std::cout << "Example: \"A3\" for column 1 - row 3" << std::endl;
	std::cout << std::endl;
}

std::string Board::getColorCode(int colorCode)
{
	switch (colorCode)
	{
	case 4:
		return "\033[31m"; // Bright Red
	case 5:
		return "\033[33m"; // Orange
	case 6:
		return "\033[34m"; // Blue
	case 7:
		return "\033[37m"; // White
	case 2:
		return "\033[32m"; // Green
	case 0:
		return "\033[30m"; // Black
	case 15:
		return "\033[97m"; // Bright White
	default:
		return ""; // Default no color
	}
}