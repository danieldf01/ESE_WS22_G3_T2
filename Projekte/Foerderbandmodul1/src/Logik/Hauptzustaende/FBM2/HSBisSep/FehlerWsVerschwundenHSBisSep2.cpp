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
//	cout << "[FEHLER] Auf Foerderbandmodul 2 ist ein Werkstueck zwischen dem Hoehensensor und dem Seperator verschwunden." << endl;
//	cout << "Bitte entfernen Sie in diesem Bereich " << wsListen->ws_list_HS_bis_Seperator_2.size() << " Werkstueck(e)." << endl;
	actions->entferneWsHSbisSep();
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
	exit();
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
	exit();
	actions->eStop();
	new (this) WartenHSBisSep2;
	entry();
}
