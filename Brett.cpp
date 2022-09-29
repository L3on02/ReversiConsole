/*
Zweck: Spielbrett mit allen benötigten Funktionen zur Überprüfung möglicher Züge und Einhaltung der Regeln
Autor: Adrian Spindler, Elias Reichert, Leon Maag
Datum: 17.01.22
*/

#include "Brett.h"
#include "GameMaster.h"
#include "LogFile.h"
#include "Computer.h"

using namespace std;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

Brett::Brett(bool Player1) {	// Konstruktor
		mPlayer1 = Player1;
}


bool Brett::CompleteMove(logFile &log, GameMaster &GM) { // Ruft die einzelnen Unterfunktionen auf, welche alle zusammen einen vollständigen Spielzug darstellen
	
	if (moveNotPossible < 2) {
		if (CheckForMoves() == 0) {
			moveNotPossible += 1; // Wenn moveNotPossible 2 erreicht, soll das Spiel abbrechen und die Steine sollen ausgezählt werden
			system("cls");
			cout << "Keine moeglichen Zuege, der naechste Spieler ist dran" << endl;
		}
		else {
			moveNotPossible = 0; // Sobald einer der beiden Spieler ein Zug machen kann wird der Zähler zurückgesetzt, da nur 2 "nicht" Züge in Folge relevant sind

			BrettAusgabe(GM);

			int eingabe = getPosition();
			
			mIndexLastMove = eingabe; // ermöglicht die Hervorhebung des letzten Zuges

			system("cls");

			makeMove(eingabe, log, GM);

			RevertHighlights();

			CheckForFlips(eingabe);

		}

		NextPlayer();

		return true;
	}
	mIndexLastMove = 99; // Damit auf der letzten Ausgabe des vollständigen Bretts keine hervorhebung mehr ist
	return false;
}


bool Brett::PcMove(Brett &brett, Computer &computer, logFile &log, GameMaster &GM) {
	if (moveNotPossible < 2) {
		if (CheckForMoves() == 0) {
			moveNotPossible += 1; // Wenn moveNotPossible 2 erreicht, soll das Spiel abbrechen und die Steine sollen ausgezählt werden
			system("cls");
			cout << "Keine mogelichen Zuege, der naechste Spieler ist dran" << endl;
		}
		else {
			moveNotPossible = 0; // Sobald einer der beiden Spieler ein Zug machen kann wird der Zähler zurückgesetzt, da nur 2 "nicht" Züge in Folge relevant sind
			
			BrettAusgabe(GM);

			Sleep(1500); // Simuliert "Nachdenken" des Computers und lässt dem Spieler Zeit, das Feld und die Möglichen Züge des Computers sehen

			int eingabe = computer.computerMove(brett);
			
			mIndexLastMove = eingabe; // ermöglicht die Hervorhebung des letzten Zuges
			
			system("cls");

			makeMove(eingabe, log, GM);

			RevertHighlights();

			CheckForFlips(eingabe);
			
		}

		NextPlayer();

		return true;
	}
	mIndexLastMove = 99; // Damit auf der letzten Ausgabe des vollständigen Bretts keine Hervorhebung mehr ist
	return false;
}


void Brett::RevertHighlights() { // Setzt die hervorgehobenen möglichen Züge im Spielfeld zurück
	for (int i = 0; i < mZeilen; i++) {
		for (int j = 0; j < mSpalten; j++) {
			int index = i * mSpalten + j;
			if (mSpielbrett[index] == 3)
				mSpielbrett[index] = 0;
		}
	}
}


void Brett::NextPlayer() { // Wechselt den aktuellen Spieler
	if (mPlayer1)
		mPlayer1 = false;
	else
		mPlayer1 = true;
}

int Brett::countPoints(int player) {
	int points = 0;
	for (int i = 0; i < 100; i++) {
		if (mSpielbrett[i] == player)
			points += 1;
	}
	return points;
}


