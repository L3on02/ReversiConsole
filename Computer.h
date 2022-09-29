#pragma once
#include <string>
#include <iostream>

using namespace std;

class Brett;
class GameMaster;

class Computer {
public:
	Computer(); // Konstruktor

	int computerMove(Brett &brett);

	void leseBrett(Brett &brett);

	int determineBestMove();

	int CheckForFlips(int index);

	void CheckForFlipsRek(int index, int direction);

private:
	int mCopySpielbrett[100] = { 0 };
	
	int mLokalCounter = 0;
	
	int mCounterPc = 0;

	const int ArrayForDirection[8] = { // speichert die Richtungen oben links/mitte/rechts , links / rechs , unten links/mitte/rechts "index"+"ArrayForDirection"
	-11,-10,-9,-1,1,9,10,11
	};
};