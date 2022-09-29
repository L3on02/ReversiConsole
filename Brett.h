#pragma once
#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <Windows.h>

using namespace std;

class GameMaster;
class logFile;
class Computer;

class Brett {
public:
	// Konstruktor
	Brett(bool Player1);

	// Macht einen Vollständigen Spielzug
	bool CompleteMove(logFile& log, GameMaster& GM);
	// Macht einen Vollständigen Computer Zug
	bool PcMove(Brett &brett, Computer &computer, logFile &log, GameMaster &GM);

	// Allgemeine Funktionen
	void NextPlayer();
	void BrettAusgabe(GameMaster &GM);
	void returnBrett(int *copySpielbrett);
	void makeMove(int index, logFile &log, GameMaster &GM);
	void RevertHighlights();
	int countPoints(int player);
	void TestSpielBrett();

	// Nach möglichen Zügen suchen
	int FieldCheck(int index, int direction);
	int CheckForMoves();
	void HighlightPossibleMoves(int index);

	// Steine Umdrehen
	void Flip(int index, int direction, int amount);
	void CheckForFlips(int index);
	void CheckForFlipsRek(int index, int direction);

	// Input
	int getPosition();
	void errorFalscheingabe();

private:
	const int mZeilen = 10;   // 10 Spalten und Zeilen, da wir einen "rand" um das Feld gezogen haben
	const int mSpalten = 10; 

	int mCounter = 0;  // Wichtig für CheckForMoves / CheckForFlips

	int moveNotPossible = 0; // Speichert Wie oft in Folge ein Spieler nicht konnte

	int mSpielbrett[100] = { // Das Startspielbrett, welches im Laufe des Spiels verändert wird.
	4,4,4,4,4,4,4,4,4,4,
	4,0,0,0,0,0,0,0,0,4,
	4,0,0,0,0,0,0,0,0,4,
	4,0,0,0,0,0,0,0,0,4,
	4,0,0,0,1,2,0,0,0,4,
	4,0,0,0,2,1,0,0,0,4,
	4,0,0,0,0,0,0,0,0,4,
	4,0,0,0,0,0,0,0,0,4,
	4,0,0,0,0,0,0,0,0,4,
	4,4,4,4,4,4,4,4,4,4,
	};

	int mTestSpielBrett1[100] = { // speichert ein Spielbrett, welches bereits vorangeschritten ist, um die Funktionen zu testen.
	4,4,4,4,4,4,4,4,4,4,
	4,0,0,1,0,2,2,0,0,4,
	4,0,0,1,2,2,2,0,0,4,
	4,1,1,2,2,2,1,1,1,4,
	4,2,2,2,2,2,1,1,0,4,
	4,2,2,1,2,2,1,1,1,4,
	4,2,2,2,1,2,1,1,1,4,
	4,0,0,1,1,2,1,0,0,4,
	4,0,0,2,2,2,1,0,0,4,
	4,4,4,4,4,4,4,4,4,4,
	};

	int mTestSpielBrett2[100] = { // speichert ein Spielbrett, welches bereits vorangeschritten ist, um die Funktionen zu testen.
	4,4,4,4,4,4,4,4,4,4,
	4,0,0,0,0,0,0,0,0,4,
	4,0,0,0,0,0,0,0,0,4,
	4,0,0,0,0,0,0,0,0,4,
	4,0,0,0,1,2,2,0,0,4,
	4,0,0,0,2,1,0,0,0,4,
	4,0,0,0,0,0,0,0,0,4,
	4,0,0,0,0,0,0,0,0,4,
	4,0,0,0,0,0,0,0,0,4,
	4,4,4,4,4,4,4,4,4,4,
	};

	int mTestSpielBrett3[100] = { // speichert ein Spielbrett, welches bereits vorangeschritten ist, um die Funktionen zu testen.
	4,4,4,4,4,4,4,4,4,4,
	4,0,0,0,0,0,0,0,0,4,
	4,0,0,0,0,0,0,0,0,4,
	4,0,0,0,0,0,0,0,0,4,
	4,0,0,0,1,2,2,2,0,4,
	4,0,0,0,2,1,0,0,0,4,
	4,0,0,0,0,0,0,0,0,4,
	4,0,0,0,0,0,0,0,0,4,
	4,0,0,0,0,0,0,0,0,4,
	4,4,4,4,4,4,4,4,4,4,
	};

	int mTestSpielBrett4[100] = { // speichert ein Spielbrett, welches bereits vorangeschritten ist, um die Funktionen zu testen.
	4,4,4,4,4,4,4,4,4,4,
	4,0,0,0,0,0,0,0,0,4,
	4,0,0,0,0,0,0,0,0,4,
	4,0,0,0,0,0,0,0,0,4,
	4,0,0,0,1,2,2,2,2,4,
	4,0,0,0,2,1,0,0,0,4,
	4,0,0,0,0,0,0,0,0,4,
	4,0,0,0,0,0,0,0,0,4,
	4,0,0,0,0,0,0,0,0,4,
	4,4,4,4,4,4,4,4,4,4,
	};

	int mTestSpielBrett5[100] = { // speichert ein Spielbrett, welches bereits vorangeschritten ist, um die Funktionen zu testen.
	4,4,4,4,4,4,4,4,4,4,
	4,1,1,1,1,1,1,1,1,4,
	4,1,1,1,1,1,1,1,1,4,
	4,1,1,1,1,1,1,1,1,4,
	4,1,1,1,1,1,1,1,1,4,
	4,2,2,2,2,2,2,2,2,4,
	4,2,2,2,2,2,2,2,2,4,
	4,2,2,2,2,2,2,2,2,4,
	4,2,2,2,2,2,2,2,2,4,
	4,4,4,4,4,4,4,4,4,4,
	};

	bool mPlayer1;

	int mIndexLastMove = 0; // Speichert den letzten Zug

	const int ArrayForDirection[8] = { // speichert die Richtungen oben links/mitte/rechts , links / rechs , unten links/mitte/rechts "index"+"ArrayForDirection"
	-11,-10,-9,-1,1,9,10,11
	};
};