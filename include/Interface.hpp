#ifndef INTERFACE_H
#define INTERFACE_H

#include <string>
#include <iostream>
#include <iomanip>

class Controller;

class Interface
{
public:
    Interface(Controller *controller);

    int showMenu();
    void showRules();

    std::string nameInput(int player);
    int showSelectBoard();

    void displayBoard(int board[], bool is_player1, bool game_end = false);
    int getPlayerMove(bool previously_false = false);

    bool queryPlayAgain();
    void showResultScreen(std::pair<int, int> points);

private:
    void printError(int id);
    std::string getColorCode(int id);

    const int m_rows = 10;
    const int m_cols = 10;

    bool m_first_load = true;

    Controller *m_controller;
};

#endif
