/*
 * FehlerWsVerschwundenLSAbisHS.cpp
 *
 *  Created on: 14.12.2022
 *      Author: Daniel Drefs Fernandes
 */

#include "FehlerWsVerschwundenLSAbisHS1.h"

using namespace std;

void FehlerWsVerschwundenLSAbisHS1::entry(){
	actions->fehlerHoch();
	cout << "[FEHLER] Auf Foerderbandmodul 1 ist ein Werkstueck zwischen der Lichtschranke Anfang und dem Hoehensensor verschwunden." << endl;
	cout << "Bitte entfernen Sie in diesem Bereich " << wsListen->ws_list_LSAnfang_bis_HS.size() << " Werkstueck(e)." << endl;
	actions->entferneWsLSAbisHS();
}

void FehlerWsVerschwundenLSAbisHS1::exit(){

}

void FehlerWsVerschwundenLSAbisHS1::WSinLSAbisHS(){

}

void FehlerWsVerschwundenLSAbisHS1::HSaktiv(){

}

void FehlerWsVerschwundenLSAbisHS1::quittiert(){
	exit();
	actions->schnellRunter();
	new (this) QuittiertVerschwundenLSAbisHS1;
	entry();
}

void FehlerWsVerschwundenLSAbisHS1::keinFehler(){

}

void FehlerWsVerschwundenLSAbisHS1::Fverschwunden(){

}

void FehlerWsVerschwundenLSAbisHS1::eStop(){
	actions->eStop();
	new (this) WartenLSAbisHS1;
	entry();
}
