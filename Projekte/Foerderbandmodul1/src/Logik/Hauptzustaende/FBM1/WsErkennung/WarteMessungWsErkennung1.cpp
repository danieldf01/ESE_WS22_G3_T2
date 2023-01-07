/*
 * WarteMessungWsErkennung1.cpp
 *
 *  Created on: 15.12.2022
 *      Author: Daniel Drefs Fernandes
 */

#include "WarteMessungWsErkennung1.h"

using namespace std;

void WarteMessungWsErkennung1::entry(){
//	cout << "Aktuelle Zeit WS in entry:" << wsListen->getWsHoehensensor1()->getTimestamp() << endl;
}

void WarteMessungWsErkennung1::exit(){

}

void WarteMessungWsErkennung1::WSinHS(){

}

void WarteMessungWsErkennung1::WsTyp(){

	exit();
	actions->langsamRunter();
	cout << "WarteMessungWsErkennung1 WsTyp revived time: " << wsListen->getWsHoehensensor1()->getTimestamp() << endl;

	if(zeitmanager->getTime() < 100 + wsListen->ws_Hoehensensor_1->getTimestamp()){
		cout << "[FEHLER] Die Werkstueckmessung auf Foerderband 1 ist zu schnell erfolgt. Bitte das Werkstueck unter dem Hoehensensor entfernen." << endl;
		new (this) FehlerHoehenmessungWsErkennung1;
	} else{
		actions->WSinHSbisSeperator();
		new (this) WartenWsErkennung1;
	}
	entry();
}

void WarteMessungWsErkennung1::quittiert(){

}

void WarteMessungWsErkennung1::keinFehler(){

}

void WarteMessungWsErkennung1::fehlerHoehenmessung(){
	exit();
	actions->langsamRunter();
	cout << "[FEHLER] Die Werkstueckmessung auf Foerderband 1 dauert zu lange. Moeglicherweise ist ein Werkstueck verschwunden." << endl;
	cout << "Bitte entfernen Sie ein Werkstueck unter dem Hoehensensor, falls dort eins liegt." << endl;
	new (this) FehlerHoehenmessungWsErkennung1;
	entry();
}

void WarteMessungWsErkennung1::eStop(){
	exit();
	actions->eStop();
	new (this) WartenWsErkennung1;
	entry();
}
