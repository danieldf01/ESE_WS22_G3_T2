/*
 * FehlerWSZuVielHSBisSep1.cpp
 *
 *  Created on: 17.12.2022
 *      Author: tobias
 */

#include "FehlerWSZuVielHSBisSep1.h"

using namespace std;

void FehlerWSZuVielHSBisSep1::entry() {
	actions->fehlerHoch();
	cout << "[FEHLER] Auf Foerderband 1 wurde zwischen dem Hoehensensor und dem Seperator ein Stoerfaktor erkannt (eventuell wurde ein Werkstueck hinzugefuegt)." << endl;
	cout << "Bitte entfernen Sie ggf. alle Werkstuecke zwischen dem Hoehensensor und dem Seperator." << endl;
}

void FehlerWSZuVielHSBisSep1::exit() {
}

void FehlerWSZuVielHSBisSep1::WSinHSbisSep() {
}

void FehlerWSZuVielHSBisSep1::MetSenAn() {
}

void FehlerWSZuVielHSBisSep1::LSSepAn() {
}

void FehlerWSZuVielHSBisSep1::aussortieren1(){

}

void FehlerWSZuVielHSBisSep1::aussortieren2(){

}

void FehlerWSZuVielHSBisSep1::aussortieren3(){

}

void FehlerWSZuVielHSBisSep1::aussortieren4(){

}

void FehlerWSZuVielHSBisSep1::quittiert() {
	exit();
	new (this) QuittiertZuVielHSBisSep1;
	entry();
}

void FehlerWSZuVielHSBisSep1::keinFehler() {
}

void FehlerWSZuVielHSBisSep1::fehlerCntDown(){

}

void FehlerWSZuVielHSBisSep1::fehlerVerschwunden(){

}

void FehlerWSZuVielHSBisSep1::eStop() {
	exit();
	actions->eStop();
	new (this) WartenHSBisSep1;
	entry();
}
