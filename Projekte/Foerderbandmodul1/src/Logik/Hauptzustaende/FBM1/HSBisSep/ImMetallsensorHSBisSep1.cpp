/*
 * ImMetallsensorHSBisSep1.cpp
 *
 *  Created on: 17.12.2022
 *      Author: tobias
 */

#include "ImMetallsensorHSBisSep1.h"

void ImMetallsensorHSBisSep1::entry() {
}

void ImMetallsensorHSBisSep1::exit() {
}

void ImMetallsensorHSBisSep1::WSinHSbisSep() {
}

void ImMetallsensorHSBisSep1::MetSenAn() {
}

void ImMetallsensorHSBisSep1::LSSepAn() {
	exit();
	actions->deleteTimerVerschwunden(); // TODO Nicht in der Doku
	aussortieren1();
	entry();
}

void ImMetallsensorHSBisSep1::quittiert() {
}

void ImMetallsensorHSBisSep1::keinFehler() {
}

void ImMetallsensorHSBisSep1::fehlerCntDown() {

}

void ImMetallsensorHSBisSep1::fehlerVerschwunden() {
	exit();
	new (this) FehlerWsVerschwundenHSBisSep1;
	entry();
}

void ImMetallsensorHSBisSep1::aussortieren1() {
	//Fehler zu frueh? TODO Define oder Konfig
	if (zeitmanager->getTime()< (500 + wsListen->ws_list_HS_bis_Seperator.front().getTimestamp())) {
		new (this) FehlerWsZuFruehHSBisSep1;
	} else {
		aussortieren2();
	}
}

void ImMetallsensorHSBisSep1::aussortieren2() {
	//ist das aktuelle Werkstueck vom geforderten Typ?
	if (wsListen->ws_list_HS_bis_Seperator.front().getWsTyp() == wsListen->sortierReihenfolge.front()) {
		cout << "Werkstueck entspricht der Reihung" << endl;
		actions->WsPassierenGefordert();
		if (wsListen->ws_list_HS_bis_Seperator.size() <= 0) {
			new (this) WartenHSBisSep1;
		} // TODO Fehlt hier nicht ein else WS_auf_Weg_zum_Sep?
		//nicht geforderter Typ
	} else {
		cout << "Werkstueck entspricht nicht der Reihung" << endl;
		aussortieren3();
	}
}

void ImMetallsensorHSBisSep1::aussortieren3() {
	if (rutsche->rutsche2->rutscheVoll2) {
		if (rutsche->rutsche1->rutscheVoll1) {
			//wenn Rutsche 1 und 2 voll sind, tritt der Fehler nicht aussortierbar ein
			actions->WsNichtAussortierbar();
			new (this) WarteAufRutscheFreiHSBisSep1;
		} else {
			//da Rutsche 2 voll ist, wird WS, das nicht der Reihung entspricht, bereits auf Band 1 aussortiert
			actions->WsAussortieren();
			if (wsListen->ws_list_HS_bis_Seperator.size() <= 0) {
				new (this) WartenHSBisSep1;
			} // TODO Fehlt hier nicht ein else WS_auf_Weg_zum_Sep?
		}
	} else {
		aussortieren4();
	}
}

void ImMetallsensorHSBisSep1::aussortieren4() {
	//ueberpruefe, ob Rutsche 1 voll ist
	//oder die Sortierreihenfolge den Typ des aktuellen Werkstuecks enthaelt
	//oder das Werkstueck ein hohes ist
	WsTyp typ = wsListen->ws_list_HS_bis_Seperator.front().getWsTyp();
	bool rutscheVoll1 = rutsche->rutsche1->rutscheVoll1;
	bool isInsideReihenfolge = std::find(wsListen->sortierReihenfolge.begin(),wsListen->sortierReihenfolge.end(), typ)!= wsListen->sortierReihenfolge.end();

	cout << "BOOL:" << isInsideReihenfolge << endl;
	cout << "typ" << typ << endl;
	cout << "rutvoll" << rutscheVoll1 << endl;

	if (rutscheVoll1 || isInsideReihenfolge || (typ== HOCH_OB || typ == HOCH_MB || typ == HOCH_MBM)) {
		cout << "ImMetallsensorHSBisSep1::aussortieren4 Werkstueck gehoert nicht zur Reihung soll aber passieren" << endl;
		//Werkstueck soll auf Foerderbandmodul 2 aussortiert werden
		actions->WsPassierenNichtGefordert();
		if (wsListen->ws_list_HS_bis_Seperator.size() <= 0) {
			new (this) WartenHSBisSep1;
		} // TODO Fehlt hier nicht ein else WS_auf_Weg_zum_Sep?
	} else {
		//Werkstueck ist ein flaches oder binaeres Werkstueck und kann auf Rutsche 1 aussortiert werden
		cout << "ImMetallsensorHSBisSep1::aussortieren4 Werkstueck soll aussortiert werden" << endl;
		actions->WsAussortieren();
		if (wsListen->ws_list_HS_bis_Seperator.size() <= 0) {
			new (this) WartenHSBisSep1;
		} // TODO Fehlt hier nicht ein else WS_auf_Weg_zum_Sep?
	}
}

void ImMetallsensorHSBisSep1::eStop() {
	exit();
	actions->eStop();
	new (this) WartenHSBisSep1;
	entry();
}
