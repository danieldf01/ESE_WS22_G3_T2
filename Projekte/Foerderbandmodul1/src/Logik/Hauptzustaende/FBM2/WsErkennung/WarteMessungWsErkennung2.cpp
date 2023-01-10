/*
 * WarteMessungWsErkennung2.cpp
 *
 *  Created on: 15.12.2022
 *      Author: Daniel Drefs Fernandes
 */

#include "WarteMessungWsErkennung2.h"

using namespace std;

void WarteMessungWsErkennung2::entry(){
//	cout << "Aktuelle Zeit WS in entry:" << wsListen->getWsHoehensensor2()->getTimestamp() << endl;
//	timestamp = wsListen->getWsHoehensensor2()->getTimestamp();
}

void WarteMessungWsErkennung2::exit(){

}

void WarteMessungWsErkennung2::WSinHS(){

}

void WarteMessungWsErkennung2::WsTyp(){
//	cout << "WarteMessungWsErkennung2 recv WSTyp" << endl;
	actions->checkWSueberschlagen();
	exit();
	actions->langsamRunter();
	if(zeitmanager->getTime() < 100 + wsListen->ws_Hoehensensor_2->getTimestamp()){
		cout << "[FEHLER] Die Werkstueckmessung auf Foerderband 2 ist zu schnell erfolgt. Bitte das Werkstueck unter dem Hoehensensor entfernen." << endl;
		new (this) FehlerHoehenmessungWsErkennung2;
	} else{
		actions->WSinHSbisSeperator();
		new (this) WartenWsErkennung2;
	}
	entry();
}

void WarteMessungWsErkennung2::quittiert(){

}

void WarteMessungWsErkennung2::keinFehler(){

}

void WarteMessungWsErkennung2::fehlerHoehenmessung(){
	actions->langsamRunter();
	cout << "[FEHLER] Die Werkstueckmessung auf Foerderband 2 dauert zu lange. Moeglicherweise ist ein Werkstueck verschwunden." << endl;
	cout << "Bitte entfernen Sie ein Werkstueck unter dem Hoehensensor, falls dort eins liegt." << endl;
	new (this) FehlerHoehenmessungWsErkennung2;
	entry();
}

void WarteMessungWsErkennung2::eStop(){
	actions->eStop();
	new (this) WartenWsErkennung2;
}
