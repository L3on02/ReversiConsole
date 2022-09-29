/*
Zweck: Start Menü und Auswahl der Spieleigenschaften
Autor: Adrian Spindler, Elias Reichert, Leon Maag
Datum: 17.01.22
*/

#include <iostream>
#include <string>
#include <cstdlib> // für rand(), srand(), ...
#include <ctime>
#include "Brett.h"
#include "LogFile.h"
#include "GameMaster.h"
using namespace std;


bool menu(GameMaster& GM, logFile& log, Brett& brett);
void rules();
bool postGameScreen(string gewinner, int points, logFile &log);
int countPoints(bool player1, Brett& brett);
bool determineWinner(Brett& brett);


void main()
{
	srand(time(0)); // da wir später einen Zufallsgenerator benötigen

	while (true) {

		Brett *brett = new Brett(true); // Neues Objekt der Klasse Brett
		logFile *log = new logFile(); // Neues Objekt der Klasse logFile
		GameMaster *GM = new GameMaster(); // Neues Objekt der Klasse GameMaster
		
		if (!(menu(*GM, *log, *brett))) // Wenn im Menü der Punkt Spiel beenden gewählt wird, gibt Menu false zurück und die while Schleife wird abgebrochen
			break;

		bool Player1Wins = determineWinner(*brett); // Speichert ob Spieler1 gewonnen hat

		if (!(postGameScreen(GM->returnName(Player1Wins), countPoints(Player1Wins, *brett), *log))) { // Wenn nicht ein neues Spiel gestartet werden soll wird die while Schleife gebrochen

			delete brett; // löscht das Objekt der Klasse Brett
			delete GM; // löscht das Objekt der Klasse GameMaster
			break;
		}
		
		delete brett; // löscht das Objekt der Klasse Brett
		delete GM; // löscht das Objekt der Klasse GameMaster
		// ! delete log wird nicht benötigt, da wir den Konstruktor explizit in posGameScreen() aufrufen !
	}
}

// Zählt die Punkte aus Brett aus
int countPoints(bool player1, Brett& brett) {
	if (player1)
		return brett.countPoints(1);
	else
		return brett.countPoints(2);
}

// ermittelt durch Zählen der Punkte, welcher Spieler gewonnen hat.
bool determineWinner(Brett& brett) { // true -> Spieler 1 hat Gewonnen; false -> Spieler 2 hat gewonnen
	if (countPoints(true, brett) > countPoints(false, brett)) {
		return true;
	}
	else
		return false;
}

// das Menü lässt den gewünschten Spielmodus auswählen und ruft dann den "GameMaster" auf, welcher das eigentlichte Spiel steuert
bool menu(GameMaster &GM, logFile &log, Brett &brett) {
	system("cls");
	cout << endl;
	cout << "-----------------------------------" << endl;
	cout << endl;
	cout << "Herzlich Willkommen bei Reversi!!!" << endl;
	cout << endl;
	cout << "-----------------------------------" << endl;
	cout << endl;

	while (true) {
		cout << "Bitte die gewuenschte Spielweise auswaehlen: " << endl;
		cout << endl;
		cout << "	(1) -> Spieler gegen Spieler " << endl;
		cout << "	(2) -> Spieler gegen Computer " << endl;
		cout << "	(3) -> Anzeigen der Spielregeln " << endl;
		cout << endl;
		cout << "Zum beenden bitte '0' eingeben. " << endl;

		char auswahl1;
		cout << " > ";
		cin >> auswahl1;
		cout << endl;
		cin.ignore();

		if (auswahl1 == '0') {
			cout << "Das Spiel wird geschlossen!" << endl;
			cout << endl;
			return false;
		}

		system("cls");

		switch (auswahl1) {
		case '1':
			GM.initializeGame(2, brett, log, GM); // Ruft die Initialisierungsfunktion der Klasse "Game" auf und übergibt das 2 Spieler gegeneinander spielen
			brett.BrettAusgabe(GM);
			return true;

		case '2':
			GM.initializeGame(1, brett, log, GM); // Ruft die Initialisierungsfunktion der Klasse "Game" auf und übergibt das 1 Spieler spielt (vs. Computer)
			brett.BrettAusgabe(GM);
			return true;

		case '3':
			rules();
			break;

		default:
			cout << "Ungueltige Eingabe! [Bitte 0, 1, 2 oder 3 eingeben]" << endl;
			cout << endl;
			cout << "------------------------------------------------" << endl;
			cout << endl;
			continue;
		}
	}
}

