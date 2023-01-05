/*
 * ActionsHSBisSep1.cpp
 *
 *  Created on: 15.12.2022
 *      Author: Daniel Drefs Fernandes
 */

#include "ActionsHSBisSep1.h"

ActionsHSBisSep1::~ActionsHSBisSep1() {

}

void ActionsHSBisSep1::setupConnection(){
	if ((logikID = name_open(LOGIK, NAME_FLAG_ATTACH_GLOBAL)) == -1) {
		perror("[FSM_HSbisSeperator] name_open failed");
		exit(EXIT_FAILURE);
	}
}

void ActionsHSBisSep1::setMetallTrue(){
	if(wsListen->ws_list_HS_bis_Seperator.front().getWsTyp() == HOCH_MB){
		wsListen->ws_list_HS_bis_Seperator.front().setWsTyp(HOCH_MBM);
	} else{
		wsListen->ws_list_HS_bis_Seperator.front().setWsTyp(UNBEKANNT);
	}
}

void ActionsHSBisSep1::WsPassierenGefordert(){
	int temp = wsListen->sortierReihenfolge.front();
	wsListen->sortierReihenfolge.pop_front();
	wsListen->sortierReihenfolge.push_back(temp);
	Werkstueck temp_ws = wsListen->ws_list_HS_bis_Seperator.front();
	wsListen->ws_list_HS_bis_Seperator.pop_front();
	temp_ws.setTimestamp(zeitmanager->getTime());
	wsListen->ws_list_passieren.push_back(temp_ws);
	if (MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT,
	CODE_FBM_1, WS_PASSIEREN) == -1) {
		perror("[FSM_HSbisSeperator] MsgSendPulse failed");
		exit(EXIT_FAILURE);
	}
}

void ActionsHSBisSep1::WsPassierenNichtGefordert(){
	Werkstueck temp_ws = wsListen->ws_list_HS_bis_Seperator.front();
	wsListen->ws_list_HS_bis_Seperator.pop_front();
	temp_ws.setTimestamp(zeitmanager->getTime());
	wsListen->ws_list_passieren.push_back(temp_ws);
	if (MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT,
	CODE_FBM_1, WS_PASSIEREN) == -1) {
		perror("[FSM_HSbisSeperator] MsgSendPulse failed");
		exit(EXIT_FAILURE);
	}
}

void ActionsHSBisSep1::WsNichtAussortierbar(){
	if (MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT,
	CODE_FBM_1, WS_NICHT_AUSSORTIERBAR) == -1) {
		perror("[FSM_HSbisSeperator] MsgSendPulse failed");
		exit(EXIT_FAILURE);
	}
}

void ActionsHSBisSep1::WsAussortieren(){
	Werkstueck temp_ws = wsListen->ws_list_HS_bis_Seperator.front();
	wsListen->ws_list_HS_bis_Seperator.pop_front();
	temp_ws.setTimestamp(zeitmanager->getTime());
	wsListen->ws_list_aussortieren.push_back(temp_ws);
	if (MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT,
	CODE_FBM_1, WS_AUSSORTIEREN) == -1) {
		perror("[FSM_HSbisSeperator] MsgSendPulse failed");
		exit(EXIT_FAILURE);
	}
}

void ActionsHSBisSep1::fehlerHoch(){
	if (MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT,
	CODE_FBM_1, FEHLER_HOCH) == -1) {
		perror("[FSM_HSbisSeperator] MsgSendPulse failed");
		exit(EXIT_FAILURE);
	}
}

void ActionsHSBisSep1::fehlerRunter(){
	if (MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT,
	CODE_FBM_1, FEHLER_RUNTER) == -1) {
		perror("[FSM_HSbisSeperator] MsgSendPulse failed");
		exit(EXIT_FAILURE);
	}
}

void ActionsHSBisSep1::entferneWsHSbisSep(){
	wsListen->ws_list_HS_bis_Seperator.pop_front();
}

void ActionsHSBisSep1::schnellRunter(){
	if (MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT,
	CODE_FBM_1, SCHNELL_RUNTER_1) == -1) {
		perror("[FSM_HSbisSeperator] MsgSendPulse failed");
		exit(EXIT_FAILURE);
	}
}

void ActionsHSBisSep1::deleteTimerVerschwunden(){
	zeitmanager->deleteTimer(wsListen->ws_list_HS_bis_Seperator.back().getiD());
}

void ActionsHSBisSep1::eStop(){
	wsListen->ws_list_passieren.clear();
	wsListen->ws_list_aussortieren.clear();
}
