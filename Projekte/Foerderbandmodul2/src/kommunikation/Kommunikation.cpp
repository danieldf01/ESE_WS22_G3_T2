/*
 * Kommunikation.cpp
 *
 *  Created on: 25.11.2022
 *      Author: Daniel Drefs Fernandes
 */

#include "Kommunikation.h"

using namespace std;

Kommunikation::Kommunikation(OutputDispatcher &oD) {
	outputDispatcher = &oD;
	qnetHandler = new QnetHandler();
	watchdogES = false;
	attach = qnetHandler->openServer(SERVER_KOM_SLAVE);
}

Kommunikation::~Kommunikation() {
	// TODO Auto-generated destructor stub
}

void Kommunikation::init() {

	coid_indis = qnetHandler->connectServer(SERVER_INDIS);
	if (coid_indis == -1) {
		perror("[KommunikationSlave] name_open connect to InputDispatcher failed");
		exit(EXIT_FAILURE);
	}
	cout << "[KommunikationSlave] connected to InputDispatcher" << endl;
	coid_kom_m = qnetHandler->connectServer(SERVER_KOM_MASTER);
	if (coid_kom_m == -1) {
		perror("[KommunikationSlave] name_open connect to KommunikationMaster failed");
		exit(EXIT_FAILURE);
	}
	cout << "[KommunikationSlave] connected to KommunikationMaster" << endl;

}

void Kommunikation::receiveSignal() {
	while (1) {
		int rcvid;
		_pulse pulse;
		rcvid = MsgReceive(attach->chid, &pulse, sizeof(_pulse), NULL);
		if (rcvid == -1) {	// error case
			perror("[KommunikationSlave] MsgReceive failed");
			exit(EXIT_FAILURE);
		}
		if (rcvid == 0) {		// pulse received
			switch (pulse.code) {

			case CODE_FBM_1:	//received message from FBM1
				pulseFBM1(pulse.value.sival_int);
				break;

			case CODE_FBM_2:	//received message from FBM2 (OutputDispatcher)
				pulseFBM2(pulse.value.sival_int);
				break;

			case CODE_ADC_2:	//ADC Wert Anlage 2
				sendPulse(coid_kom_m, SIGEV_PULSE_PRIO_INHERIT, CODE_ADC_2, pulse.value.sival_int);
				break;

			default:
				qnetHandler->handle_pulse(pulse, rcvid, SERVER_KOM_MASTER);
			}
			continue;
		} else {	// received some sync. message
			if (pulse.type == _IO_CONNECT) {
				cout << "[KommunikationSlave] received _IO_CONNECT (sync. message)" << endl;
				MsgReply(rcvid, EOK, NULL, 0);
			} else {
				printf("[KommunikationSlave] received unexpected sync. message with the type = 0x%04X and value = %d\n",
						pulse.type, pulse.value.sival_int);
				MsgError(rcvid, ENOSYS);
			}
			continue;
		}
	}
	name_detach(attach, 0);
}


/**
 *
 * PULSE VON FBM1
 *
 */
