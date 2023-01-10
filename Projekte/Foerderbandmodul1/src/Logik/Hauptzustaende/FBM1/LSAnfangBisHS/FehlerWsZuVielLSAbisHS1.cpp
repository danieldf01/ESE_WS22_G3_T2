/*
 * FehlerWsZuVielLSAbisHS.cpp
 *
 *  Created on: 14.12.2022
 *      Author: Daniel Drefs Fernandes
 */

#include "FehlerWsZuVielLSAbisHS1.h"

using namespace std;

void FehlerWsZuVielLSAbisHS1::entry(){
	actions->fehlerHoch();
	actions->HSleeren();
	cout << "[FEHLER] Auf Foerderbandmodul 1 wurde ein unerwarteter Stoerfaktor (evtl. ein Werkstueck) erkannt." << endl;
	cout << "Bitte entfernen Sie den Stoerfaktor und/oder alle Werkstuecke zwischen der Lichtschranke am Anfang und dem Hoehensensor." << endl;
}

void FehlerWsZuVielLSAbisHS1::exit(){

}

void FehlerWsZuVielLSAbisHS1::WSinLSAbisHS(){

}

void FehlerWsZuVielLSAbisHS1::HSaktiv(){

}

void FehlerWsZuVielLSAbisHS1::quittiert(){
	exit();
	new (this) QuittiertZuVielLSAbisHS1;
	entry();
}

void FehlerWsZuVielLSAbisHS1::keinFehler(){

}

void FehlerWsZuVielLSAbisHS1::Fverschwunden(){

}

void FehlerWsZuVielLSAbisHS1::eStop(){
	actions->eStop();
	new (this) WartenLSAbisHS1;
}
