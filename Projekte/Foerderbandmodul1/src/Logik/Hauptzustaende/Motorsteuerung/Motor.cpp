/*
 * Motor.cpp
 *
 *  Created on: 12.12.2022
 *      Author: acy003
 */
#include "Motor.h"

Motor::Motor(Zeitmanager *zeitmanager1, Zeitmanager *zeitmanager2) {
	this->zeitFBM1=zeitmanager1;
	this->zeitFBM2=zeitmanager2;
	cnt_langsam=0;
	cnt_schnell=0;
	cnt_stop=0;
	// TODO Auto-generated constructor stub

}

Motor::~Motor() {
	// TODO Auto-generated destructor stub
}
using namespace std;

void Motor::handlePulse(int code,int value){
	if(code==1){
		switch(value){
		case E_STOP_AN:
			cnt_langsam=0;
			cnt_schnell=0;
			cnt_stop=0;
			zeitFBM1->setTimerSpeedStop();
			break;
		case SCHNELL_HOCH_1:
			if(cnt_schnell ==0){
				MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_1,MOT_R_AN_1);
				if(cnt_stop>0){
					zeitFBM1->setTimerSpeedStop();
				}
				else if(cnt_langsam>0){
					zeitFBM1->setTimerSpeedLangsam();
				}
				else if(cnt_stop<=0){
					zeitFBM1->setTimerSpeedSchnell();
				}

			}
			cnt_schnell++;
			break;
		case SCHNELL_RUNTER_1:
			cnt_schnell--;
			if(cnt_schnell <=0){
				MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_1,MOT_R_AUS_1);
				zeitFBM1->setTimerSpeedStop();


			}
			break;
		case LANGSAM_HOCH_1:
			if(cnt_langsam==0){
				MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_1,MOT_LANGSAM_AN_1);
				zeitFBM1->setTimerSpeedLangsam();
			}
			cnt_langsam++;
			break;
		case LANGSAM_RUNTER_1:
			cnt_langsam--;
			if(cnt_langsam<=0){
				MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_1,MOT_LANGSAM_AUS_1);
				if(cnt_stop>0){
					zeitFBM1->setTimerSpeedStop();

				}
				else if(cnt_schnell>0){
					zeitFBM1->setTimerSpeedSchnell();

				}
			}
			break;
		case STOP_HOCH_1:
			MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_1,MOT_STOP_AN_1);
			zeitFBM1->setTimerSpeedStop();

			cnt_stop++;
			break;
		case STOP_RUNTER_1:
			cnt_stop--;
			if(cnt_stop<=0){
				MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_1,MOT_STOP_AUS_1);
				cnt_stop=0;
				if(cnt_langsam>0){
					zeitFBM1->setTimerSpeedLangsam();

				}
				else if(cnt_schnell>0){
					zeitFBM1->setTimerSpeedSchnell();

				}
				else{
					zeitFBM1->setTimerSpeedStop();

				}
			}
			break;
		}
	}
	else{
		switch(value){
		case E_STOP_AN:
			cnt_langsam=0;
			cnt_schnell=0;
			cnt_stop=0;
			zeitFBM2->setTimerSpeedStop();
			break;
		case SCHNELL_HOCH_2:
			if(cnt_schnell ==0){
				MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_2,MOT_R_AN_2);
				zeitFBM2->setTimerSpeedSchnell();
			}
			cnt_schnell++;
			break;
		case SCHNELL_RUNTER_2:
			cnt_schnell--;
			if(cnt_schnell <=0){
				MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_2,MOT_R_AUS_2);
				zeitFBM2->setTimerSpeedStop();
			}
			break;
		case LANGSAM_HOCH_2:
			if(cnt_langsam==0){
				MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_2,MOT_LANGSAM_AN_2);
				zeitFBM2->setTimerSpeedLangsam();
			}
			cnt_langsam++;
			break;
		case LANGSAM_RUNTER_2:
			cnt_langsam--;
			if(cnt_langsam<=0){
				MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_2,MOT_LANGSAM_AUS_2);
				if(cnt_stop>0){
					zeitFBM2->setTimerSpeedStop();
				}
				else if(cnt_schnell>0){
					zeitFBM2->setTimerSpeedSchnell();
				}
			}
			break;
		case STOP_HOCH_2:
			if(cnt_stop<=0){
				MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_2,MOT_STOP_AN_2);
				zeitFBM2->setTimerSpeedStop();
			}
			cnt_stop++;
			break;
		case STOP_RUNTER_2:
			cnt_stop--;
			if(cnt_stop<=0){
				MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_2,MOT_STOP_AUS_2);
				cnt_stop=0;
				if(cnt_langsam>0){
					zeitFBM2->setTimerSpeedLangsam();
				}
				else if(cnt_schnell>0){
					zeitFBM2->setTimerSpeedSchnell();
				}
				else{
					zeitFBM2->setTimerSpeedStop();
				}
			}
			break;
		}
	}
}