void Kommunikation::pulseFBM1(int value){
	switch (value) {

	case WATCHDOG_ESTOP:
		sendPulse(coid_indis, sched_get_priority_max(SCHED_FIFO), CODE_FBM_1, WATCHDOG_ESTOP);
		break;

	case ESTOP_AN:
		sendPulse(coid_indis, sched_get_priority_max(SCHED_FIFO), CODE_FBM_1, ESTOP_AN_2);
		break;
	case ESTOP_AUS:
		sendPulse(coid_indis, sched_get_priority_max(SCHED_FIFO), CODE_FBM_1, ESTOP_AUS_2);
		break;

		//init watchdog
	case WATCHDOG_INIT: {
		init();
		sendPulse(coid_kom_m, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_2, WATCHDOG_INIT);
		watchdog = new Watchdog(attach->chid);
		thread startWD(&Watchdog::init, ref(watchdog));
		startWD.detach();
		break;
	}

	/*
	 * Watchdog notify
	 */
	case WATCHDOG_NOTIF:
		watchdogM.lock();
		if(!watchdogES) {
			watchdog->notify();
		}
		watchdogM.unlock();
		break;

	case INIT_NOTIF:
		init();
		break;

	case WEICHE1:
		if(outputDispatcher->auswerfer==true){
		sendPulse(coid_kom_m, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_2, AUSWERFER2);
		}
		else{
		sendPulse(coid_kom_m, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_2, WEICHE2);
		}
		break;
	case FEHLER_AN:
		sendPulse(coid_indis, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, FEHLER_AN);
		break;
	case FEHLER_AUS:
		sendPulse(coid_indis, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, FEHLER_AUS);
		break;

	case STOP_AN:
		sendPulse(coid_indis, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, STOP_AN);
		break;
	case STOP_AUS:
		sendPulse(coid_indis, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, STOP_AUS);
		break;

	case MOTOR_AN:
		sendPulse(coid_indis, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, MOTOR_AN);
		break;
	case MOTOR_AUS:
		sendPulse(coid_indis, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, MOTOR_AUS);
		break;

	case MOTOR_STOP_AN:
		sendPulse(coid_indis, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, MOTOR_STOP_AN);
		break;
	case MOTOR_STOP_AUS:
		sendPulse(coid_indis, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, MOTOR_STOP_AUS);
		break;

	case MOTOR_LANGSAM_AN:
		sendPulse(coid_indis, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, MOTOR_LANGSAM_AN);
		break;
	case MOTOR_LANGSAM_AUS:
		sendPulse(coid_indis, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, MOTOR_LANGSAM_AUS);
		break;

	case SEP_AN:
		sendPulse(coid_indis, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, SEP_AN);
		break;
	case SEP_AUS:
		sendPulse(coid_indis, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, SEP_AUS);
		break;

	case RUTSCHE_VOLL:
		sendPulse(coid_indis, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, RUTSCHE_VOLL);
		break;
	case RUTSCHE_FREI:
		sendPulse(coid_indis, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, RUTSCHE_FREI);
		break;

	case BETRIEBSMODUS_AN:
		sendPulse(coid_indis, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, BETRIEBSMODUS_AN);
		break;
	case BETRIEBSMODUS_AUS:
		sendPulse(coid_indis, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, BETRIEBSMODUS_AUS);
		break;
	case SERVICE_MODE_AN:
		sendPulse(coid_indis, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, SERVICE_MODE_AN);
		break;
	case SERVICE_MODE_AUS:
		sendPulse(coid_indis, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, SERVICE_MODE_AUS);
		break;
	case FEHLER_QUITTIERT:
		cout << "received fehler quittiert" << endl;
		sendPulse(coid_indis, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, FEHLER_QUITTIERT);
		break;
	case FEHLER_G_UNQUITTIERT:
		sendPulse(coid_indis, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, FEHLER_G_UNQUITTIERT);
		break;
	case LED_START_AN:
		sendPulse(coid_indis, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_1, LED_START_AN);
		break;
	case LED_START_AUS:
		sendPulse(coid_indis, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_1, LED_START_AUS);
		break;
	case LED_RESET_AN:
		sendPulse(coid_indis, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_1, LED_RESET_AN);
		break;
	case LED_RESET_AUS:
		sendPulse(coid_indis, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_1, LED_RESET_AUS);
		break;
	}
}

/**
 *
 * PULSE VON FBM2
 *
 */
