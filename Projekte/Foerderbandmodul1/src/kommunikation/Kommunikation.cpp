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
	attach = qnetHandler->openServer(SERVER_KOM_MASTER);
}

Kommunikation::~Kommunikation() {

}

void Kommunikation::init() {
	coid_indis = qnetHandler->connectServer(INPUTDISPATCHER);
	if (coid_indis == -1) {
		perror("[KommunikationMaster] name_open connect to InputDispatcher failed");
		exit(EXIT_FAILURE);
	}
	cout << "[KommunikationMaster] connected to InputDispatcher" << endl;
	coid_kom_s = qnetHandler->connectServer(SERVER_KOM_SLAVE);
	if (coid_kom_s == -1) {
		perror("[KommunikationMaster] name_open connect to KommunikationSlave failed");
		exit(EXIT_FAILURE);
	}
	cout << "[KommunikationMaster] connected to KommunikationSlave" << endl;
	MsgSendPulse(coid_kom_s, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, WATCHDOG_INIT);
	MsgSendPulse(coid_kom_s, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, INIT_NOTIF);
}


void Kommunikation::receiveSignal() {
	while (1) {
		int rcvid;
		_pulse pulse;
		rcvid = MsgReceive(attach->chid, &pulse, sizeof(_pulse), NULL);
		if (rcvid == -1) {		// error case
			perror("[KommunikationMaster] MsgReceive failed");
			exit(EXIT_FAILURE);
		}
		if (rcvid == 0) {		// pulse received
			switch (pulse.code) {

			case CODE_FBM_1:	//received message from FBM1 (OutputDispatcher)
				pulseFBM1(pulse.value.sival_int);
				break;

			case CODE_FBM_2: 	//received message from FBM2
				pulseFBM2(pulse.value.sival_int);
				break;

			case CODE_ADC_2:	//ADC Wert Anlage 2
				outputDispatcher->dispatchADC(pulse.value.sival_int, 2);
				break;

			default:	//received some other (unexpected) pulse message
				qnetHandler->handle_pulse(pulse, rcvid, SERVER_KOM_MASTER);
			}
			continue;
		} else {	//handle sync messages
			if (pulse.type == _IO_CONNECT) {	//handle name open from clients
				cout << "[KommunikationMaster] received _IO_CONNECT (sync. message)" << endl;
				MsgReply(rcvid, EOK, NULL, 0);
			} else {		//unexpected sync message
				printf("[KommunikationMaster] received unexpected sync. message with the type = 0x%04X and value = %d\n",
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

	case ESTOP_AN:
		sendPulse(coid_kom_s, sched_get_priority_max(SCHED_FIFO), ESTOP_AN);
		break;
	case ESTOP_AUS:
		sendPulse(coid_kom_s, sched_get_priority_max(SCHED_FIFO), ESTOP_AUS);
		break;

	case WATCHDOG_SEND_NOTIF:
		watchdogM.lock();
		if(!watchdogES){
			sendPulse(coid_kom_s, SIGEV_PULSE_PRIO_INHERIT, WATCHDOG_NOTIF);
		}
		watchdogM.unlock();
		break;

	case WATCHDOG_ESTOP:
		watchdogM.lock();
		watchdogES = true;
		watchdogM.unlock();
		watchdog->stopTimer();
		outputDispatcher->dispatchOutput(WATCHDOG_ESTOP, 1);
		sendPulse(coid_kom_s, sched_get_priority_max(SCHED_FIFO), WATCHDOG_ESTOP);
		break;

		//Aktorik auf Anlage 2 ansprechen
	case FEHLER_AN:
		sendPulse(coid_kom_s, SIGEV_PULSE_PRIO_INHERIT, FEHLER_AN);
		break;
	case FEHLER_AUS:
		sendPulse(coid_kom_s, SIGEV_PULSE_PRIO_INHERIT, FEHLER_AUS);
		break;

	case STOP_AN:
		sendPulse(coid_kom_s, SIGEV_PULSE_PRIO_INHERIT, STOP_AN);
		break;
	case STOP_AUS:
		sendPulse(coid_kom_s, SIGEV_PULSE_PRIO_INHERIT, STOP_AUS);
		break;

	case MOTOR_AN:
		sendPulse(coid_kom_s, SIGEV_PULSE_PRIO_INHERIT, MOTOR_AN);
		break;
	case MOTOR_AUS:
		sendPulse(coid_kom_s, SIGEV_PULSE_PRIO_INHERIT, MOTOR_AUS);
		break;

	case MOTOR_STOP_AN:
		sendPulse(coid_kom_s, SIGEV_PULSE_PRIO_INHERIT, MOTOR_STOP_AN);
		break;
	case MOTOR_STOP_AUS:
		sendPulse(coid_kom_s, SIGEV_PULSE_PRIO_INHERIT, MOTOR_STOP_AUS);
		break;

	case MOTOR_LANGSAM_AN:
		sendPulse(coid_kom_s, SIGEV_PULSE_PRIO_INHERIT, MOTOR_LANGSAM_AN);
		break;
	case MOTOR_LANGSAM_AUS:
		sendPulse(coid_kom_s, SIGEV_PULSE_PRIO_INHERIT, MOTOR_LANGSAM_AUS);
		break;

	case SEP_AN:
		sendPulse(coid_kom_s, SIGEV_PULSE_PRIO_INHERIT, SEP_AN);
		break;
	case SEP_AUS:
		sendPulse(coid_kom_s, SIGEV_PULSE_PRIO_INHERIT, SEP_AUS);
		break;

	case RUTSCHE_VOLL:
		sendPulse(coid_kom_s, SIGEV_PULSE_PRIO_INHERIT, RUTSCHE_VOLL);
		break;
	case RUTSCHE_FREI:
		sendPulse(coid_kom_s, SIGEV_PULSE_PRIO_INHERIT, RUTSCHE_FREI);
		break;

	case BETRIEBSMODUS_AN:
		sendPulse(coid_kom_s, SIGEV_PULSE_PRIO_INHERIT, BETRIEBSMODUS_AN);
		break;
	case BETRIEBSMODUS_AUS:
		sendPulse(coid_kom_s, SIGEV_PULSE_PRIO_INHERIT, BETRIEBSMODUS_AUS);
		break;
	case SERVICE_MODE_AN:
		sendPulse(coid_kom_s, SIGEV_PULSE_PRIO_INHERIT, SERVICE_MODE_AN);
		break;
	case SERVICE_MODE_AUS:
		sendPulse(coid_kom_s, SIGEV_PULSE_PRIO_INHERIT, SERVICE_MODE_AUS);
		break;

	case FEHLER_QUITTIERT:
		sendPulse(coid_kom_s, SIGEV_PULSE_PRIO_INHERIT, FEHLER_QUITTIERT);
		break;

	case FEHLER_G_UNQUITTIERT:
		sendPulse(coid_kom_s, SIGEV_PULSE_PRIO_INHERIT, FEHLER_G_UNQUITTIERT);
		break;
	case LED_START_AN:
		sendPulse(coid_kom_s, SIGEV_PULSE_PRIO_INHERIT, LED_START_AN);
		break;
	case LED_START_AUS:
		sendPulse(coid_kom_s, SIGEV_PULSE_PRIO_INHERIT, LED_START_AUS);
		break;
	case LED_RESET_AN:
		sendPulse(coid_kom_s, SIGEV_PULSE_PRIO_INHERIT, LED_RESET_AN);
		break;
	case LED_RESET_AUS:
		sendPulse(coid_kom_s, SIGEV_PULSE_PRIO_INHERIT, LED_RESET_AUS);
		break;
	case WEICHE1:
		sendPulse(coid_kom_s, SIGEV_PULSE_PRIO_INHERIT, WEICHE1);
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
		outputDispatcher->dispatchOutput(E_STOP_PIN_2, 0);
		break;
	case E_STOP_AUS:
		outputDispatcher->dispatchOutput(E_STOP_PIN_2, 1);
		break;

	case WATCHDOG_ESTOP:
		outputDispatcher->dispatchOutput(WATCHDOG_ESTOP, 1);
		break;

		//init watchdog
	case WATCHDOG_INIT:
		this->watchdog = new Watchdog(attach->chid);
		break;

		/*
		 * Watchdog notify
		 */
	case WATCHDOG_NOTIF:
		watchdogM.lock();
		if(!watchdogES){
			watchdog->notify();
		}
		watchdogM.unlock();
		break;

		/*
		 * pins
		 */
	case LS_ANFANG_AN:
		outputDispatcher->dispatchOutput(LS_ANFANG_PIN_2, 0);
		break;
	case LS_ANFANG_AUS:
		outputDispatcher->dispatchOutput(LS_ANFANG_PIN_2, 1);
		break;

	case HS_HOCH_OK_AN:
		outputDispatcher->dispatchOutput(HS_HOCH_OK_PIN_2, 1);
		break;
	case HS_HOCH_OK_AUS:
		outputDispatcher->dispatchOutput(HS_HOCH_OK_PIN_2, 0);
		break;

	case LS_SEPERATOR_AN:
		outputDispatcher->dispatchOutput(LS_SEPERATOR_PIN_2, 0);
		break;
	case LS_SEPERATOR_AUS:
		outputDispatcher->dispatchOutput(LS_SEPERATOR_PIN_2, 1);
		break;

	case METALLSENSOR_AN:
		outputDispatcher->dispatchOutput(METALLSENSOR_PIN_2, 1);
		break;
	case METALLSENSOR_AUS:
		outputDispatcher->dispatchOutput(METALLSENSOR_PIN_2, 0);
		break;

	case LS_ZUSTAND_SEPERATOR_AN:
		outputDispatcher->dispatchOutput(LS_ZUSTAND_SEPERATOR_PIN_2, 1);
		break;
	case LS_ZUSTAND_SEPERATOR_AUS:
		outputDispatcher->dispatchOutput(LS_ZUSTAND_SEPERATOR_PIN_2, 0);
		break;

	case LS_RUTSCHE_AN:
		outputDispatcher->dispatchOutput(LS_RUTSCHE_PIN_2, 0);
		break;
	case LS_RUTSCHE_AUS:
		outputDispatcher->dispatchOutput(LS_RUTSCHE_PIN_2, 1);
		break;

	case LS_ENDE_AN:
		outputDispatcher->dispatchOutput(LS_ENDE_PIN_2, 0);
		break;
	case LS_ENDE_AUS:
		outputDispatcher->dispatchOutput(LS_ENDE_PIN_2, 1);
		break;

	case T_START_AN:
		outputDispatcher->dispatchOutput(T_START_PIN_2, 1);
		break;
	case T_START_AUS:
		outputDispatcher->dispatchOutput(T_START_PIN_2, 0);
		break;

	case T_STOP_AN:
		outputDispatcher->dispatchOutput(T_STOP_PIN_2, 0);
		break;
	case T_STOP_AUS:
		outputDispatcher->dispatchOutput(T_STOP_PIN_2, 1);
		break;

	case T_RESET_AN:
		outputDispatcher->dispatchOutput(T_RESET_PIN_2, 1);
		break;
	case T_RESET_AUS:
		outputDispatcher->dispatchOutput(T_RESET_PIN_2, 0);
		break;
	case AUSWERFER2:
		outputDispatcher->dispatchOutput(AUSWERFER2, 0);
		break;
	case WEICHE2:
		outputDispatcher->dispatchOutput(WEICHE2, 0);
		break;
	}
}


void Kommunikation::sendPulse(int coid, int prio, int value) {
	if ((MsgSendPulse(coid, prio, _PULSE_CODE_MINAVAIL + 1, value)) == -1) {
		perror("[KommunikationMaster] failed to send pulse message");
		exit(EXIT_FAILURE);
	}
}
