#include "Controller.h"
#include "Computer.h"
#include "Board.h"
#include "Interface.h"

Controller::Controller()
{
    m_interface = new Interface(this);
}

Controller::~Controller()
{
    delete m_interface;
}

void Controller::start()
{
    do
    {
        // Shows the menu and returns the number of players
        if (m_player_count = m_interface->showMenu(); m_player_count == 0)
            break;
        initializeGame();
        runGame();
        evaluateGame();

    } while (m_interface->queryPlayAgain());
}

std::string Controller::returnName(bool is_player_1)
{
    return is_player_1 ? m_player1_name : m_player2_name;
}

void Controller::initializeGame() // Initializes all important values and lets the player set the parameters for the game.
{
    m_player1_name = m_interface->nameInput(1); // reads the name of player 1

    if (m_player_count == 2)
    {
        m_player2_name = m_interface->nameInput(2); // reads the name of player 2 in case of player vs player
        m_is_vs_computer = false;
    }
    else
    {
        m_player2_name = "Computer";
        m_is_vs_computer = true;
    }
    
    int board_id = m_interface->showSelectBoard();
    m_board = new Board(board_id);

    if (m_is_vs_computer)
    {
        m_computer = new Computer(m_board);
    }
}

void Controller::runGame()
{
    int player;
    int move;
    while (!m_board->gameEnd())
    {
        player = m_board->getCurrentPlayer();

        int board[100];
        m_board->copyBoard(board, true);

        bool false_move = false;
        do
        {
            m_interface->displayBoard(board, player == 1);
            if (m_is_vs_computer && player == 2)
            {
                move = m_computer->computerSelectMove();
            }
            else
            {
                move = m_interface->getPlayerMove(false_move);
                false_move = true;
            }
        } while (!m_board->makeMove(move));
    }
}

void Controller::evaluateGame()
{
    int result_board[100];
    m_board->copyBoard(result_board, true);
    m_interface->displayBoard(result_board, true, true);

    m_interface->showResultScreen(m_board->countPoints());
    cleanUp();
}

void Controller::cleanUp()
{
    if (m_board)
    {
        delete m_board;
        m_board = nullptr;
    }

    if (m_computer)
    {
        delete m_computer;
        m_computer = nullptr;
    }
}
