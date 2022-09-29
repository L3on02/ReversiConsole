/*
Zweck: Speichern der Spielzüge in einer Datei und Ausgabe dieser Datei auf der Konsole
Autor: Adrian Spindler, Elias Reichert, Leon Maag
Datum: 17.01.22
*/

#include "LogFile.h"
#include "Brett.h"
#include "GameMaster.h"

using namespace std;

logFile::logFile() {

	mZugNummer = 1;
	openFile();
}

logFile::~logFile() {	// Schließt die LogDatei bei Aufruf

	mFileOut.close();
	cout << "log-Datei geschlossen" << endl;
}
	
void logFile::openFile() {
		
	mFileOut.open("log.txt");

	if (!mFileOut)
		cout << "Fehler beim oeffnen der Ausgabeatei 'log.txt'" << endl;
	else
		cout << "log-Datei wurde erfolgreich geoeffnet!" << endl;
}

void logFile::writeToLog(bool player1, char reihe, int spalte, GameMaster &GM) {

	if (player1) {
		mFileOut << setw(2) << right << mZugNummer << ". " << setw(8) << left << GM.returnName(true) << " macht Zug: " << reihe << spalte << endl;
	}
	else {
		mFileOut << setw(2) << right << mZugNummer << ". " << setw(8) << left << GM.returnName(false) <<" macht Zug: " << reihe << spalte << endl;
	}
	mZugNummer += 1;
}

void logFile::displayLog() {
	
	ifstream mFileIn("log.txt");

	while (getline(mFileIn, mLine)) {
		cout << mLine << endl;
	}
}