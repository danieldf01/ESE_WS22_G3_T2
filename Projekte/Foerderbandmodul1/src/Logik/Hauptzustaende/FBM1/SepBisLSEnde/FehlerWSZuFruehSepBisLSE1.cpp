/*
 * FehlerWSZuFrueh.cpp
 *
 *  Created on: 22.12.2022
 *      Author: tobias
 */

#include "FehlerWSZuFruehSepBisLSE1.h"

void FehlerWSZuFruehSepBisLSE1::entry(){
	actions->fehlerHoch();
	cout << "[FEHLER] Auf Foerderbandmodul 1 wurde an der Lichtschranke am Ende ein Stoerfaktor erkannt (oder ein Werkstueck nach vorne geschoben)." << endl;
	cout << "Bitte entfernen Sie den Stoerfaktor oder das Werkstueck, das sich am naechsten an der Lichtschranke befindet." << endl;
}

void FehlerWSZuFruehSepBisLSE1::exit(){

}

void FehlerWSZuFruehSepBisLSE1::LsEAn(){

}

void FehlerWSZuFruehSepBisLSE1::WsPassieren(){

}

void FehlerWSZuFruehSepBisLSE1::WeicheSchliessen(){

}

void FehlerWSZuFruehSepBisLSE1::FBM2bereit(){

}

void FehlerWSZuFruehSepBisLSE1::WsWurdeUebergeben(){

}

void FehlerWSZuFruehSepBisLSE1::quittiert(){
	exit();
	new (this) QuittiertZuFruehSepBisLSE1;
	entry();
}

void FehlerWSZuFruehSepBisLSE1::keinFehler(){

}

void FehlerWSZuFruehSepBisLSE1::fehlerVerschwunden(){

}

void FehlerWSZuFruehSepBisLSE1::eStop(){
	actions->eStop();
	new (this) WarteSepBisLSE1;
}
