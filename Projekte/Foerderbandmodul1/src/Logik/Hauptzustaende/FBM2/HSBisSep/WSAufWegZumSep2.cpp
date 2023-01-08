/*
 * WSAufWegZumSep2.cpp
 *
 *  Created on: 17.12.2022
 *      Author: tobias
 */

#include "WSAufWegZumSep2.h"

using namespace std;

void WSAufWegZumSep2::entry() {
}

void WSAufWegZumSep2::exit() {
}

void WSAufWegZumSep2::WSinHSbisSep() {
}

void WSAufWegZumSep2::MetSenAn() {
//	cout << "WSAufWegZumSep2 recv:MetSenAn" << endl;
	exit();
	actions->setMetallTrue();
	new (this) ImMetallsensorHSBisSep2;
	entry();
}

void WSAufWegZumSep2::LSSepAn() {
//	cout << "WSAufWegZumSep2 recv:LSSepAn" << endl;
	exit();
//	cout << "auf weg sep: WsListe Typ" <<  wsListen->ws_list_HS_bis_Seperator_2.front().getWsTyp() << endl;
	cout << "SortierReihenfolge: " << wsListen->sortierReihenfolge2.front() << endl;
	actions->deleteTimerVerschwunden();
	// TODO Zeit anpassen
	aussortieren1();
	entry();
}

void WSAufWegZumSep2::quittiert() {
}

void WSAufWegZumSep2::keinFehler() {
}

void WSAufWegZumSep2::fehlerCntDown() {

}

void WSAufWegZumSep2::fehlerVerschwunden() {
	exit();
	new (this) FehlerWsVerschwundenHSBisSep2;
	entry();
}

void WSAufWegZumSep2::eStop() {
	exit();
	actions->eStop();
	new (this) WartenHSBisSep2;
	entry();
}

void WSAufWegZumSep2::aussortieren1() {
	//Fehler zu frueh?
	if (zeitmanager->getTime()< (500 + wsListen->ws_hs_bis_seperator_2->getTimestamp())) {
		new (this) FehlerWsZuFruehHSBisSep2;
	} else {
		aussortieren2();
	}
}

void WSAufWegZumSep2::aussortieren2() {
	//ist das aktuelle Werkstueck vom geforderten Typ?
	if (wsListen->ws_hs_bis_seperator_2->getWsTyp() == wsListen->sortierReihenfolge2.front()) {
		cout << "[FBM2] Werkstueck entspricht der Reihung" << endl;
		actions->WsPassieren();
		new (this) WartenHSBisSep2;
		//nicht geforderter Typ
	} else {
		cout << "[FBM2] Werkstueck entspricht nicht der Reihung" << endl;
		aussortieren3();
	}
}

void WSAufWegZumSep2::aussortieren3() {
	if (rutsche->rutsche2->rutscheVoll2) {
		actions->WsNichtAussortierbar();
		new (this) WarteAufRutscheFreiHSBisSep2;
	} else {
//		cout << "WSAufWegZumSep2 aussortieren3 else" << endl;
		actions->WsAussortieren();
		new (this) WartenHSBisSep2;
	}
}
