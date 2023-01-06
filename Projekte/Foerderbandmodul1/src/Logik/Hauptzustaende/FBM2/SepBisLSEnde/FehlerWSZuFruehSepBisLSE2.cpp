/*
 * FehlerWSZuFrueh.cpp
 *
 *  Created on: 22.12.2022
 *      Author: tobias
 */

#include "FehlerWSZuFruehSepBisLSE2.h"

void FehlerWSZuFruehSepBisLSE2::entry(){
	actions->fehlerHoch();
	cout << "[FEHLER] Auf Foerderbandmodul 2 wurde an der Lichtschranke am Ende ein Stoerfaktor erkannt (oder ein Werkstueck nach vorne geschoben)." << endl;
	cout << "Bitte entfernen Sie den Stoerfaktor oder das Werkstueck, das sich am naechsten an der Lichtschranke befindet." << endl;
}

void FehlerWSZuFruehSepBisLSE2::exit(){

}

void FehlerWSZuFruehSepBisLSE2::LsEAn(){

}

void FehlerWSZuFruehSepBisLSE2::LsEAus() {

}

void FehlerWSZuFruehSepBisLSE2::WsPassieren(){

}

void FehlerWSZuFruehSepBisLSE2::WeicheSchliessen(){

}

void FehlerWSZuFruehSepBisLSE2::FBM2bereit(){

}

void FehlerWSZuFruehSepBisLSE2::WsWurdeUebergeben(){

}

void FehlerWSZuFruehSepBisLSE2::quittiert(){
	exit();
	new (this) QuittiertZuFruehSepBisLSE2;
	entry();
}

void FehlerWSZuFruehSepBisLSE2::keinFehler(){

}

void FehlerWSZuFruehSepBisLSE2::fehlerVerschwunden(){

}

void FehlerWSZuFruehSepBisLSE2::eStop(){
	actions->eStop();
	new (this) WarteSepBisLSE2;
}
