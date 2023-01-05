/*
 * FehlerWsVerschwundenHSBisSep1.cpp
 *
 *  Created on: 17.12.2022
 *      Author: tobias
 */

#include "FehlerWsVerschwundenHSBisSep1.h"

using namespace std;

void FehlerWsVerschwundenHSBisSep1::entry() {
	actions->fehlerHoch();
	cout << "[FEHLER] Auf Foerderbandmodul 1 ist ein Werkstueck zwischen dem Hoehensensor und dem Seperator verschwunden." << endl;
	cout << "Bitte entfernen Sie in diesem Bereich " << wsListen->ws_list_HS_bis_Seperator.size() << " Werkstueck(e)." << endl;
	actions->entferneWsHSbisSep();
}

void FehlerWsVerschwundenHSBisSep1::exit() {
}

void FehlerWsVerschwundenHSBisSep1::WSinHSbisSep() {
}

void FehlerWsVerschwundenHSBisSep1::MetSenAn() {
}

void FehlerWsVerschwundenHSBisSep1::LSSepAn() {
}

void FehlerWsVerschwundenHSBisSep1::aussortieren1(){

}

void FehlerWsVerschwundenHSBisSep1::aussortieren2(){

}

void FehlerWsVerschwundenHSBisSep1::aussortieren3(){

}

void FehlerWsVerschwundenHSBisSep1::aussortieren4(){

}

void FehlerWsVerschwundenHSBisSep1::quittiert() {
	exit();
	actions->schnellRunter();
	new (this) QuittiertVerschwundenHSBisSep1;
	entry();
}

void FehlerWsVerschwundenHSBisSep1::keinFehler() {
}

void FehlerWsVerschwundenHSBisSep1::fehlerCntDown(){

}

void FehlerWsVerschwundenHSBisSep1::fehlerVerschwunden(){

}

void FehlerWsVerschwundenHSBisSep1::eStop() {
	exit();
	actions->eStop();
	new (this) WartenHSBisSep1;
	entry();
}
