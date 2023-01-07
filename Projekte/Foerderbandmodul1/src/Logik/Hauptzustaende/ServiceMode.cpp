/*
 * ServiceMode.cpp
 *
 *  Created on: Jan 6, 2023
 *      Author: bardi
 */

#include "ServiceMode.h"

using namespace std;

void ServiceMode::handlePulse(int code, int value){
	switch(code){

	case CODE_FBM_1: //pulse von FBM1
		pulseFBM1(value);
		break;

	case CODE_FBM_2: //Pulse von FBM2
		pulseFBM2(value);
		break;

	case CODE_ADC_1: //Pulse von ADC_1
//		MsgSendPulse(auswertungID1, SIGEV_PULSE_PRIO_INHERIT,	PULSE_ADC_SAMLING_WINDOW_DONE, value);
		//cout << "ADC1 Wert erhalten" << value << endl;
		//FMB1 ADC_WERT
		break;

	case CODE_ADC_2: //Pulse von ADC_2
//		MsgSendPulse(auswertungID2, SIGEV_PULSE_PRIO_INHERIT,	PULSE_ADC_SAMLING_WINDOW_DONE, value);
		//FMB2 ADC_WERT
		break;

	}
}



void ServiceMode::pulseFBM1(int value){
	switch(value){

	case LS_ANFANG_AN: 		//active low+
		cout << "LS_ANFANG an" << endl;
		break;
	case LS_ANFANG_AUS:
		cout << "LS_ANFANG aus" << endl;
		if(durchlauf==1){
		cout << "Zeit LS_A Schnell"<< zeitFBM1->getTime()<<endl;
		zeitLSAaus= zeitFBM1->getTime();
		}
		if(durchlauf==2){
			cout<<"Zeit LS_A langsam"<< zeitFBM1->getTime()<<endl;
		}
		break;
	case HS_HOCH_OK_AN:
		cout << "HOCH_OK an" << endl;
		if(durchlauf==1){
			cout << "Zeit HS_OK AN Schnell"<< zeitFBM1->getTime()<<endl;
			zeitLSAbisHS= zeitFBM1->getTime() - zeitLSAaus;
		}
		if(durchlauf==2){
			cout<<"Zeit HS_OK AN langsam"<< zeitFBM1->getTime() <<endl;
		}
		break;
	case HS_HOCH_OK_AUS: //active high+
		cout << "HOCH_OK aus" << endl;
		if(durchlauf==1){
			cout << "Zeit HOCH_OK AUS Schnell"<< zeitFBM1->getTime()<<endl;
			zeitHSaus= zeitFBM1->getTime();
		}
		if(durchlauf==2){
			cout<<"Zeit HOCH_OK AUS langsam"<< zeitFBM1->getTime() <<endl;
		}
		break;
	case LS_SEPERATOR_AN: //active low+
		if(durchlauf>1){
			MsgSendPulse(inputID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, SEP_AN);
			thread t_durchlassen(&ServiceMode::durchlassen, this,1);
			t_durchlassen.detach();
		}
		cout << " LS_SEPERATOR an" << endl;

		if(durchlauf==2){
			cout<<"Zeit SEPERATOR_AN langsam"<< zeitFBM1->getTime() <<endl;
		}
		if(durchlauf==1){
			cout << "Zeit SEPERATOR AN schnell bis rutsche"<< zeitFBM1->getTime();
			zeitHSbisSep= zeitFBM1->getTime()-zeitHSaus;
			zeitSepAn=zeitHSbisSep;
		}
		break;
	case LS_SEPERATOR_AUS:
		cout << "LS_SEPERATOR aus" << endl;
		if(durchlauf==2){
			cout<<"Zeit SEPERATOR_AUS langsam"<< zeitFBM1->getTime() <<endl;
		}
		if(durchlauf==3){
			cout << "Zeit SEPERATOR AUS schnell bis rutsche"<< zeitFBM1->getTime();
			zeitSepAus= zeitFBM1->getTime();
		}
		break;
	case METALLSENSOR_AN:
		cout << "METALLSENSOR an" << endl;
		break;
	case METALLSENSOR_AUS: //active high+
		cout << "METALLSENSOR aus" << endl;
		break;
	case LS_RUTSCHE_AN: //active low+
		cout << "LS_RUTSCHE an" << endl;
		cout << "Zeit Rutsche an" << zeitFBM1->getTime()<<endl;
		zeitSepbisRutsche=zeitFBM1->getTime() - zeitSepAn;
		break;
	case LS_RUTSCHE_AUS:
		MsgSendPulse(motorID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_1,SCHNELL_RUNTER_1);
		cout << " LS_RUTSCHE aus" << endl;
		break;
	case LS_ENDE_AN:	//active low+
		cout << "LS_ENDE an" << endl;
		cout << "Zeit LS_ENDE AN:"<< zeitFBM1->getTime()<<endl;
		if(durchlauf==3){
		zeitSepbisEnde= zeitFBM1->getTime() - zeitSepAus;
		}
		MsgSendPulse(motorID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_2,SCHNELL_HOCH_2);
		break;
	case LS_ENDE_AUS:
		cout << "LS_ENDE aus" << endl;
		cout << "Zeit LS_ENDE AUS:"<< zeitFBM1->getTime()<<endl;
		if(durchlauf==3){
		zeitEndeAus= zeitFBM1->getTime();
		}
		break;
	case T_START_AN:
		cout << "START an" << endl;
		break;
	case T_START_AUS:  		//active high+
		durchlauf++;
		cout<< "durchlauf:"<<durchlauf<<endl;
		MsgSendPulse(motorID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_1,SCHNELL_HOCH_1);
		if(durchlauf==2){
			MsgSendPulse(inputID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_1,MOTOR_LANGSAM_AN);
		}
		cout << "START aus" << endl;
		break;

	case T_STOP_AN: 	//active low+
		cout << "STOP an" << endl;
		break;
	case T_STOP_AUS:
		cout << "STOP aus" << endl;
		break;
	case T_RESET_AN:
		cout << "RESET an" << endl;
		break;
	case T_RESET_AUS: 	//active high+
		cout << "RESET aus" << endl;
		durchlauf=0;
		break;

	case E_STOP_AN: 	//active low+
		eStop(1);
		break;
	case LS_ZUSTAND_SEPERATOR_AN:	//active high+
		cout << "LS_ZUSTAND_SEPERATOR an" << endl;
		break;
	case LS_ZUSTAND_SEPERATOR_AUS:
		cout << "LS_ZUSTAND_SEPERATOR aus" << endl;
		break;
	case MOT_R_AN_1:
		MsgSendPulse(inputID, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL,
				MOTOR_AN);
		break;

	case MOT_R_AUS_1:
		MsgSendPulse(inputID, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL,
				MOTOR_AUS);
		break;

	case MOT_LANGSAM_AN_1:
		MsgSendPulse(inputID, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL,
				MOTOR_LANGSAM_AN);
		break;

	case MOT_LANGSAM_AUS_1:
		MsgSendPulse(inputID, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL,
				MOTOR_LANGSAM_AUS);
		break;

	case MOT_STOP_AN_1:
		MsgSendPulse(inputID, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL,
				MOTOR_STOP_AN);
		break;

	case MOT_STOP_AUS_1:
		MsgSendPulse(inputID, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL,
				MOTOR_STOP_AUS);
		break;
	}
}

