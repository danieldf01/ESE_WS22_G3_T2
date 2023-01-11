/*
 * FehlerNichtAussortierbarHSBisSep1.cpp
 *
 *  Created on: 19.12.2022
 *      Author: Daniel Drefs Fernandes
 */
#include "WarteAufRutscheFreiHSBisSep1.h"

void WarteAufRutscheFreiHSBisSep1::entry() {
}

void WarteAufRutscheFreiHSBisSep1::exit() {
}

void WarteAufRutscheFreiHSBisSep1::WSinHSbisSep() {
}

void WarteAufRutscheFreiHSBisSep1::MetSenAn() {
}

void WarteAufRutscheFreiHSBisSep1::LSSepAn() {
}

void WarteAufRutscheFreiHSBisSep1::aussortieren1(){

}

void WarteAufRutscheFreiHSBisSep1::aussortieren2(){

}

void WarteAufRutscheFreiHSBisSep1::quittiert() {
}

void WarteAufRutscheFreiHSBisSep1::keinFehler() {
}

void WarteAufRutscheFreiHSBisSep1::fehlerVerschwunden() {

}

void WarteAufRutscheFreiHSBisSep1::fehlerCntDown() {
	if (!rutsche->rutsche1->rutscheVoll1 || !rutsche->rutsche2->rutscheVoll2) {
		exit();
		aussortieren3();
		entry();
	}
}

void WarteAufRutscheFreiHSBisSep1::aussortieren3(){
	if (rutsche->rutsche2->rutscheVoll2) {
		if (rutsche->rutsche1->rutscheVoll1) {
			//wenn Rutsche 1 und 2 voll sind, tritt der Fehler nicht aussortierbar ein
			actions->WsNichtAussortierbar();
			new (this) WarteAufRutscheFreiHSBisSep1;
		} else {
			//da Rutsche 2 voll ist, wird WS, das nicht der Reihung entspricht, bereits auf Band 1 aussortiert
			actions->WsAussortieren();
			if (wsListen->ws_list_HS_bis_Seperator.size() > 0) {
				new (this) WSAufWegZumSep1;
			} else {
				new (this) WartenHSBisSep1;
			}
		}
	} else {
		aussortieren4();
	}
}

void WarteAufRutscheFreiHSBisSep1::aussortieren4(){
	//ueberpruefe, ob Rutsche 1 voll ist
	//oder die Sortierreihenfolge den Typ des aktuellen Werkstuecks enthaelt
	//oder das Werkstueck ein hohes ist
	WsTyp typ = wsListen->ws_list_HS_bis_Seperator.front().getWsTyp();
	bool rutscheVoll1 = rutsche->rutsche1->rutscheVoll1;
	bool isInsideReihenfolge = std::find(wsListen->sortierReihenfolge.begin(),wsListen->sortierReihenfolge.end(), typ)!= wsListen->sortierReihenfolge.end();

//	cout << "BOOL:" << isInsideReihenfolge << endl;
//	cout << "typ" << typ << endl;
//	cout << "rutvoll" << rutscheVoll1 << endl;

	if (rutscheVoll1 || isInsideReihenfolge || (typ== HOCH_OB || typ == HOCH_MB || typ == HOCH_MBM)) {
		cout << "[FBM1] Werkstueck gehoert nicht zur Reihung soll aber passieren" << endl;
		//Werkstueck soll auf Foerderbandmodul 2 aussortiert werden
		actions->WsPassierenNichtGefordert();
		if (wsListen->ws_list_HS_bis_Seperator.size() <= 0) {
			new (this) WartenHSBisSep1;
		} else{
			new (this) WSAufWegZumSep1;
		}
	} else {
		//Werkstueck ist ein flaches oder binaeres Werkstueck und kann auf Rutsche 1 aussortiert werden
		cout << "[FBM1] Werkstueck soll aussortiert werden" << endl;
		actions->WsAussortieren();
		if (wsListen->ws_list_HS_bis_Seperator.size() <= 0) {
			new (this) WartenHSBisSep1;
		} else {
			new (this) WSAufWegZumSep1;
		}
	}
}

void WarteAufRutscheFreiHSBisSep1::eStop() {
	exit();
	actions->eStop();
	new (this) WartenHSBisSep1;
	entry();
}
