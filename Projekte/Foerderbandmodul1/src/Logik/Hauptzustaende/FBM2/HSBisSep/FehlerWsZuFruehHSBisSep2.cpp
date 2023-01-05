/*
 * FehlerWsZuFruehHSBisSep2.cpp
 *
 *  Created on: 17.12.2022
 *      Author: tobias
 */

#include "FehlerWsZuFruehHSBisSep2.h"

void FehlerWsZuFruehHSBisSep2::entry() {
	actions->fehlerHoch();
	cout << "[FEHLER] Auf Foerderbandmodul 2 wurde beim Seperator ein Stoerfaktor erkannt (oder ein Werkstueck nach vorne geschoben)." << endl;
	cout << "Bitte entfernen Sie den Stoerfaktor oder das Werkstueck, das sich am naechsten am Seperator befindet." << endl;
}

void FehlerWsZuFruehHSBisSep2::exit() {
}

void FehlerWsZuFruehHSBisSep2::WSinHSbisSep() {
}

void FehlerWsZuFruehHSBisSep2::MetSenAn() {
}

void FehlerWsZuFruehHSBisSep2::LSSepAn() {
}

void FehlerWsZuFruehHSBisSep2::aussortieren1(){

}

void FehlerWsZuFruehHSBisSep2::aussortieren2(){

}

void FehlerWsZuFruehHSBisSep2::aussortieren3(){

}

void FehlerWsZuFruehHSBisSep2::quittiert() {
	exit();
	new (this) QuittiertZuFruehHSBisSep2;
	entry();
}

void FehlerWsZuFruehHSBisSep2::keinFehler() {
}

void FehlerWsZuFruehHSBisSep2::fehlerCntDown(){

}

void FehlerWsZuFruehHSBisSep2::fehlerVerschwunden(){

}

void FehlerWsZuFruehHSBisSep2::eStop() {
	exit();
	actions->eStop();
	new (this) WartenHSBisSep2;
	entry();
}
