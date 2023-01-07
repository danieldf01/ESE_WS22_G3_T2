/*
 * ActionsHSBisSep2.cpp
 *
 *  Created on: 15.12.2022
 *      Author: Daniel Drefs Fernandes
 */

#include "ActionsHSBisSep2.h"

ActionsHSBisSep2::~ActionsHSBisSep2() {

}

void ActionsHSBisSep2::setupConnection(){
	if ((logikID = name_open(LOGIK, NAME_FLAG_ATTACH_GLOBAL)) == -1) {
		perror("[FSM_HSbisSeperator2] name_open failed");
		exit(EXIT_FAILURE);
	}
}

void ActionsHSBisSep2::setMetallTrue(){
	if(wsListen->ws_hs_bis_seperator_2->getWsTyp() == HOCH_MB){
		wsListen->ws_hs_bis_seperator_2->setWsTyp(HOCH_MBM);
	} else{
		wsListen->ws_hs_bis_seperator_2->setWsTyp(UNBEKANNT);
	}
}

void ActionsHSBisSep2::WsPassieren(){

	// update Reihung
	int temp = wsListen->sortierReihenfolge.front();
	wsListen->sortierReihenfolge.pop_front();
	wsListen->sortierReihenfolge.push_back(temp);

	// update Werkstuecke
	Werkstueck *temp_ws = wsListen->ws_hs_bis_seperator_2;
	temp_ws->setTimestamp(zeitmanager->getTime());
	wsListen->ws_passieren_2 = temp_ws;
	wsListen->ws_hs_bis_seperator_2 = nullptr;


	if (MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_2, WS_PASSIEREN) == -1) {
		perror("[FSM_HSbisSeperator2] MsgSendPulse failed");
		exit(EXIT_FAILURE);
	}
}

void ActionsHSBisSep2::WsAussortieren(){

	cout << "ActionsHSBisSep2 WsAussortieren" << endl;
	// update Werkstuecke
	Werkstueck *temp_ws = wsListen->ws_hs_bis_seperator_2;
	temp_ws->setTimestamp(zeitmanager->getTime());
	wsListen->ws_aussortieren_2 = temp_ws;
	wsListen->ws_hs_bis_seperator_2 = nullptr;

	if (MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_2, WS_AUSSORTIEREN) == -1) {
		perror("[FSM_HSbisSeperator2] MsgSendPulse failed");
		exit(EXIT_FAILURE);
	}
}

void ActionsHSBisSep2::WsNichtAussortierbar(){
	if (MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_2, WS_NICHT_AUSSORTIERBAR) == -1) {
		perror("[FSM_HSbisSeperator] MsgSendPulse failed");
		exit(EXIT_FAILURE);
	}
}

void ActionsHSBisSep2::fehlerHoch(){
	if (MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_2, FEHLER_HOCH) == -1) {
		perror("[FSM_HSbisSeperator2] MsgSendPulse failed");
		exit(EXIT_FAILURE);
	}
}

void ActionsHSBisSep2::fehlerRunter(){
	if (MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_2, FEHLER_RUNTER) == -1) {
		perror("[FSM_HSbisSeperator2] MsgSendPulse failed");
		exit(EXIT_FAILURE);
	}
}

void ActionsHSBisSep2::entferneWsHSbisSep(){
//	wsListen->ws_list_HS_bis_Seperator_2.pop_front();
}

void ActionsHSBisSep2::schnellRunter(){
	if (MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_2, SCHNELL_RUNTER_2) == -1) {
		perror("[FSM_HSbisSeperator2] MsgSendPulse failed");
		exit(EXIT_FAILURE);
	}
}

void ActionsHSBisSep2::deleteTimerVerschwunden(){
	zeitmanager->deleteTimer(wsListen->ws_list_HS_bis_Seperator.back().getiD());
}

void ActionsHSBisSep2::sendFBM2Bereit() {
	if (MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_2, FBM2_BEREIT) == -1) {
		perror("[FSM_LSAnfang2] MsgSendPulse failed");
		exit(EXIT_FAILURE);
	}
}

void ActionsHSBisSep2::eStop(){
	wsListen->ws_list_passieren.clear();
	wsListen->ws_list_aussortieren.clear();
}