void ServiceMode::pulseFBM2(int value){
	switch(value){

	case LS_ANFANG_AN: 		//active low+
		MsgSendPulse(motorID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_1,SCHNELL_RUNTER_1);
		MsgSendPulse(inputID, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, MOTOR_LANGSAM_AUS);
		cout << "LS_ANFANG 2 an" << endl;
		cout << "LS_ANFANG 2 Zeit:"<< zeitFBM1->getTime();
		if(durchlauf==3){
		zeitEndebisLSA2= zeitFBM1->getTime() - zeitEndeAus;
		}
		break;
	case LS_ANFANG_AUS:
		cout << "LS_ANFANG 2 aus" << endl;
		break;
	case HS_HOCH_OK_AN:
		cout << "HOCH_OK 2 an" << endl;
		break;
	case HS_HOCH_OK_AUS: //active high+
		cout << "HOCH_OK 2 aus" << endl;
		break;
	case LS_SEPERATOR_AN: //active low+
		if(durchlauf>2){
			MsgSendPulse(kommID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, SEP_AN);
			thread t_durchlassen(&ServiceMode::durchlassen, this,2);
			t_durchlassen.detach();
		}
		cout << "LS_SEPERATOR 2 an" << endl;
		break;
	case LS_SEPERATOR_AUS:
		cout << "LS_SEPERATOR 2 aus" << endl;
		break;
	case METALLSENSOR_AN:
		cout << "METALLSENSOR 2 an" << endl;
		break;
	case METALLSENSOR_AUS: //active high+
		cout << "METALLSENSOR 2 aus" << endl;
		break;
	case LS_RUTSCHE_AN: //active low+
		cout << "LS_RUTSCHE 2 an" << endl;
		break;
	case LS_RUTSCHE_AUS:
		MsgSendPulse(motorID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_2, SCHNELL_RUNTER_2);
		cout << "LS_RUTSCHE 2 aus" << endl;
		break;
	case LS_ENDE_AN:	//active low+
		cout << "LS_ENDE 2 an" << endl;


		cout << "ZeitLSAbisHS:"<< zeitLSAbisHS<< " ,ZeitHSbisSep:"<< zeitHSbisSep<< " ,Zeit SepBisRutsche:"<< zeitSepbisRutsche<< " ,ZeitSepBisEnde:"<<zeitSepbisEnde<<" ,ZeitEndeBisLSA2:"<<zeitEndebisLSA2 << endl;

		dateiManager->set_value_of(Konfi_Codes::FBM1_KUERZTE_ZEIT_BIS_HS, zeitLSAbisHS);
		dateiManager->set_value_of(Konfi_Codes::FBM1_KUERZESTE_ZEIT_BIS_SEP, zeitHSbisSep);
		dateiManager->set_value_of(Konfi_Codes::FBM1_LAENGSTE_ZEIT_BIS_LS_RUT, zeitSepbisRutsche);
		dateiManager->set_value_of(Konfi_Codes::FBM1_KUERZESTE_ZEIT_BIS_LS_ENDE, zeitSepbisEnde);
		dateiManager->set_value_of(Konfi_Codes::FBM1_LAENGSTE_ZEIT_WS_UEBERGEBEN, zeitEndebisLSA2);
		dateiManager->speicherInKonfigurationsdatei();
		MsgSendPulse(motorID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_2, SCHNELL_RUNTER_2);
		new (this) Ruhezustand;
		MsgSendPulse(inputID, SIGEV_PULSE_PRIO_INHERIT,_PULSE_CODE_MINAVAIL,SERVICE_MODE_AUS);
		MsgSendPulse(kommID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, SERVICE_MODE_AUS);
		break;
	case LS_ENDE_AUS:
		cout << "LS_ENDE 2 aus" << endl;
		break;
	case T_START_AN:
		cout << "START 2 an" << endl;
		MsgSendPulse(motorID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_2, LANGSAM_HOCH_2);
		break;
	case T_START_AUS:  		//active high+
		MsgSendPulse(motorID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_2, LANGSAM_RUNTER_2);
		cout << "START 2 aus" << endl;
		break;
	case T_STOP_AN: 	//active low+
		cout << "STOP 2 an" << endl;

		break;
	case T_STOP_AUS:
		cout << "STOP 2 aus" << endl;
		break;
	case T_RESET_AN:
		cout << "RESET 2 an" << endl;
		break;
	case T_RESET_AUS: 	//active high+
		cout << "RESET 2 aus" << endl;
		break;
	case E_STOP_AN: 	//active low+
		eStop(2);
		break;
	case LS_ZUSTAND_SEPERATOR_AN:	//active high+
		cout << "LS_ZUSTAND_SEPERATOR 2 an" << endl;
		break;
	case LS_ZUSTAND_SEPERATOR_AUS:
		cout << "LS_ZUSTAND_SEPERATOR 2 aus" << endl;
		break;
	case MOT_LANGSAM_AN_2:
		MsgSendPulse(kommID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, MOTOR_LANGSAM_AN);
		break;
	case MOT_LANGSAM_AUS_2:
		MsgSendPulse(kommID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, MOTOR_LANGSAM_AUS);
		break;

	case MOT_R_AN_2:
		MsgSendPulse(kommID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, MOTOR_AN);
		break;
	case MOT_R_AUS_2:
		MsgSendPulse(kommID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, MOTOR_AUS);
		break;

	case MOT_STOP_AN_2:
		MsgSendPulse(kommID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, MOTOR_STOP_AN);

		break;
	case MOT_STOP_AUS_2:
		MsgSendPulse(kommID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, MOTOR_STOP_AUS);
		break;

	}
}
void ServiceMode::durchlassen(int anlage){
	this_thread::sleep_for(chrono::milliseconds(1000));
	if(anlage==1){
		MsgSendPulse(inputID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, SEP_AUS);
	}
	else{
		MsgSendPulse(kommID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, SEP_AUS);
	}
}
void ServiceMode::updateAuswertung(){

}
void ServiceMode::pulseZeit1(int value){

}

