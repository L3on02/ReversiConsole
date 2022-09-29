#pragma once
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
class GameMaster;

class logFile {
public:
	logFile();

	~logFile();

	void openFile();

	void writeToLog(bool player1, char reihe, int spalte, GameMaster &GM);

	void displayLog();


private:
	ifstream mFileIn;
	ofstream mFileOut;
	int mZugNummer;
	string mLine;
};