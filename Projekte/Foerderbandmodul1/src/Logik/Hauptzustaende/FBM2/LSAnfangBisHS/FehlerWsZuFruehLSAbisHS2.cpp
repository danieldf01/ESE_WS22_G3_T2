/*
 * FehlerWsZuFruehLSAbisHS.cpp
 *
 *  Created on: 14.12.2022
 *      Author: Daniel Drefs Fernandes
 */

#include "FehlerWsZuFruehLSAbisHS2.h"

void FehlerWsZuFruehLSAbisHS2::entry(){
	actions->fehlerHoch();
	cout << "[FEHLER] Auf Foerderbandmodul 2 wurde unter dem Hoehensensor ein Stoerfaktor erkannt (oder ein Werkstueck nach vorne geschoben)." << endl;
	cout << "Bitte entfernen Sie den Stoerfaktor oder das Werkstueck, das sich am naechsten am Hoehensensor (wahrscheinlich sogar darunter) befindet." << endl;
}

void FehlerWsZuFruehLSAbisHS2::exit(){

}

void FehlerWsZuFruehLSAbisHS2::WSinLSAbisHS(){

}

void FehlerWsZuFruehLSAbisHS2::HSaktiv(){

}

void FehlerWsZuFruehLSAbisHS2::quittiert(){
	exit();
	new (this) QuittiertZuFruehLSAbisHS2;
	entry();
}

void FehlerWsZuFruehLSAbisHS2::keinFehler(){

}

void FehlerWsZuFruehLSAbisHS2::Fverschwunden(){

}

void FehlerWsZuFruehLSAbisHS2::eStop(){
	exit();
	actions->eStop();
	new (this) WartenLSAbisHS2;
	entry();
}