/**
 *
 * PULSE VON zeitFBM2
 *
 */

void ServiceMode::pulseZeit2(int value){

}
void ServiceMode::eStop(int estop){
	cout << "switched to EStop1"<< endl;
	MsgSendPulse(inputID, SIGEV_PULSE_PRIO_INHERIT,_PULSE_CODE_MINAVAIL,BETRIEBSMODUS_AUS );
	MsgSendPulse(motorID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_1,E_STOP_AN );
	MsgSendPulse(motorID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_2,E_STOP_AN);
	MsgSendPulse(fsmLSA1_ID, SIGEV_PULSE_PRIO_INHERIT,_PULSE_CODE_MINAVAIL, E_STOP_AN);
	MsgSendPulse(auswertungID1, SIGEV_PULSE_PRIO_INHERIT,_PULSE_CODE_MINAVAIL, HS_LEEREN);
	MsgSendPulse(auswertungID2, SIGEV_PULSE_PRIO_INHERIT,_PULSE_CODE_MINAVAIL, HS_LEEREN);
	MsgSendPulse(auswertungID1, SIGEV_PULSE_PRIO_INHERIT,_PULSE_CODE_MINAVAIL, MOTOR_STOP_AN);
	MsgSendPulse(auswertungID2, SIGEV_PULSE_PRIO_INHERIT,_PULSE_CODE_MINAVAIL, MOTOR_STOP_AN);
	MsgSendPulse(fsmLSAbisHS1_ID, SIGEV_PULSE_PRIO_INHERIT,_PULSE_CODE_MINAVAIL, E_STOP_AN);
	MsgSendPulse(fsmWsErkennung1_ID, SIGEV_PULSE_PRIO_INHERIT,_PULSE_CODE_MINAVAIL, E_STOP_AN);
	MsgSendPulse(rutschenID, SIGEV_PULSE_PRIO_INHERIT,_PULSE_CODE_MINAVAIL, E_STOP_AN);
	MsgSendPulse(fsmHSbisSep1_ID, SIGEV_PULSE_PRIO_INHERIT,_PULSE_CODE_MINAVAIL, E_STOP_AN);
	MsgSendPulse(fsmSepBisRut1_ID, SIGEV_PULSE_PRIO_INHERIT,_PULSE_CODE_MINAVAIL, E_STOP_AN);
	MsgSendPulse(fsmSepBisLSEnde1_ID, SIGEV_PULSE_PRIO_INHERIT,_PULSE_CODE_MINAVAIL, E_STOP_AN);
	MsgSendPulse(fsmLSA2_ID, SIGEV_PULSE_PRIO_INHERIT,_PULSE_CODE_MINAVAIL, E_STOP_AN);
	zeitFBM1->clearLists();
	zeitFBM2->clearLists();

	//TODO alle EStop Signale auf hoechste Prioritaet setzen?
	MsgSendPulse(kommID, sched_get_priority_max(SCHED_FIFO), CODE_FBM_1, ESTOP_AN);
	fehlerCount=0;
	warnungsCount=0;
	if(estop==1){
		eStop1=true;
	} else{
		eStop2=true;
	}
	new (this) EStop;
}