void Brett::TestSpielBrett() {

	cout << endl;
	cout << "Welches Spielbrett moechten Sie nutzen? (Eingabe 1 - 5, ansonsten Zufaellig)" << endl;
	cout << " > ";
	char x;
	cin >> x;
	cin.ignore();

	switch (x) {
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
		break;
	default:
		x = rand() % 5 + 1;
		break;
	}

	switch (x) { // Wählt eines der 5 verfügbaren Spielbretter aus
	case '1':
		for (int i = 0; i < 100; i++) {
			mSpielbrett[i] = mTestSpielBrett1[i];
		}
		cout << "--------------------------------------------" << endl;
		cout << "Testspielbrett 1 wurde ausgewaehlt" << endl;
		cout << "--------------------------------------------" << endl;
		break;

	case '2':
		for (int i = 0; i < 100; i++) {
			mSpielbrett[i] = mTestSpielBrett2[i];
		}
		cout << "--------------------------------------------" << endl;
		cout << "Testspielbrett 2 wurde ausgewaehlt" << endl;
		cout << "--------------------------------------------" << endl;
		break;

	case '3':
		for (int i = 0; i < 100; i++) {
			mSpielbrett[i] = mTestSpielBrett3[i];
		}
		cout << "--------------------------------------------" << endl;
		cout << "Testspielbrett 3 wurde ausgewaehlt" << endl;
		cout << "--------------------------------------------" << endl;
		break;

	case '4':
		for (int i = 0; i < 100; i++) {
			mSpielbrett[i] = mTestSpielBrett4[i];
		}
		cout << "--------------------------------------------" << endl;
		cout << "Testspielbrett 4 wurde ausgewaehlt" << endl;
		cout << "--------------------------------------------" << endl;
		break;

	case '5':
		for (int i = 0; i < 100; i++) {
			mSpielbrett[i] = mTestSpielBrett5[i];
		}
		cout << "--------------------------------------------" << endl;
		cout << "Testspielbrett 5 wurde ausgewaehlt" << endl;
		cout << "--------------------------------------------" << endl;
		break;
	}

	Sleep(1200);
	system("cls");
}

void Brett::returnBrett(int *copySpielbrett) {
	for (int i = 0; i < 100; i++) {
		copySpielbrett[i] = mSpielbrett[i];
	}
}


/*
 Farben:
 mit: SetConsoleTextAttribute(hConsole, "Farbecode");
 4  -> Hellrot
 5  -> Orange
 6  -> Blau
 7  -> Weiß
 2  -> Grün
 0  -> Schwarz
 15 -> Bright White
 */

void Brett::BrettAusgabe(GameMaster& GM) {
	// system("cls");
	int zaehler = 0;
	int number = 1;
	
	cout << endl;
	if (mPlayer1) { // Gibt Spieler in Farbe aus
		SetConsoleTextAttribute(hConsole, 6);
		cout << "  ---------- " << setw(6) << left << GM.returnName(true) << " ----------" << endl;
		cout << endl;
	}
	else {
		SetConsoleTextAttribute(hConsole, 5);
		cout << "  ---------- " << setw(6) << left << GM.returnName(false)  << " ----------" << endl;
		cout << endl;
	}

	if (mIndexLastMove == 99) { // löscht die Ausgabe des Names bei der Ausgabe des Bretts am Spielende
		system("cls");
	}

	SetConsoleTextAttribute(hConsole, 7);

	cout << "   ";

	for (int a = 65; a <= 72; a++) {
		cout << right << " " << setw(1) << char(a) << " ";

	}
	cout << endl;

	for (int i = 0; i < mZeilen; i++) {

		for (int j = 0; j < mSpalten; j++) {

			int index = i * mSpalten + j;

			if ((index == mIndexLastMove) && (index != 0) && (index != 99)) {
				SetConsoleTextAttribute(hConsole, 4); // Hebt den letzten Zug des jeweilig anderen rot hervor
			}
			else {
				
				switch (mSpielbrett[index]) {
				case 1:
					SetConsoleTextAttribute(hConsole, 6);
					break;
					
				case 2:
					SetConsoleTextAttribute(hConsole, 5);
					break;

				case 3:
					SetConsoleTextAttribute(hConsole, 2);
					break;

				default:
					SetConsoleTextAttribute(hConsole, 15);
					break;
				}
			}

			switch (mSpielbrett[index]) {
			case 0:
				cout << right << setw(1) << "|";
				
				SetConsoleTextAttribute(hConsole, 0);
				cout << mSpielbrett[index];
				SetConsoleTextAttribute(hConsole, 7);
				
				cout << "|";
				break;

			case 1:
				cout << right << setw(1) << "|X|";
				break;

			case 2:
				cout << right << setw(1) << "|O|";
				break;
			
			case 3:
				cout << right << setw(1) << "|+|";
				break;

			case 4:
				cout << right << setw(1) << "   ";
				break;

			default:
				break;
			}

			zaehler++;

			if (zaehler == 10) {

				if (number > 1 && number < 10)
					cout << " " << number - 1 << endl;
				else
					cout << "  " << endl;

				number++;
			}
		}

		zaehler = 0;
	}

	number = 1;
}


