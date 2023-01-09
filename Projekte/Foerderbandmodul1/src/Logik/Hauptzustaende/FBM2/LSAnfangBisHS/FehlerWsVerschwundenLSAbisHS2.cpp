/*
 * FehlerWsVerschwundenLSAbisHS.cpp
 *
 *  Created on: 14.12.2022
 *      Author: Daniel Drefs Fernandes
 */

#include "FehlerWsVerschwundenLSAbisHS2.h"

using namespace std;

void FehlerWsVerschwundenLSAbisHS2::entry(){
	actions->fehlerHoch();
	cout << "[FEHLER] Auf Foerderbandmodul 2 ist ein Werkstueck zwischen der Lichtschranke Anfang und dem Hoehensensor verschwunden." << endl;
	cout << "Bitte entfernen Sie alle Werkstuecke vom Foerderbandmodul 2." << endl;
	actions->entferneWsLSAbisHS();
}

void FehlerWsVerschwundenLSAbisHS2::exit(){

}

void FehlerWsVerschwundenLSAbisHS2::WSinLSAbisHS(){

}

void FehlerWsVerschwundenLSAbisHS2::HSaktiv(){

}

void FehlerWsVerschwundenLSAbisHS2::quittiert(){
	actions->schnellRunter();
	new (this) QuittiertVerschwundenLSAbisHS2;
	entry();
}

void FehlerWsVerschwundenLSAbisHS2::keinFehler(){

}

void FehlerWsVerschwundenLSAbisHS2::Fverschwunden(){

}

void FehlerWsVerschwundenLSAbisHS2::eStop(){
	actions->eStop();
	new (this) WartenLSAbisHS2;
}