void Kommunikation::pulseFBM2(int value){
	switch (value) {

	case E_STOP_AN:
		sendPulse(coid_kom_m, sched_get_priority_max(SCHED_FIFO), CODE_FBM_2, E_STOP_AN);
		break;
	case E_STOP_AUS:
		sendPulse(coid_kom_m, sched_get_priority_max(SCHED_FIFO), CODE_FBM_2, E_STOP_AUS);
		break;

	case WATCHDOG_ESTOP:
		watchdogM.lock();
		watchdogES = true;
		watchdogM.unlock();
		cout << "ESTOPP AKTIV" << endl;
		sendPulse(coid_kom_m, sched_get_priority_max(SCHED_FIFO), CODE_FBM_2, WATCHDOG_ESTOP);
		watchdog->stopTimer();
		sendPulse(coid_indis, sched_get_priority_max(SCHED_FIFO), CODE_FBM_2, WATCHDOG_ESTOP);
		break;

	case WATCHDOG_SEND_NOTIF:
		watchdogM.lock();
		if (!watchdogES) {
			sendPulse(coid_kom_m, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_2, WATCHDOG_NOTIF);
		}
		watchdogM.unlock();
		break;


	case LS_ANFANG_AN:
		sendPulse(coid_kom_m, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_2, LS_ANFANG_AN);
		break;
	case LS_ANFANG_AUS:
		sendPulse(coid_kom_m, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_2, LS_ANFANG_AUS);
		break;

	case HS_HOCH_OK_AN:
		sendPulse(coid_kom_m, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_2, HS_HOCH_OK_AN);
		break;
	case HS_HOCH_OK_AUS:
		sendPulse(coid_kom_m, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_2, HS_HOCH_OK_AUS);
		break;

	case LS_SEPERATOR_AN:
		sendPulse(coid_kom_m, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_2, LS_SEPERATOR_AN);
		break;
	case LS_SEPERATOR_AUS:
		sendPulse(coid_kom_m, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_2, LS_SEPERATOR_AUS);
		break;

	case METALLSENSOR_AN:
		sendPulse(coid_kom_m, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_2, METALLSENSOR_AN);
		break;
	case METALLSENSOR_AUS:
		sendPulse(coid_kom_m, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_2, METALLSENSOR_AUS);
		break;

	case LS_ZUSTAND_SEPERATOR_AN:
		sendPulse(coid_kom_m, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_2, LS_ZUSTAND_SEPERATOR_AN);
		break;
	case LS_ZUSTAND_SEPERATOR_AUS:
		sendPulse(coid_kom_m, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_2, LS_ZUSTAND_SEPERATOR_AUS);
		break;

	case LS_RUTSCHE_AN:
		sendPulse(coid_kom_m, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_2, LS_RUTSCHE_AN);
		break;
	case LS_RUTSCHE_AUS:
		sendPulse(coid_kom_m, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_2, LS_RUTSCHE_AUS);
		break;

	case LS_ENDE_AN:
		sendPulse(coid_kom_m, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_2, LS_ENDE_AN);
		break;
	case LS_ENDE_AUS:
		sendPulse(coid_kom_m, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_2, LS_ENDE_AUS);
		break;

	case T_START_AN:
		sendPulse(coid_kom_m, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_2, T_START_AN);
		break;
	case T_START_AUS:
		sendPulse(coid_kom_m, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_2, T_START_AUS);
		break;

	case T_STOP_AN:
		sendPulse(coid_kom_m, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_2, T_STOP_AN);
		break;
	case T_STOP_AUS:
		sendPulse(coid_kom_m, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_2, T_STOP_AUS);
		break;

	case T_RESET_AN:
		sendPulse(coid_kom_m, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_2, T_RESET_AN);
		break;
	case T_RESET_AUS:
		sendPulse(coid_kom_m, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_2, T_RESET_AUS);
		break;

	}
}

void Kommunikation::sendPulse(int coid, int prio, int code, int value) {
	//TODO test pulse message, muss vorher je nach Fall konstruiert werden
	if ((MsgSendPulse(coid, prio, code, value)) != 0) {
		perror("[KommunikationSlave] failed to send pulse message");
		exit(EXIT_FAILURE);
	}
}
