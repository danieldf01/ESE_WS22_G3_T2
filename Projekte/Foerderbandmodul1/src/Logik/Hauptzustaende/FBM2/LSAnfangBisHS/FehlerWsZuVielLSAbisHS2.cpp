/*
 * FehlerWsZuVielLSAbisHS.cpp
 *
 *  Created on: 14.12.2022
 *      Author: Daniel Drefs Fernandes
 */

#include "FehlerWsZuVielLSAbisHS2.h"

using namespace std;

void FehlerWsZuVielLSAbisHS2::entry(){
	actions->fehlerHoch();
	cout << "[FEHLER] Auf Foerderbandmodul 2 wurde ein unerwarteter Stoerfaktor (evtl. ein Werkstueck) erkannt." << endl;
	cout << "Bitte entfernen Sie den Stoerfaktor und/oder alle Werkstuecke zwischen der Lichtschranke am Anfang und dem Hoehensensor." << endl;
}

void FehlerWsZuVielLSAbisHS2::exit(){

}

void FehlerWsZuVielLSAbisHS2::WSinLSAbisHS(){

}

void FehlerWsZuVielLSAbisHS2::HSaktiv(){

}

void FehlerWsZuVielLSAbisHS2::quittiert(){
	exit();
	new (this) QuittiertZuVielLSAbisHS2;
	entry();
}

void FehlerWsZuVielLSAbisHS2::keinFehler(){

}

void FehlerWsZuVielLSAbisHS2::Fverschwunden(){

}

void FehlerWsZuVielLSAbisHS2::eStop(){
	exit();
	actions->eStop();
	new (this) WartenLSAbisHS2;
	entry();
}
