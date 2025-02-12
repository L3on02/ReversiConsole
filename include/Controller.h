#ifndef GAMEMASTER_H
#define GAMEMASTER_H

#include <string>
#include <optional>

#include "Board.h"
#include "Computer.h"
#include "Interface.h"

class Controller
{
public:
    void start();
    std::string returnName(bool is_player_1);

private:
    void initializeGame();
    void runGame();
    void evaluateGame();

    void cleanUp();

    int m_player_count;
    bool m_is_vs_computer;
    
    std::string m_player1_name;
    std::string m_player2_name;

    Board *m_board = nullptr;
    Computer *m_computer = nullptr;
    Interface *m_interface = nullptr;
};

#endif
