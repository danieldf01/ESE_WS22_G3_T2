/*
 * FehlerWsVerschwundenHSBisSep2.cpp
 *
 *  Created on: 17.12.2022
 *      Author: tobias
 */

#include "FehlerWsVerschwundenHSBisSep2.h"

using namespace std;

void FehlerWsVerschwundenHSBisSep2::entry() {
	actions->fehlerHoch();
	actions->entferneWsHSbisSep();
	cout << "[FEHLER] Auf Foerderbandmodul 2 ist ein Werkstueck zwischen dem Hoehensensor und dem Seperator verschwunden." << endl;
	cout << "Bitte entfernen Sie alle Werkstuecke vom Foerderbandmodul 2." << endl;
}

void FehlerWsVerschwundenHSBisSep2::exit() {
}

void FehlerWsVerschwundenHSBisSep2::WSinHSbisSep() {
}

void FehlerWsVerschwundenHSBisSep2::MetSenAn() {
}

void FehlerWsVerschwundenHSBisSep2::LSSepAn() {
}

void FehlerWsVerschwundenHSBisSep2::aussortieren1(){

}

void FehlerWsVerschwundenHSBisSep2::aussortieren2(){

}

void FehlerWsVerschwundenHSBisSep2::aussortieren3(){

}

void FehlerWsVerschwundenHSBisSep2::quittiert() {
	actions->schnellRunter();
	new (this) QuittiertVerschwundenHSBisSep2;
	entry();
}

void FehlerWsVerschwundenHSBisSep2::keinFehler() {
}

void FehlerWsVerschwundenHSBisSep2::fehlerCntDown(){

}

void FehlerWsVerschwundenHSBisSep2::fehlerVerschwunden(){

}

void FehlerWsVerschwundenHSBisSep2::eStop() {
	actions->eStop();
	new (this) WartenHSBisSep2;
}
