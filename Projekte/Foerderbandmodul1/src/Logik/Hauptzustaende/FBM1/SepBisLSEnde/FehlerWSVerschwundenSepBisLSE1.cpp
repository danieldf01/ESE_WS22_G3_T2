/*
 * FehlerWSVerschwunden.cpp
 *
 *  Created on: 22.12.2022
 *      Author: tobias
 */

#include "FehlerWSVerschwundenSepBisLSE1.h"

using namespace std;

void FehlerWSVerschwundenSepBisLSE1::entry(){
	actions->fehlerHoch();
	cout << "[FEHLER] Auf Foerderbandmodul 1 ist ein Werkstueck zwischen dem Seperator und der Lichtschranke am Ende verschwunden." << endl;
	cout << "Bitte entfernen Sie in diesem Bereich " << wsListen->ws_list_passieren.size() << " Werkstueck(e)." << endl;
	actions->entferneWsPassieren();
}

void FehlerWSVerschwundenSepBisLSE1::exit(){

}

void FehlerWSVerschwundenSepBisLSE1::LsEAn(){

}

void FehlerWSVerschwundenSepBisLSE1::WsPassieren(){

}

void FehlerWSVerschwundenSepBisLSE1::WeicheSchliessen(){

}

void FehlerWSVerschwundenSepBisLSE1::FBM2bereit(){

}

void FehlerWSVerschwundenSepBisLSE1::WsWurdeUebergeben(){

}

void FehlerWSVerschwundenSepBisLSE1::quittiert(){
	exit();
	actions->schnellRunter();
	entry();
}

void FehlerWSVerschwundenSepBisLSE1::keinFehler(){

}

void FehlerWSVerschwundenSepBisLSE1::fehlerVerschwunden(){

}

void FehlerWSVerschwundenSepBisLSE1::eStop(){
	actions->eStop();
	new (this) WarteSepBisLSE1;
}
