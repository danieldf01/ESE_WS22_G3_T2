/*
 * WSAufWegZumSep1.cpp
 *
 *  Created on: 17.12.2022
 *      Author: tobias
 */

#include "WSAufWegZumSep1.h"

using namespace std;

void WSAufWegZumSep1::entry() {
//	cout << "WSAufWegZumSep1 entry" << endl;
}

void WSAufWegZumSep1::exit() {
}

void WSAufWegZumSep1::WSinHSbisSep() {
}

void WSAufWegZumSep1::MetSenAn() {
	exit();
	actions->setMetallTrue();
	new (this) ImMetallsensorHSBisSep1;
	entry();
}

void WSAufWegZumSep1::LSSepAn() {
	actions->deleteTimerVerschwunden();
	cout << "auf weg sep: WsListe Typ" <<  wsListen->ws_list_HS_bis_Seperator.front().getWsTyp() << endl;
	cout << "SortierReihenfolge: " << wsListen->sortierReihenfolge.front() << endl;
	aussortieren1();
	entry();
}

void WSAufWegZumSep1::quittiert() {
}

void WSAufWegZumSep1::keinFehler() {
}

void WSAufWegZumSep1::fehlerCntDown() {

}

void WSAufWegZumSep1::fehlerVerschwunden() {
	exit();
	new (this) FehlerWsVerschwundenHSBisSep1;
	entry();
}

void WSAufWegZumSep1::aussortieren1() {
	cout << "WSAufWegZumSep1 Before FehlerZuFrueh" << endl;
	//Fehler zu frueh? TODO Zeit als Define oder Konfig
	if (zeitmanager->getTime()< (500 + wsListen->ws_list_HS_bis_Seperator.front().getTimestamp())) {
		new (this) FehlerWsZuFruehHSBisSep1;
	} else {
		aussortieren2();
	}
}

void WSAufWegZumSep1::aussortieren2() {
	cout << "WSAufWegZumSep1 Before geforderterTyp?" << endl;
	//ist das aktuelle Werkstueck vom geforderten Typ?
	if (wsListen->ws_list_HS_bis_Seperator.front().getWsTyp() == wsListen->sortierReihenfolge.front()) {
		cout << "Werkstueck entspricht der Reihung" << endl;
		actions->WsPassierenGefordert();
		if (wsListen->ws_list_HS_bis_Seperator.size() <= 0) {
			new (this) WartenHSBisSep1;
		}
		//nicht geforderter Typ
	} else {
		cout << "Werkstueck entspricht nicht der Reihung" << endl;
		aussortieren3();
	}
}

void WSAufWegZumSep1::aussortieren3() {
	cout << "RUTSCHE 1 VOLL: " << rutsche->rutsche1->rutscheVoll1 << endl;
	cout << "RUTSCHE 2 VOLL: " << rutsche->rutsche2->rutscheVoll2 << endl;
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
			}
		}
	} else {
		aussortieren4();
	}
}

void WSAufWegZumSep1::aussortieren4() {
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
		cout << "[FBM1] WSAufWegZumSep1::aussortieren4 Werkstueck gehoert nicht zur Reihung soll aber passieren" << endl;
		//Werkstueck soll auf Foerderbandmodul 2 aussortiert werden
		actions->WsPassierenNichtGefordert();
		if (wsListen->ws_list_HS_bis_Seperator.size() <= 0) {
			new (this) WartenHSBisSep1;
		}
	} else {
		//Werkstueck ist ein flaches oder binaeres Werkstueck und kann auf Rutsche 1 aussortiert werden
		cout << "[FBM1] WSAufWegZumSep1::aussortieren4 Werkstueck soll aussortiert werden" << endl;
		actions->WsAussortieren();
		if (wsListen->ws_list_HS_bis_Seperator.size() <= 0) {
			new (this) WartenHSBisSep1;
		}
	}
}

void WSAufWegZumSep1::eStop() {
	exit();
	actions->eStop();
	new (this) WartenHSBisSep1;
	entry();
}
