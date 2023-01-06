/*
 * FehlerWSZuVielSepBisLSEnde.cpp
 *
 *  Created on: 22.12.2022
 *      Author: tobias
 */

#include "FehlerWSZuVielSepBisLSE2.h"

using namespace std;

void FehlerWSZuVielSepBisLSE2::entry(){
	actions->fehlerHoch();
	cout << "[FEHLER] Auf Foerderbandmodul 2 wurde an der Lichtschranke am Ende ein Stoerfaktor erkannt." << endl;
	cout << "Bitte entfernen Sie alle Werkstuecke zwischen dem Seperator und der Lichtschranke am Ende." << endl;
}

void FehlerWSZuVielSepBisLSE2::exit(){

}

void FehlerWSZuVielSepBisLSE2::LsEAn(){

}

void FehlerWSZuVielSepBisLSE2::LsEAus() {

}

void FehlerWSZuVielSepBisLSE2::WsPassieren(){

}

void FehlerWSZuVielSepBisLSE2::WeicheSchliessen(){

}

void FehlerWSZuVielSepBisLSE2::FBM2bereit(){

}

void FehlerWSZuVielSepBisLSE2::WsWurdeUebergeben(){

}

void FehlerWSZuVielSepBisLSE2::quittiert(){
	exit();
	new (this) QuittiertZuVielSepBisLSE2;
	entry();
}

void FehlerWSZuVielSepBisLSE2::keinFehler(){

}

void FehlerWSZuVielSepBisLSE2::fehlerVerschwunden(){

}

void FehlerWSZuVielSepBisLSE2::eStop(){
	actions->eStop();
	new (this) WarteSepBisLSE2;
}
