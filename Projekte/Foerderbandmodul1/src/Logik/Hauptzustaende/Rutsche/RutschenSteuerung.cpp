/*
 * RutscheLeer.cpp
 *
 *  Created on: 15.12.2022
 *      Author: acy003
 */

#include "RutschenSteuerung.h"


using namespace std;
RutschenSteuerung::RutschenSteuerung() {
	// TODO Hier wurden die Variablen jetzt folgend init:
	logikID = 1;
	rutscheVoll1 = false;
	rutscheFrei1 = true;
	rutscheVoll2 = false;
	rutscheFrei2 = true;
}

RutschenSteuerung::~RutschenSteuerung() {
	// TODO Auto-generated destructor stub
}

void RutschenSteuerung::handlePulse(int code, int wert){
	if(wert==E_STOP_AN){
		rutscheFrei1=false;
		rutscheFrei2=false;
		rutscheVoll1=false;
		rutscheVoll2=false;
	}
	if(code==1){
		switch(wert){

		case LS_RUTSCHE_AN:
			rutscheFrei1=false;
			initTimer(1);
			break;
		case LS_RUTSCHE_AUS:
			rutscheFrei1=true;
			if(rutscheVoll1){
				MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_1,WARNUNG_AUS);
				rutscheVoll1=false;
			}
			else{
				destroyTimer(1);
			}
			break;
		case TIMER_RUTSCHE:
			if(!rutscheFrei1){
				MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_1,WARNUNG_AN);
				rutscheVoll1=true;
			}
			break;


		}
	}
	else{
		switch(wert){
		case LS_RUTSCHE_AN:
			rutscheFrei2=false;
			initTimer(2);
			break;
		case LS_RUTSCHE_AUS:
			rutscheFrei2=true;
			if(rutscheVoll2){
				MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_2,WARNUNG_AUS);
				rutscheVoll2=false;
			}
			else{
				destroyTimer(2);
			}
			break;
		case TIMER_RUTSCHE:
			if(!rutscheFrei2){
				MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_2,WARNUNG_AN);
				rutscheVoll2=true;
			}
			break;


		}
	}
}
void RutschenSteuerung::initTimer(int code){
	SIGEV_PULSE_INIT(&pruefTimerEvent, logikID, SIGEV_PULSE_PRIO_INHERIT,_PULSE_CODE_MINAVAIL+code ,TIMER_RUTSCHE);
	if(code ==1){
		timer_create(CLOCK_REALTIME, &pruefTimerEvent, &pruefTimerID1);
		pruefTimer.it_value.tv_sec = 0;
		pruefTimer.it_value.tv_nsec = 700000000;
		pruefTimer.it_interval.tv_sec = 0;
		pruefTimer.it_interval.tv_nsec = 0;
		timer_settime(pruefTimerID1, 0, &pruefTimer, NULL);
	}
	else{
		timer_create(CLOCK_REALTIME, &pruefTimerEvent, &pruefTimerID2);
		pruefTimer.it_value.tv_sec = 0;
		pruefTimer.it_value.tv_nsec = 700000000;
		pruefTimer.it_interval.tv_sec = 0;
		pruefTimer.it_interval.tv_nsec = 0;
		timer_settime(pruefTimerID2, 0, &pruefTimer, NULL);
	}

}
void RutschenSteuerung::destroyTimer(int code){
		switch(code){
		case 1:
			if ((timer_delete(pruefTimerID1)) != 0) {
				perror("[Rutsche] Timer_delete failed");
				break;
		case 2:
			if ((timer_delete(pruefTimerID2)) != 0) {
				perror("[Rutsche] Timer_delete failed");

				break;
			}
			}
		}
}

//static bool RutschenSteuerung::getRutscheVoll1(){
//	return rutscheVoll1;
//}
//
//static bool RutschenSteuerung::getRutscheVoll2(){
//	return rutscheVoll2;
//}