// Gibt Gewinner etc. aus und enthält die Möglichkeit die LogDatei auszugeben
bool postGameScreen(string gewinner, int points, logFile &log) {  // Bei gewünschtem Rematch wird true zurückgegeben

	switch (points) {
	case 32:
		cout << endl;
		cout << "-----------------------------------" << endl;
		cout << endl;
		cout << "Mit jeweils 32 Punkten endet das Spiel mit einem Unentschieden!" << endl;
		cout << endl;
		cout << "-----------------------------------" << endl;
		cout << endl;
		break;

	default:
		cout << endl;
		cout << "-----------------------------------" << endl;
		cout << endl;
		cout << "Mit " << points << " Punkten ist der Gewinner " << gewinner << "!" << endl;
		cout << endl;
		cout << "-----------------------------------" << endl;
		cout << endl;
		break;
	}

	while (true) { // Damit bei falscher Eingabe wiederhohlt wird
		
		cout << "Moechten Sie die log-Datei einsehen? [J(a)/N(ein)]" << endl;
		char eingabe;
		cin >> eingabe;
		cout << endl;
		cin.ignore();

		switch (eingabe) {
		case 'J':
		case 'j':
			cout << "log-Datei wird geoeffnet..." << endl;
			cout << "--------------------------------------------" << endl;
			cout << endl;

			log.displayLog(); // Ruft die ausgabe der logDatei auf

			cout << endl;
			cout << "--------------------------------------------" << endl;

			log.~logFile(); // ruft den Destruktor der Klasse logFile auf, da wir sie nun nicht mehr benötigen

			break;

		case 'N':
		case 'n':
			break;

		default:
			cout << "Ungueltige Eingabe, bitte 'J' fuer Ja oder 'N' fuer Nein eingeben." << endl;
			cout << endl;
			continue;
		}

		break;
	}

	cout << endl;

	while (true) { // Damit case default wieder an den Anfang springt
		cout << "Moechten Sie nocheinmal Spielen?" << endl;
		char eingabe;
		cin >> eingabe;
		cout << endl;
		cin.ignore();

		switch (eingabe) {
		case 'J':
		case 'j':
			cout << "Neues Spiel wird gestartet." << endl;
			cout << endl;
			cout << "--------------------------------------------" << endl;
			cout << endl;
			return true;

		case 'N':
		case 'n':
			cout << "Spiel wird beendet, bis zum naechsten Mal!" << endl;
			return false;

		default:
			cout << "Ungueltige Eingabe, bitte 'J' fuer Ja oder 'N' fuer Nein eingeben." << endl;
			cout << endl;
			continue;
		}
	}
	system("cls");
}


void rules() {
	cout << endl;
	cout << "------------------------ Regeln ------------------------" << endl;
	cout << " - Es wird abwechselnd gespielt, der Start wird ausgelost." << endl;
	cout << " - Jede Person hat Steine in einer eigenen, zugeteilten Farbe." << endl;
	cout << " - Ein Stein muss auf einem leeren Feld platziert werden, das an ein Feld grenzt," << endl;
	cout << "   das mit einem Stein der anderen Farbe belegt ist (waagerecht, senkrecht oder Diagonal)." << endl;
	cout << " - Kann ein Spieler keinen Stein legen, ist der andere Spieler wieder am Zug." << endl;
	cout << " - Werden durch das Platzieren eines Steines eine oder mehrere Reihen an beiden Enden" << endl;
	cout << "   durch Steine der eigenen Farbe begrenzt, koennen alle dazwischen liegenden" << endl;
	cout << "   Steine der gegnerischen Farbe in die eigene Farbe umgewandelt(gedreht) werden." << endl;
	cout << " - Das Spiel ist zu Ende, wenn alle Felder belegt sind oder" << endl;
	cout << "   keiner der beiden Spieler einen Zug machen kann." << endl;
	cout << " - Gewonnen hat, wer am meisten Steine der eigenen Farbe besitzt " << endl;
	cout << "-------------------------------------------------------" << endl;
	cout << endl;
}