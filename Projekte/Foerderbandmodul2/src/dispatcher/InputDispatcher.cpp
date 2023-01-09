/*
 * InputDispatcher.cpp
 *
 *  Created on: Nov 13, 2022
 *      Author: Bardia
 */
#include "InputDispatcher.h"

using namespace std;
//global variables
//Sensorik senorik
//Aktorik aktorik
//QnetHandler?

InputDispatcher::InputDispatcher(HALAktorik &hal) {
	this->hal = &hal;
	this->qnetHandler = QnetHandler();
	this->attach=qnetHandler.openServer(SERVER_INDIS);

	//init();

	//TODO generate Qnet Server for Logic (mit QnetHandler?)
	//Objekte für Globale variablen erstellen
}

InputDispatcher::~InputDispatcher() {
	//TODO Destruktor
}

void InputDispatcher::receiveSignal() {
	//TODO Qnet Server wartet auf Message/Pulse von der Logik in einer while loop
	//Der Inhalt der Message/Pulse wird über einem switch case verarbeitet

	while(1){
		int rcvid;
		_pulse pulse;
		rcvid = MsgReceive(attach->chid, &pulse, sizeof(_pulse), NULL);

		if(rcvid == -1){
			perror("[InputDispatcher] MsgReceive failed");
			break;
		}

		else if(rcvid == 0){
			//handle pulse message in switch case
			//TODO switch case behandlung
			if(estop){
				switch(pulse.value.sival_int){

				case ESTOP_AUS:
					hal->ampel->lampeBlinkenAus(Rot);
					estop=false;
					cout << "estop false" << endl;

					break;

				case ESTOP_AUS_2:
					hal->ampel->lampeBlinkenAus(Rot);
					estop=false;
					cout << "estop false" << endl;
					break;
				}

			}
			else{

			switch(pulse.value.sival_int){

				case ESTOP_AN:
				{
					thread e(&Ampel::blinken, hal->ampel, Rot, HALBESEKUNDE);
					e.detach();
					estop=true;
					cout << "estop true" << endl;
					break;
				}
				case ESTOP_AN_2:
				{
					hal->eStopp();
					thread e(&Ampel::blinken, hal->ampel, Rot, HALBESEKUNDE);
					e.detach();
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
					//TODO Laufbandmotor fsm counter hoch
					hal->sortierer->sortiererEinfahren();
					hal->ampel->lampeBlinkenAus(Rot);
					thread e(&Ampel::blinken, hal->ampel, Rot, HALBESEKUNDE);
					e.detach();
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
					hal->ampel->lampeBlinkenAus(Rot);
					thread e(&Ampel::blinken, hal->ampel, Rot, SEKUNDE);
					e.detach();
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

				case SEP_AUS:
					hal->sortierer->sortiererEinfahren();
					break;

				case SEP_AN:
					hal->sortierer->sortiererAusfahren();

					break;

				case RUTSCHE_VOLL:
					{
						hal->ampel->lampeBlinkenAus(Gelb);
						thread t_rutscheVoll(&Ampel::blinken, hal->ampel, Gelb, HALBESEKUNDE);
						t_rutscheVoll.detach();
						break;
					}
					break;

				case RUTSCHE_FREI:
					hal->ampel->lampeBlinkenAus(Gelb);

					break;
				case WATCHDOG_ESTOP:
				{
					hal->eStopp();
					thread e(&Ampel::blinken, hal->ampel, Rot, HALBESEKUNDE);
					e.detach();
					estop=true;
					break;
				}
			}
			}
		}

		else if((_IO_BASE <= pulse.type) && (pulse.type <= _IO_MAX)){
			if(pulse.type == _IO_CONNECT){
				cout << "[InputDispatcher] received _IO_CONNECT via sync. message" << endl;
				MsgReply(rcvid, EOK, NULL, 0);
			}
			//continue;
		}
		else {
		printf("[InputDispatcher] received an unexpected sync. message with the type = 0x04X\n", pulse.type);
		MsgError(rcvid, ENOSYS);
		}
	}
}

int InputDispatcher::init() {
	if ((attach = name_attach(NULL, SERVER_INDIS, NAME_FLAG_ATTACH_GLOBAL))
			== NULL) {
		perror("[InputDispatcher] name_attach failed");
		return EXIT_FAILURE;
	}
	return 0;
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
	this_thread::sleep_for(chrono::milliseconds(1000));
	hal->lampe->lampeRotAn();
}
