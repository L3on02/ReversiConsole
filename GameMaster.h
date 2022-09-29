#pragma once
#include <iostream>
#include <string>
using namespace std;

class Brett;
class logFile;
class Computer;

class GameMaster {
public:
	GameMaster();

	void Game(Brett &brett, logFile& log, GameMaster& GM); // Steuert den Spielverlauf

	void initializeGame(int PlayerCount, Brett& brett, logFile &log, GameMaster& GM); // Lässt den Spieler die Spieleigenschaften festlegen

	string nameInput(int player); // Liest den Namen eines Spielers ein

	string returnName(bool player1); // gibt den Gewünschten Namen aus

	bool boolTestspiel(); // fragt ob testspiel gewünscht ist

private:
	string mPlayer1Name;
	string mPlayer2Name;
	bool mTestSpiel = false; // Speichert ob ein Testspiel gestartet werden soll
	bool mVsComputer = false; // Speichert ob Spieler 2 ein Computer seien soll
};
