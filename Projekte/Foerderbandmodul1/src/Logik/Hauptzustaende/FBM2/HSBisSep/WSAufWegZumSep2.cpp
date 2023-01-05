/*
 * WSAufWegZumSep2.cpp
 *
 *  Created on: 17.12.2022
 *      Author: tobias
 */

#include "WSAufWegZumSep2.h"

using namespace std;

void WSAufWegZumSep2::entry() {
	cout << "WSAufWegZumSep2 entry" << endl;
}

void WSAufWegZumSep2::exit() {
}

void WSAufWegZumSep2::WSinHSbisSep() {
}

void WSAufWegZumSep2::MetSenAn() {
	exit();
	actions->setMetallTrue();
	new (this) ImMetallsensorHSBisSep2;
	entry();
}

void WSAufWegZumSep2::LSSepAn() {
	exit();
//	cout << "auf weg sep: WsListe Typ" <<  wsListen->ws_list_HS_bis_Seperator_2.front().getWsTyp() << endl;
	cout << "SortierReihenfolge: " << wsListen->sortierReihenfolge.front() << endl;
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
//	if (zeitmanager->getTime()< (500 + wsListen->ws_list_HS_bis_Seperator_2.front().getTimestamp())) {
//		new (this) FehlerWsZuFruehHSBisSep2;
//	} else {
//		aussortieren2();
//	}
}

void WSAufWegZumSep2::aussortieren2() {
	//ist das aktuelle Werkstueck vom geforderten Typ?
//	if (wsListen->ws_list_HS_bis_Seperator_2.front().getWsTyp() == wsListen->sortierReihenfolge.front()) {
//		cout << "Werkstueck entspricht der Reihung" << endl;
//		actions->WsPassierenGefordert();
//		if (wsListen->ws_list_HS_bis_Seperator_2.size() <= 0) {
//			new (this) WartenHSBisSep2;
//		}
//		//nicht geforderter Typ
//	} else {
//		cout << "Werkstueck entspricht nicht der Reihung" << endl;
//		aussortieren3();
//	}
}
// TODO Anpassen
void WSAufWegZumSep2::aussortieren3() {
	if (rutsche->rutsche2->rutscheVoll2) {
		
	} else {
		
	}
}
