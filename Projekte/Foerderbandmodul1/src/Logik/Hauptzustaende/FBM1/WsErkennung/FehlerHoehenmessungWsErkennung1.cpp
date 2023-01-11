/*
 * FehlerHoehenmessungWsErkennung1.cpp
 *
 *  Created on: 15.12.2022
 *      Author: Daniel Drefs Fernandes
 */

#include "FehlerHoehenmessungWsErkennung1.h"

using namespace std;

void FehlerHoehenmessungWsErkennung1::entry(){
	actions->fehlerHoch();
	actions->deleteWsHoehensensor();
	cout << "[FEHLER] Die Werkstueckmessung auf Foerderband 1 dauert zu lange. Moeglicherweise ist ein Werkstueck verschwunden." << endl;
	cout << "Bitte entfernen Sie ein Werkstueck unter dem Hoehensensor, falls dort eins liegt." << endl;
}

void FehlerHoehenmessungWsErkennung1::exit(){

}

void FehlerHoehenmessungWsErkennung1::WSinHS(){

}

void FehlerHoehenmessungWsErkennung1::WsTyp(){

}

void FehlerHoehenmessungWsErkennung1::quittiert(){
	exit();
	actions->schnellRunter();
	new (this) QuittiertWsErkennung1;
	entry();
}

void FehlerHoehenmessungWsErkennung1::keinFehler(){

}

void FehlerHoehenmessungWsErkennung1::fehlerHoehenmessung(){

}

void FehlerHoehenmessungWsErkennung1::eStop(){
	exit();
	actions->eStop();
	new (this) WartenWsErkennung1;
	entry();
}
