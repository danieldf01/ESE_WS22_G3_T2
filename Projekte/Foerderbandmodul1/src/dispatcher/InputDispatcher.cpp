/*
 * InputDispatcher.cpp
 *
 *  Created on: Nov 13, 2022
 *      Author: Bardia
 */
#include "InputDispatcher.h"

using namespace std;

InputDispatcher::InputDispatcher(HALAktorik &hal) {
	this->hal = &hal;
	this->qnetHandler = QnetHandler();
	this->attach=qnetHandler.openServer(INPUTDISPATCHER);
}

InputDispatcher::~InputDispatcher() {
	//TODO Destruktor
}

void InputDispatcher::receiveSignal() {
	while (1) {
		int rcvid;
		_pulse pulse;
		rcvid = MsgReceive(attach->chid, &pulse, sizeof(_pulse), NULL);

		if (rcvid == -1) {
			perror("[InputDispatcher] MsgReceive failed");
			exit(EXIT_FAILURE);
			break;
		}

		else if (rcvid == 0) {
			if (estop) {
				switch (pulse.value.sival_int) {

				case ESTOP_AUS:
					hal->ampel->lampeBlinkenAus(Rot);
					estop = false;
					break;

				case ESTOP_AUS_2:
					hal->ampel->lampeBlinkenAus(Rot);
					estop = false;
					break;
				}
			} else {
				switch(pulse.value.sival_int){

				case WATCHDOG_ESTOP:
				{
					cout << "activated watchdog estop on fbm1" << endl;
					hal->eStopp();
					estop=true;
					break;
				}

				case ESTOP_AN:
				{
//					thread e(&Ampel::blinken, hal->ampel, Rot, HALBESEKUNDE);
//					e.detach();
					estop=true;
					break;
				}

				case ESTOP_AN_2:{
					hal->eStopp();
//					thread e(&Ampel::blinken, hal->ampel, Rot, HALBESEKUNDE);
//					e.detach();
					estop=true;
					break;
				}

				case BETRIEBSMODUS_AN:
					hal->lampe->lampeGruenAn();
					break;

				case BETRIEBSMODUS_AUS:
					hal->lampe->lampeGruenAus();
					break;
				case SERVICE_MODE_AN:
				{
					thread t_service_mode(&Ampel::blinken, hal->ampel, Gruen, SEKUNDE);
					t_service_mode.detach();
					break;
				}
				case SERVICE_MODE_AUS:
					hal->ampel->lampeBlinkenAus(Gruen);
					break;

				case FEHLER_AN:
				{
//					hal->sortierer->sortiererEinfahren();
					if(hal->ampel->blinkenRot){
						hal->ampel->zeitRot=HALBESEKUNDE;
					}
					else{
					thread t_fehlerAn(&Ampel::blinken, hal->ampel, Rot, HALBESEKUNDE);
					t_fehlerAn.detach();
					}
					break;
				}

				case FEHLER_AUS:
					hal->ampel->lampeBlinkenAus(Rot);
					hal->lampe->lampeRotAus();
					break;

				case FEHLER_QUITTIERT:
				{
					hal->lampe->lampeRotAn();
//					thread t_fehler_quittiert(&InputDispatcher::fehlerQuittiert, this);
//					t_fehler_quittiert.detach();
					break;
				}
				case FEHLER_G_UNQUITTIERT:
				{
					if(hal->ampel->blinkenRot){
						hal->ampel->zeitRot=SEKUNDE;
					}
					else{
					thread t_fehler_g_unq(&Ampel::blinken, hal->ampel, Rot, SEKUNDE);
					t_fehler_g_unq.detach();
					}
					break;
				}

				case STOP_AN:
					hal->laufband->laufbandStopAn();
					break;

				case STOP_AUS:
					hal->laufband->laufbandStopAus();
					break;

				case MOTOR_AN:
					hal->laufband->laufbandRechtsAn();
					break;

				case MOTOR_AUS:
					hal->laufband->laufbandRechtsAus();
					break;

				case MOTOR_STOP_AN:
					hal->laufband->laufbandStopAn();
					break;

				case MOTOR_STOP_AUS:
					hal->laufband->laufbandStopAus();
					break;

				case MOTOR_LANGSAM_AN:
					hal->laufband->laufbandLangsamAn();
					break;

				case MOTOR_LANGSAM_AUS:
					hal->laufband->laufbandLangsamAus();
					break;

				case RUTSCHE_VOLL:
				{
					hal->ampel->lampeBlinkenAus(Gelb);
					thread t_rutscheVoll(&Ampel::blinken, hal->ampel, Gelb, HALBESEKUNDE);
					t_rutscheVoll.detach();
					break;
				}

				case RUTSCHE_FREI:
					hal->ampel->lampeBlinkenAus(Gelb);
					break;

				case SL_Q1_AN:
					hal->bedienpanel->signalleuchteQ1An();
					break;

				case SL_Q1_AUS:
					hal->bedienpanel->signalleuchteQ1Aus();
					break;
				case LED_START_AN:
					hal->bedienpanel->ledStartAn();
					break;
				case LED_START_AUS:
					hal->bedienpanel->ledStartAus();
					break;
				case LED_RESET_AN:
					hal->bedienpanel->ledResetAn();
					break;
				case LED_RESET_AUS:
					hal->bedienpanel->ledResetAus();
					break;
				case SEP_AN:
					hal->sortierer->sortiererAusfahren();
					break;

				case SEP_AUS:
					hal->sortierer->sortiererEinfahren();
					break;

				}//END SWITCH
			}
		}

		else if((_IO_BASE <= pulse.type) && (pulse.type <= _IO_MAX)) {
			if(pulse.type == _IO_CONNECT){
				cout << "[InputDispatcher] received _IO_CONNECT via sync. message" << endl;
				MsgReply(rcvid, EOK, NULL, 0);
			}
			//continue;
		} else {
			printf("[InputDispatcher] received an unexpected sync. message with the type = 0x04X\n", pulse.type);
			MsgError(rcvid, ENOSYS);
		}
	}
}

void InputDispatcher::test() {
	hal->lampe->lampeGruenAn();
	hal->laufband->laufbandRechtsAn();
}

void InputDispatcher::test2() {
	hal->ampel->lampeBlinkenAus(Gelb);
}

void InputDispatcher::fehlerQuittiert(){
	hal->ampel->lampeBlinkenAus(Rot);
	this_thread::sleep_for(chrono::milliseconds(500));
	hal->lampe->lampeRotAn();
}
