/*
 * FehlerWSZuVielHSBisSep2.cpp
 *
 *  Created on: 17.12.2022
 *      Author: tobias
 */

#include "FehlerWSZuVielHSBisSep2.h"

using namespace std;

void FehlerWSZuVielHSBisSep2::entry() {
	actions->fehlerHoch();
	cout << "[FEHLER] Auf Foerderband 2 wurde zwischen dem Hoehensensor und dem Seperator ein Stoerfaktor erkannt (eventuell wurde ein Werkstueck hinzugefuegt)." << endl;
	cout << "Bitte entfernen Sie ggf. alle Werkstuecke zwischen dem Hoehensensor und dem Seperator." << endl;
}

void FehlerWSZuVielHSBisSep2::exit() {
}

void FehlerWSZuVielHSBisSep2::WSinHSbisSep() {
}

void FehlerWSZuVielHSBisSep2::MetSenAn() {
}

void FehlerWSZuVielHSBisSep2::LSSepAn() {
}

void FehlerWSZuVielHSBisSep2::aussortieren1(){

}

void FehlerWSZuVielHSBisSep2::aussortieren2(){

}

void FehlerWSZuVielHSBisSep2::aussortieren3(){

}

void FehlerWSZuVielHSBisSep2::quittiert() {
	new (this) QuittiertZuVielHSBisSep2;
	entry();
}

void FehlerWSZuVielHSBisSep2::keinFehler() {
}

void FehlerWSZuVielHSBisSep2::fehlerCntDown(){

}

void FehlerWSZuVielHSBisSep2::fehlerVerschwunden(){

}

void FehlerWSZuVielHSBisSep2::eStop() {
	actions->eStop();
	new (this) WartenHSBisSep2;
}
