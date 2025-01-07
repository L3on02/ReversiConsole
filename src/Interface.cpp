#include "Interface.h"
#include "Controller.h"
#include <unistd.h>

std::string Interface::getColorCode(int id)
{
    switch (id)
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

Interface::Interface(Controller *controller) : m_controller(controller) {}

void Interface::showRules()
{
    system("clear");
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
int Interface::showMenu()
{
    if (m_first_load)
    {
        m_first_load = false;
        system("clear");
        std::cout << std::endl;
        std::cout << "-----------------------------------" << std::endl;
        std::cout << std::endl;
        std::cout << "Welcome to Reversi!!!" << std::endl;
        std::cout << std::endl;
        std::cout << "-----------------------------------" << std::endl;
        std::cout << std::endl;
    }

    while (true)
    {
        std::cout << "Please select the desired game mode: " << std::endl;
        std::cout << std::endl;
        std::cout << "    (1) -> Player vs Computer " << std::endl;
        std::cout << "    (2) -> Player vs Player " << std::endl;
        std::cout << "    (3) -> Display game rules " << std::endl;
        std::cout << std::endl;
        std::cout << "To exit, enter any other key " << std::endl;

        char selection;
        std::cout << " > ";
        std::cin >> selection;
        std::cout << std::endl;
        std::cin.ignore();

        switch (selection)
        {
        case '1':
            std::cout << "Starting a game against the computer..." << std::endl;
            sleep(0.5);
            system("clear");
            return 1;
        case '2':
            std::cout << "Starting a PvP game..." << std::endl;
            sleep(0.5);
            system("clear");
            return 2;
        case '3':
            showRules();
            break;

        default:
            std::cout << "The game will be closed!" << std::endl;
            std::cout << std::endl;
            return 0;
        }
    }
}

bool Interface::queryPlayAgain()
{
    while (true)
    {
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
            sleep(0.5);
            system("clear");
            return true;

        case 'N':
        case 'n':
            std::cout << "The game will end, see you next time!" << std::endl;
            return false;

        default:
            system("clear");
            std::cout << "Invalid input, please enter 'Y' for Yes or 'N' for No." << std::endl;
            std::cout << std::endl;
            continue;
        }
    }
}

std::string Interface::nameInput(int player)
{
    std::cout << std::endl
              << "Player " << player << ", please enter your name: " << std::endl
              << " > ";

    std::string name;
    getline(std::cin, name);
    
    system("clear");
    return name;
}

// Displays winner etc. and contains the option to view the log file
void Interface::showResultScreen(std::pair<int, int> points)
{
    std::cout << std::endl
              << "-----------------------------------" << std::endl
              << std::endl;

    int points_player1 = points.first;
    int points_player2 = points.second;

    if (points_player1 == points_player2)
        std::cout << "With " << points_player1 << " points each, the game ends in a draw!" << std::endl;
    else
    {
        bool player1_wins = points_player1 > points_player2;
        std::string winner = m_controller->returnName(player1_wins);
        int winning_points = player1_wins ? points_player1 : points_player2;

        std::cout << "With " << winning_points << " points, the winner is " << winner << "!" << std::endl;
    }
    std::cout << std::endl
              << "-----------------------------------" << std::endl
              << std::endl;
}

int Interface::getPlayerMove(bool previously_false)
{
    if (previously_false)
    {
        printError(2);
    }
    std::string field;
    while (true)
    {
        std::cout << " Enter a field position:\n";
        std::cout << "  > ";
        getline(std::cin, field);
        std::cout << std::endl;

        if (field.length() != 2)
        {
            std::cout << "Number of characters incorrect\n";
            printError(1);
            continue;
        }

        char colChar = toupper(field[0]);
        int row = field[1] - '0';

        if (colChar < 'A' || colChar > 'H' || row < 1 || row > 8)
        {
            std::cout << "Invalid input\n";
            printError(1);
            continue;
        }

        int col = colChar - 'A' + 1;
        return col + 10 * row;
    }
}

void Interface::printError(int id)
{
    switch (id)
    {
    case 1:
        std::cout << "Enter fields in the following form: Letter for the column, number for the row "<< std::endl;
        std::cout << "Example: \"A3\" for column 1 - row 3" << std::endl<< std::endl;
        break;
    case 2:
        std::cout << "The entered move is not rule-compliant" << std::endl;
        std::cout << "Please choose one of the fields highlighted in green" << std::endl<< std::endl;
        break;
    default:
        break;
    }
}

int Interface::showSelectBoard()
{
    system("clear");
    std::cout << std::endl;
    std::cout << "Which game board would you like to use? (enter 0 for default board or 1-5 for test boards)" << std::endl;
    std::cout << " > ";
    char x;
    std::cin >> x;
    std::cin.ignore();

    return x - '0';
}

void Interface::displayBoard(int board[], bool is_player1, bool game_end)
{
    system("clear");
    int counter = 0;
    int number = 1;

    if (!game_end)
    {
        std::cout << std::endl;
        // Displays player in color
        std::cout << (is_player1 ? getColorCode(6) : getColorCode(5)) << "  ---------- " << std::setw(6) << std::left << m_controller->returnName(is_player1) << " ----------" << std::endl
                  << std::endl;
    }

    std::cout << getColorCode(7) << "   ";

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
            switch (board[index])
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

            switch (board[index])
            {
            case 0:
                std::cout << std::right << std::setw(1) << "|";

                std::cout << getColorCode(0);
                std::cout << board[index];
                std::cout << getColorCode(7);

                std::cout << "|";
                break;
            case 5: // Highlight last move
                std::cout << getColorCode(4);
            case 1:
                std::cout << std::right << std::setw(1) << "|X|";
                break;
            case 6: // Highlight last move
                std::cout << getColorCode(4);
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
                    std::cout << number - 1 << std::endl;
                else
                    std::cout << " " << std::endl;
                number++;
            }
        }
        counter = 0;
    }

    std::cout << getColorCode(7) << "   ";
    for (int a = 65; a <= 72; a++)
    {
        std::cout << std::right << " " << std::setw(1) << char(a) << " ";
    }
    std::cout << std::endl << std::endl;
}
