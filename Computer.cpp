/*
Zweck: Koodrinierung der Spielzüge des Computergegners
Autor: Adrian Spindler, Elias Reichert, Leon Maag
Datum: 17.01.22
*/

#include "Computer.h"
#include "Brett.h"

Computer::Computer() {
}
	

void Computer::leseBrett(Brett &brett) {

	brett.returnBrett(mCopySpielbrett);
}


int Computer::computerMove(Brett &brett) {
	leseBrett(brett);
	return determineBestMove();
}


int Computer::determineBestMove() {
	int indexBestMove = 0;
	int currentBestMove = -10; // eliminiert den unwahrscheinlichen Fall, dass der wenn der Computer nur einen Stein um einen Eckstein als möglichen Zug
							  // hat, er einen Stein auf den Rand setzt.

	// Der folgende Block sorgt dafür, dass immer wenn möglich eine Ecke besetzt wird, da diese wichtiger sind als jegliche Menge an umgedrehten Steinen
	if (mCopySpielbrett[18] == 3)
		return 18;
	else if (mCopySpielbrett[11] == 3)
		return 11;
	else if (mCopySpielbrett[88] == 3)
		return 88;
	else if (mCopySpielbrett[81] == 3)
		return 81;
	// Wenn keine Ecke besetzt werden kann, wählt der Computer den Zug aus, welcher am meisten Gegnerische Steine umdreht
	else {

		for (int j = 0; j < 100; j++) {

			if (mCopySpielbrett[j] == 3) {

				int currentMove = CheckForFlips(j);

				// Hierdruch wird der Computer "unberechenbar", da er bei mehreren gleichwertigen Zügen zufällig einen jener Züge auswählt
				if ((rand() % (2))) { // gibt zufällig 0 oder 1, also true oder false aus

					if (currentMove > currentBestMove) {
						indexBestMove = j;
						currentBestMove = currentMove;
					}
				}
				else {

					if (currentMove >= currentBestMove) {
						indexBestMove = j;
						currentBestMove = currentMove;
					}
				}
			}
		}
		return indexBestMove;
	}
}


int Computer::CheckForFlips(int index) {
	
	mCounterPc = 0;
	
	// eventuelle Gewichtung der Spielfelder
	
	// Steine die an die Ecken angrenzen sind suboptimal, da der Gegner dadurch die Möglichkeit hat einen Eckstein zu besetzten,
	// sie werden daher nur ausgewählt wenn kein anderer Zug möglich ist.
	switch (index) {
	case 12:
	case 21:
	case 22:
	case 17:
	case 27:
	case 28:
	case 71:
	case 72:
	case 82:
	case 77:
	case 78:
	case 87:
		return -9; // Durch die Rückgabe von -9 wird einer dieser Züge nur gewählt, wenn kein anderer Zug mit einem Flip oder mehr gefunden wird
	
	// Steine am Spielfeldrand sind "wertvoller" als Steine in der Mitte.
	case 13:
	case 14:
	case 15:
	case 16:
	case 31:
	case 41:
	case 51:
	case 61:
	case 38:
	case 48:
	case 58:
	case 68:
	case 83:
	case 84:
	case 85:
	case 86:
		mCounterPc = 2; // Der Counter für mögliche Flips startet bei 2 anstelle von 0, ihnen werden also bei der Berechnung für den
		break;				// bestmöglichem Zug, 2 zusätzliche virtuelle Flips hinzuaddiert.
	}
	

	for (int n = 0; n < 8; n++) {
		CheckForFlipsRek(index, ArrayForDirection[n]);
	}

	return mCounterPc;
}


void Computer::CheckForFlipsRek(int index, int direction) {

	switch (mCopySpielbrett[index + direction]) {

	case 1:
		mLokalCounter++;
		CheckForFlipsRek((index + direction), direction);
		break;

	case 2:
		mCounterPc += mLokalCounter;
		mLokalCounter = 0;
		break;

	default:
		mLokalCounter = 0;
		break;
	}
}