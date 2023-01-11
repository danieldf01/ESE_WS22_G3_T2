/*
 * FehlerRutsche2Voll.cpp
 *
 *  Created on: 21.12.2022
 *      Author: Daniel Drefs Fernandes
 */

#include "FehlerRutsche2Voll.h"

using namespace std;

void FehlerRutsche2Voll::entry(){
	actions->fehlerHoch();
	cout << "[FEHLER] Die Rutsche auf Foerderbandmodul 2 ist voll, es kann dort kein Werkstueck aussortiert werden!" << endl;
	cout << "Bitte entfernen Sie alle Werkstuecke aus der Rutsche" << endl;
}

void FehlerRutsche2Voll::exit(){
	actions->fehlerRunter();
}

void FehlerRutsche2Voll::WsNichtAussortierbar(){

}

void FehlerRutsche2Voll::LsRutscheAus1(){

}

void FehlerRutsche2Voll::LsRutscheAus2(){
	exit();
	new (this) WartenWsNichtAussortierbar;
	entry();
}

void FehlerRutsche2Voll::eStop(){
	new (this) WartenWsNichtAussortierbar;
}
