/*
 * FehlerWSZuVielSepBisLSEnde.cpp
 *
 *  Created on: 22.12.2022
 *      Author: tobias
 */

#include "FehlerWSZuVielSepBisLSE1.h"

using namespace std;

void FehlerWSZuVielSepBisLSE1::entry(){
	actions->fehlerHoch();
	cout << "[FEHLER] Auf Foerderbandmodul 1 wurde an der Lichtschranke am Ende ein Stoerfaktor erkannt." << endl;
	cout << "Bitte entfernen Sie alle Werkstuecke zwischen dem Seperator und der Lichtschranke am Ende." << endl;
}

void FehlerWSZuVielSepBisLSE1::exit(){

}

void FehlerWSZuVielSepBisLSE1::LsEAn(){

}

void FehlerWSZuVielSepBisLSE1::WsAufWegZuLSE(){

}

void FehlerWSZuVielSepBisLSE1::FBM2bereit(){

}

void FehlerWSZuVielSepBisLSE1::WsWurdeUebergeben(){

}

void FehlerWSZuVielSepBisLSE1::quittiert(){
	exit();
	new (this) QuittiertZuVielSepBisLSE1;
	entry();
}

void FehlerWSZuVielSepBisLSE1::keinFehler(){

}

void FehlerWSZuVielSepBisLSE1::fehlerVerschwunden(){

}

void FehlerWSZuVielSepBisLSE1::eStop(){
	actions->eStop();
	new (this) WarteSepBisLSE1;
}
