/*
 * ActionsSepBisLSEnde.cpp
 *
 *  Created on: 21.12.2022
 *      Author: acx514
 */

#include "ActionsSepBisLSE2.h"

ActionsSepBisLSE2::~ActionsSepBisLSE2() {
}

void ActionsSepBisLSE2::setupConnection(){
	if ((logikID = name_open(LOGIK, NAME_FLAG_ATTACH_GLOBAL)) == -1) {
		perror("[FSM_SepBisLSE2] name_open failed");
		exit(EXIT_FAILURE);
	}
}

void ActionsSepBisLSE2::augabeKonsoleMQTT(){
Werkstueck ws = *wsListen->ws_passieren_2;
		int wsId = ws.getiD();
		int WS_Typ = ws.getWsTyp();
		string wsTypAsString = "Fehler WS Typ nicht gesetzt";
		double wsMeanhight = ws.getMittlereHoehe();
		double wsHeight = ws.getHoehenmesswert();
		bool isUeberschlagen = ws.getUeberschlagen();

		if (WS_Typ == FLACH) {
			wsTypAsString = "FLACH";
		}
		if (WS_Typ == HOCH_OB) {
			wsTypAsString = "HOCH_OB";
		}
		if (WS_Typ == HOCH_MB) {
			wsTypAsString = "HOCH_MB";
		}
		if (WS_Typ == HOCH_MBM) {
			wsTypAsString = "HOCH_MBM";
		}
		if (WS_Typ == UNBEKANNT) {
			wsTypAsString = "UNBEKANNT";
		}


		// Konsolen Ausgabe
		cout << "----Werkstueck Daten----" << endl;
		cout << "wsId" << wsId << endl;
		cout << "wsTyp" << wsTypAsString << endl;
		printf("wsMeanhight %f.2", wsMeanhight);
		printf("wsHeight %f.2", wsHeight);

		if(isUeberschlagen){
			cout << "ist ueberschlagen" << endl;
		}else{
			cout << "nicht ueberschlagen" << endl;
		}


		// MQTT Stuff
		std::string address ="tcp://192.168.235.1:1883";
		std::string clientID="FESTO_Client_Pub";
		std::string topic="Festo";

		MQTTClientHandler *client = new MQTTClientHandler(address, clientID);
		client->senden(topic, wsId, wsTypAsString, wsMeanhight, wsHeight);//TODO FLIPT fehlt
		client->destroy();
}

void ActionsSepBisLSE2::seperatorAn(){
	if (MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_2, TIMER_START_WEICHE) == -1) {
		perror("[FSM_SepBisLSE2] MsgSendPulse failed");
		exit(EXIT_FAILURE);
	}
	if (MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_2, SEP_AN) == -1) {
		perror("[FSM_SepBisLSE2] MsgSendPulse failed");
		exit(EXIT_FAILURE);
	}
}

void ActionsSepBisLSE2::seperatorAus(){
	if (MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_2, SEP_AUS) == -1) {
		perror("[FSM_SepBisLSE2] MsgSendPulse failed");
		exit(EXIT_FAILURE);
	}
}

void ActionsSepBisLSE2::fehlerHoch(){
	if (MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_2, FEHLER_HOCH) == -1) {
		perror("[FSM_SepBisLSE2] MsgSendPulse failed");
		exit(EXIT_FAILURE);
	}
}

void ActionsSepBisLSE2::fehlerRunter(){
	if (MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_2, FEHLER_RUNTER) == -1) {
		perror("[FSM_SepBisLSE2] MsgSendPulse failed");
		exit(EXIT_FAILURE);
	}
}

void ActionsSepBisLSE2::entferneWsPassieren(){
	wsListen->ws_passieren_2 = nullptr;
}

void ActionsSepBisLSE2::schnellRunter(){
	if (MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_2, SCHNELL_RUNTER_2) == -1) {
		perror("[FSM_SepBisLSE2] MsgSendPulse failed");
		exit(EXIT_FAILURE);
	}
}

void ActionsSepBisLSE2::stopHoch(){
	if (MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_2, STOP_HOCH_2) == -1) {
		perror("[FSM_SepBisLSE2] MsgSendPulse failed");
		exit(EXIT_FAILURE);
	}
}

void ActionsSepBisLSE2::stopRunter(){
	if (MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_2, STOP_RUNTER_2) == -1) {
		perror("[FSM_SepBisLSE2] MsgSendPulse failed");
		exit(EXIT_FAILURE);
	}
}

void ActionsSepBisLSE2::deleteTimerVerschwunden(){
	zeitmanager->deleteTimer(wsListen->ws_passieren_2->getiD());
}

void ActionsSepBisLSE2::sendFBM2Bereit() {
	if (MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_2, FBM2_BEREIT) == -1) {
		perror("[FSM_LSAnfang2] MsgSendPulse failed");
		exit(EXIT_FAILURE);
	}
}

void ActionsSepBisLSE2::eStop(){

}
