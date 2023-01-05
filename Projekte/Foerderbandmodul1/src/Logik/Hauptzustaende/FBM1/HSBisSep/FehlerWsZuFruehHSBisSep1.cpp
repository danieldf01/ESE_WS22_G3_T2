/*
 * FehlerWsZuFruehHSBisSep1.cpp
 *
 *  Created on: 17.12.2022
 *      Author: tobias
 */

#include "FehlerWsZuFruehHSBisSep1.h"

void FehlerWsZuFruehHSBisSep1::entry() {
	actions->fehlerHoch();
	cout << "[FEHLER] Auf Foerderbandmodul 1 wurde beim Seperator ein Stoerfaktor erkannt (oder ein Werkstueck nach vorne geschoben)." << endl;
	cout << "Bitte entfernen Sie den Stoerfaktor oder das Werkstueck, das sich am naechsten am Seperator befindet." << endl;
}

void FehlerWsZuFruehHSBisSep1::exit() {
}

void FehlerWsZuFruehHSBisSep1::WSinHSbisSep() {
}

void FehlerWsZuFruehHSBisSep1::MetSenAn() {
}

void FehlerWsZuFruehHSBisSep1::LSSepAn() {
}

void FehlerWsZuFruehHSBisSep1::aussortieren1(){

}

void FehlerWsZuFruehHSBisSep1::aussortieren2(){

}

void FehlerWsZuFruehHSBisSep1::aussortieren3(){

}

void FehlerWsZuFruehHSBisSep1::aussortieren4(){

}

void FehlerWsZuFruehHSBisSep1::quittiert() {
	exit();
	new (this) QuittiertZuFruehHSBisSep1;
	entry();
}

void FehlerWsZuFruehHSBisSep1::keinFehler() {
}

void FehlerWsZuFruehHSBisSep1::fehlerCntDown(){

}

void FehlerWsZuFruehHSBisSep1::fehlerVerschwunden(){

}

void FehlerWsZuFruehHSBisSep1::eStop() {
	exit();
	actions->eStop();
	new (this) WartenHSBisSep1;
	entry();
}
