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

void WarteAufRutscheFreiHSBisSep1::aussortieren3(){

}

void WarteAufRutscheFreiHSBisSep1::aussortieren4(){

}

void WarteAufRutscheFreiHSBisSep1::quittiert() {
}

void WarteAufRutscheFreiHSBisSep1::keinFehler() {
}

void WarteAufRutscheFreiHSBisSep1::fehlerCntDown() {
	if (!rutsche->rutsche1->rutscheVoll1 || !rutsche->rutsche2->rutscheVoll2) {
		exit();
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
			//ueberpruefe, ob Rutsche 1 voll ist
			//oder die Sortierreihenfolge den Typ des aktuellen Werkstuecks enthaelt
			//oder das Werkstueck ein hohes ist
			if (rutsche->rutsche1->rutscheVoll1
					|| (std::find(wsListen->sortierReihenfolge.begin(),
							wsListen->sortierReihenfolge.end(),
							wsListen->ws_list_HS_bis_Seperator.front().getWsTyp())
							!= wsListen->sortierReihenfolge.end())
					|| (wsListen->ws_list_HS_bis_Seperator.front().getWsTyp()
							== HOCH_OB
							|| wsListen->ws_list_HS_bis_Seperator.front().getWsTyp()
									== HOCH_MB
							|| wsListen->ws_list_HS_bis_Seperator.front().getWsTyp()
									== HOCH_MBM)) {
				//Werkstueck soll auf Foerderbandmodul 2 aussortiert werden
				actions->WsPassierenNichtGefordert();
				if (wsListen->ws_list_HS_bis_Seperator.size() > 0) {
					new (this) WSAufWegZumSep1;
				} else {
					new (this) WartenHSBisSep1;
				}
			} else {
				//Werkstueck ist ein flaches oder binaeres Werkstueck und kann auf Rutsche 1 aussortiert werden
				actions->WsAussortieren();
				if (wsListen->ws_list_HS_bis_Seperator.size() > 0) {
					new (this) WSAufWegZumSep1;
				} else {
					new (this) WartenHSBisSep1;
				}
			}
		}
		entry();
	}
}

void WarteAufRutscheFreiHSBisSep1::fehlerVerschwunden() {

}

void WarteAufRutscheFreiHSBisSep1::eStop() {
	exit();
	actions->eStop();
	new (this) WartenHSBisSep1;
	entry();
}
