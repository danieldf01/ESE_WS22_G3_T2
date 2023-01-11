/*
 * FehlerWsZuFruehLSAbisHS.cpp
 *
 *  Created on: 14.12.2022
 *      Author: Daniel Drefs Fernandes
 */

#include "FehlerWsZuFruehLSAbisHS1.h"

void FehlerWsZuFruehLSAbisHS1::entry(){
	actions->fehlerHoch();
	actions->HSleeren();
	cout << "[FEHLER] Auf Foerderbandmodul 1 wurde unter dem Hoehensensor ein Stoerfaktor erkannt (oder ein Werkstueck nach vorne geschoben)." << endl;
	cout << "Bitte entfernen Sie den Stoerfaktor oder das Werkstueck, das sich am naechsten am Hoehensensor (wahrscheinlich sogar darunter) befindet." << endl;
}

void FehlerWsZuFruehLSAbisHS1::exit(){

}

void FehlerWsZuFruehLSAbisHS1::WSinLSAbisHS(){

}

void FehlerWsZuFruehLSAbisHS1::HSaktiv(){

}

void FehlerWsZuFruehLSAbisHS1::quittiert(){
	exit();
	new (this) QuittiertZuFruehLSAbisHS1;
	entry();
}

void FehlerWsZuFruehLSAbisHS1::keinFehler(){

}

void FehlerWsZuFruehLSAbisHS1::Fverschwunden(){

}

void FehlerWsZuFruehLSAbisHS1::eStop(){
	exit();
	actions->eStop();
	new (this) WartenLSAbisHS1;
	entry();
}