void Brett::HighlightPossibleMoves(int index) {
	if (mSpielbrett[index] == 0)
		mSpielbrett[index] = 3;
}


int Brett::FieldCheck(int index, int direction) {
	
	switch (mSpielbrett[index + direction]) {
	case 0:
		if (mCounter >= 1) {
			mCounter = -1;
			HighlightPossibleMoves(index + direction);
			break; // möglicher Zug
		}
		mCounter = 0;
		break; // kein möglicher Zug

	case 1:
		if (mPlayer1) {	// dreht case 1 / 2 um jenachdem ob Spieler 1 am Zug ist
			break;
		}
		else {
			mCounter++;
			FieldCheck((index + direction), direction);
			break;
		}

	case 2:
		if (mPlayer1) {
			mCounter++;
			FieldCheck((index + direction), direction);
			break;
		}
		else {
			break;
		}

	default:
		mCounter = 0;
		break;
	}

	return mCounter;
}


void Brett::Flip(int index, int direction, int amount) {
	if (mPlayer1) {
		for (int i = 1; i <= amount; i++) {
			mSpielbrett[index + (i * direction)] = 1; // dreht alle in der übergebenen Richtung für den aktuellen Spieler gespeichert in bool mPlayer1
		}
	}
	else {
		for (int i = 1; i <= amount; i++) {
			mSpielbrett[index + (i * direction)] = 2; // dreht alle in der übergebenen Richtung für den aktuellen Spieler gespeichert in bool mPlayer1
		}
	}
}


void Brett::CheckForFlips(int index) {
	
	for (int n = 0; n < 8; n++) {
		mCounter = 1;
		CheckForFlipsRek(index, ArrayForDirection[n]);
	}
	mCounter = 0;
}


void Brett::CheckForFlipsRek(int index, int direction) {

	switch (mSpielbrett[index + direction]) {

	case 1:
		if (mPlayer1) {	// dreht case 1 / 2 um jenachdem ob Spieler 1 am Zug ist
			Flip(index - ((mCounter - 1) * direction), direction, mCounter);
			break;
		}
		else {
			mCounter++;
			CheckForFlipsRek((index + direction), direction);
			break;
		}

	case 2:
		if (mPlayer1) {
			mCounter++;
			CheckForFlipsRek((index + direction), direction);
			break;
		}
		else {
			Flip(index - ((mCounter - 1) * direction), direction, mCounter);
			break;
		}

	default:
		break;
	}
}


int Brett::CheckForMoves() {
	int numberOfPossibleMoves = 0;
	int whichPlayer;

	if (mPlayer1) {  // Ließt aus mPlayer1 wer gerade am Zug ist und weißt whichPlayer die entsrpechende Zahl (1 oder 2) zu
		whichPlayer = 1;
	}
	else {
		whichPlayer = 2;
	}

	for (int i = 1; i < mZeilen - 1; i++) { // -1, da die vierer (Rand) erst später relevant sind und deshalb ignoriert werden 

		for (int j = 1; j < mSpalten - 1; j++) { // "
			int index = i * mSpalten + j;

			if (mSpielbrett[index] == whichPlayer) { // Sucht nach Feldern

				for (int n = 0; n < 8; n++) {
					mCounter = 0;
					int x = FieldCheck(index, ArrayForDirection[n]); // in x wird gleichzeitig durch x = -1||0 übergeben ob der Zug möglich ist,
																	 // oder durch x > 0 wie Viele Steine in der gegebenen Richtung umgedreht werden müssen

					switch (x) {
					case -1: // möglicher Zug
						numberOfPossibleMoves += 1;
						break;

					case 0: // kein Möglicher Zug
						break;

					default:
						break;
					}
				}
			}
		}
	}

	return numberOfPossibleMoves;
}


