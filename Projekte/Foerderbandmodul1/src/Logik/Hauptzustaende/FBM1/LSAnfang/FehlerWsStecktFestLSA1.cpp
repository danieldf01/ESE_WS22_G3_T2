/*
 * FWSstecktFest.cpp
 *
 *  Created on: 11.12.2022
 *      Author: Daniel
 */

#include "FehlerWsStecktFestLSA1.h"

using namespace std;

void FehlerWsStecktFestLSA1::entry() {
	actions->fehlerHoch();
	cout << "[FEHLER] Ein Werkstueck steckt auf Foerderbandmodul 1 in der Lichtschranke am Anfang fest, bitte leeren." << endl;
}

void FehlerWsStecktFestLSA1::exit() {

}

void FehlerWsStecktFestLSA1::LSan() {

}

void FehlerWsStecktFestLSA1::LSaus() {

}

void FehlerWsStecktFestLSA1::timerAbstand() {

}

void FehlerWsStecktFestLSA1::WSstecktFest() {

}

void FehlerWsStecktFestLSA1::quittiert() {
	exit();
	actions->schnellRunter();
	new (this) QuittiertLSA1;
	entry();
}

void FehlerWsStecktFestLSA1::keinFehler() {

}

void FehlerWsStecktFestLSA1::eStop(){
	actions->eStop();
	new (this) WarteAufWsLSA1;
}

