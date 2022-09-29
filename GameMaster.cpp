/*
Zweck: Auswahl der Spieleigenschaften und Koordinator des Spiels
Autor: Adrian Spindler, Elias Reichert, Leon Maag
Datum: 17.01.22
*/
#include "GameMaster.h"
#include "Brett.h"
#include "Computer.h"


GameMaster::GameMaster() {} // Konstruktor

void GameMaster::initializeGame(int PlayerCount, Brett& brett, logFile& log, GameMaster& GM) { // Initialiersiert alle wichtigen Werte und l‰sst den Spieler die Parameter f¸r das Spiel festlegen.
	
	mPlayer1Name = nameInput(1); // lieﬂt Namen von Spieler 1 ein

	if (PlayerCount == 2) {
		mPlayer2Name = nameInput(2); // lieﬂt im Fall Spieler gegen Spieler auch noch einen zweiten Namen ein
		mVsComputer = false;
	}
	else {
		mPlayer2Name = "Computer";
		mVsComputer = true;
	}

	mTestSpiel = boolTestspiel();

	system("cls");

	Game(brett, log, GM);
}

void GameMaster::Game(Brett& brett, logFile& log, GameMaster &GM) {
	
	if (mTestSpiel) {
		brett.TestSpielBrett();
	}


	if (! mVsComputer) {

		if ((rand() % (2))) { // entscheidet zuf‰llig ob Spieler 1 oder Spieler 2 beginnt
			brett.NextPlayer();
		}

		while (true) {
			if (brett.CompleteMove(log, GM))
				continue;
			break;
		}
	}
	else {
		Computer *computer = new Computer(); // Neues Objekt der Klasse Computer

		if ((rand() % (2))) { // entscheidet zuf‰llig ob Spieler 1 oder Spieler 2 beginnt
			while (true) {

				if (!brett.CompleteMove(log, GM))
					break;

				if (!brett.PcMove(brett, *computer, log, GM))
					break;
			}
		}
		else {
			brett.NextPlayer(); // Brett startet standartm‰ﬂig mit Spieler 1, deshalb muss hier ein Spielerwechsel erfolgen

			while (true) {

				if (!brett.PcMove(brett, *computer, log, GM))
					break;

				if (!brett.CompleteMove(log, GM))
					break;
			}
		}

		delete computer;
	}
	system("cls");
	cout << endl;
}

string GameMaster::returnName(bool player1) {
	if (player1)
		return mPlayer1Name;
	else
		return mPlayer2Name;
}

string GameMaster::nameInput(int player) {
	
	cout << endl;
	cout << "Spieler " << player << ", bitte geben Sie ihren Namen ein: " << endl;
	string name;
	cout << " > ";
	getline(cin, name);
	cout << endl;
	cout << "Sie haben \"" << name << "\" gewaehlt!" << endl;
	cout << endl;
	cout << "-----------------------------------" << endl;
	return name;
}

bool GameMaster::boolTestspiel() {
	while (true) {
		cout << endl;
		cout << "Moechten Sie das Spiel als Testspiel starten? -> [J(a) / N(ein)]" << endl;
		char eingabe;
		cin >> eingabe;
		cin.ignore();

		switch (eingabe) {
		case 'J':
		case 'j':
			return true;

		case 'N':
		case 'n':
			return false;

		default:
			cout << "Ungueltige Eingabe, bitte 'J' fuer Ja oder 'N' fuer Nein eingeben." << endl;
			cout << endl;
			continue;
		}
	}
}