int Brett::getPosition() {
	
	int spalte = 0;
	string feld;
	
	while (true) {

		// hole Nutzereingabe
		cout << " Geben Sie eine Feldposition ein:\n";
		cout << "  > ";
		
		getline(cin, feld);
		cout << endl;

			// Prüfe Nutzereingabe
				// prüft ob Eingabe 2zeichen lang ist
		if (feld.length() != 2) {
			cout << "Anzahl zeichen fehlerhaft\n";
			errorFalscheingabe();
			continue;
		}
		
		switch (feld[0]) { // Prüft erstes zeichen der Eingabe, Wandelt Buchstaben in Spaltennummer um
		case 'A':
		case 'a':
			spalte = 1;
			break;
		
		case 'B':
		case 'b':
			spalte = 2;
			break;
		
		case 'C':
		case 'c':
			spalte = 3;
			break;
		
		case 'D':
		case 'd':
			spalte = 4;
			break;
		
		case 'E':
		case 'e':
			spalte = 5;
			break;
		
		case 'F':
		case 'f':
			spalte = 6;
			break;
		
		case 'G':
		case 'g':
			spalte = 7;
			break;
		
		case 'H':
		case 'h':
			spalte = 8;
			break;	// Eingegebene Spalte akzeptiert, switch case wird beendet
		
		default:
			cout << "Spalte fehlerhaft\n";
			errorFalscheingabe();
			continue;  // keine gültige Eingabe, kehrt zurück zum Beginn der while-schleife
		}

		switch (feld[1]) { // Prüft zweites Zeichen der eingabe
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
			break;	// Eingegebene Spalte akzeptiert, switch case wird beendet
		default:
			cout << "Zeile Fehlerhaft\n";
			errorFalscheingabe();
			continue;	// keine gültige Eingabe, kehrt zurück zum Beginn der while-schleife
		}

		int index = spalte + 10 * (feld[1] - 48);

		if (mSpielbrett[index] == 3) {
			cout << "Eingabe erfolgreich" << endl;
			return (index);
		}
		else {
			cout << "Der eingegebene Zug ist nicht Regelkonform" << endl;
			cout << "Bitte waehlen Sie eines der in gruen hervorgehobenen Felder" << endl;
			continue;
		}
	}
}


void Brett::makeMove(int index, logFile &log, GameMaster &GM) {
	
	if (mPlayer1) {
		mSpielbrett[index] = 1;
	}
	else {
		mSpielbrett[index] = 2;
	}

	int x = index % 10; // Rechnet den Index zurück in Reihen und Spalten
	char reihe = ' ';

	switch (x) {
	case 1:
		reihe = 'A';
		break;
	case 2:
		reihe = 'B';
		break;
	case 3:
		reihe = 'C';
		break;
	case 4:
		reihe = 'D';
		break;
	case 5:
		reihe = 'E';
		break;
	case 6:
		reihe = 'F';
		break;
	case 7:
		reihe = 'G';
		break;
	case 8:
		reihe = 'H';
		break;
	}
	int spalte = index / 10;

	cout << "Gegnerischer Zug: " << reihe << spalte << endl;

	log.writeToLog(mPlayer1, reihe, spalte, GM); // schreibt den aktuellen Zug in die Log Datei
}


void Brett::errorFalscheingabe() {
	cout << "Geben sie Felder in folgender Form ein: Buchstabe fuer die Spalte, Zahl fuer die Zeile\n";
	cout << "Beispiel: \"A3\" fuer Spalte 1 - Reihe 3" << endl;
	cout << endl;
}