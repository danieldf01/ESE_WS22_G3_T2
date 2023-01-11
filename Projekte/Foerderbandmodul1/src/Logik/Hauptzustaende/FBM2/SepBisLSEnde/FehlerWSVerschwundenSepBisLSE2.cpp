/*
 * FehlerWSVerschwunden.cpp
 *
 *  Created on: 22.12.2022
 *      Author: tobias
 */

#include "FehlerWSVerschwundenSepBisLSE2.h"

using namespace std;

void FehlerWSVerschwundenSepBisLSE2::entry(){
	actions->fehlerHoch();
	cout << "[FEHLER] Auf Foerderbandmodul 2 ist ein Werkstueck zwischen dem Seperator und der Lichtschranke am Ende verschwunden." << endl;
	cout << "Bitte entfernen Sie alle Werkstuecke vom Foerderbandmodul 2." << endl;
	actions->entferneWsPassieren();
}

void FehlerWSVerschwundenSepBisLSE2::exit(){

}

void FehlerWSVerschwundenSepBisLSE2::LsEAn(){

}

void FehlerWSVerschwundenSepBisLSE2::LsEAus() {

}

void FehlerWSVerschwundenSepBisLSE2::WsPassieren(){

}

void FehlerWSVerschwundenSepBisLSE2::WeicheSchliessen(){

}

void FehlerWSVerschwundenSepBisLSE2::quittiert(){
	actions->schnellRunter();
	new (this) QuittiertVerschwundenSepBisLSE2;
	entry();
}

void FehlerWSVerschwundenSepBisLSE2::keinFehler(){

}

void FehlerWSVerschwundenSepBisLSE2::fehlerVerschwunden(){

}

void FehlerWSVerschwundenSepBisLSE2::eStop(){
	actions->eStop();
	new (this) WarteSepBisLSE2;
}
