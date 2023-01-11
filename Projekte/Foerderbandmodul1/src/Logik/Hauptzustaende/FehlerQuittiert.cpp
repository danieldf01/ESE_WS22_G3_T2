/*
 * FehlerQuittiert.cpp
 *
 *  Created on: 12.12.2022
 *      Author: acy003
 */

#include "FehlerQuittiert.h"

void FehlerQuittiert::handlePulse(int code, int value){

	switch(code){

	case CODE_FBM_1: //pulse von FBM1
		pulseFBM1(value);
		break;

	case CODE_FBM_2: //Pulse von GPIO_2
		pulseFBM2(value);
		break;

	case CODE_ZEIT_1:
		pulseZeit1(value);
		break;

	case CODE_ZEIT_2:
		pulseZeit2(value);
		break;
	}

}


/**
 *
 * PULSE VON FBM1
 *
 */
void FehlerQuittiert::pulseFBM1(int value){
	switch(value){

	case E_STOP_AN:
		eStop(1);
		break;

	case FEHLER_HOCH:
		fehlerCount++;
		MsgSendPulse(kommID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, FEHLER_AN);
		MsgSendPulse(inputID, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, FEHLER_AN);
		new (this) Fehlerzustand;
		MsgSendPulse(inputID, SIGEV_PULSE_PRIO_INHERIT,_PULSE_CODE_MINAVAIL,LED_RESET_AN );
		MsgSendPulse(kommID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, LED_RESET_AN);
		MsgSendPulse(inputID, SIGEV_PULSE_PRIO_INHERIT,_PULSE_CODE_MINAVAIL,LED_START_AUS );
		MsgSendPulse(kommID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, LED_START_AUS);
		break;

	case FEHLER_RUNTER:
		cout << "Von " << fehlerCount << "Fehler wird einer entfernt" << endl;
		fehlerCount--;
		// TODO Implementierung wieso hier Fehler Runter?
		MsgSendPulse(fsmHSbisSep1_ID, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, FEHLER_RUNTER);
		MsgSendPulse(fsmHSbisSep2_ID, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, FEHLER_RUNTER);
		break;

	case T_START_AUS:
		keinFehler();
		break;

	case LS_RUTSCHE_AUS:	//active low+
		MsgSendPulse(rutschenID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_1,LS_RUTSCHE_AUS);
		MsgSendPulse(fsmWsNichtAussortierbar_ID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1,LS_RUTSCHE_AUS);
		break;

	case LS_RUTSCHE_AN: //active low+
		MsgSendPulse(rutschenID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_1,LS_RUTSCHE_AN);
		if (MsgSendPulse(fsmSepBisRut1_ID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, LS_RUTSCHE_AN) == -1) {
			perror("[LOGIK_Betriebszustand] MsgSendPulse failed");
			exit(EXIT_FAILURE);
		}
		break;

	case SCHNELL_HOCH_1:
		MsgSendPulse(motorID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_1,SCHNELL_HOCH_1);
		break;

	case SCHNELL_RUNTER_1:
		MsgSendPulse(motorID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_1,SCHNELL_RUNTER_1);
		break;

	case LANGSAM_HOCH_1:
		MsgSendPulse(motorID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_1,LANGSAM_HOCH_1);
		break;

	case LANGSAM_RUNTER_1:
		MsgSendPulse(motorID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_1,LANGSAM_RUNTER_1);
		break;

	case STOP_HOCH_1:
		MsgSendPulse(motorID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_1,STOP_HOCH_1);
		MsgSendPulse(auswertungID1,SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, MOTOR_STOP_AN);
		break;

	case STOP_RUNTER_1:
		MsgSendPulse(motorID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_1,STOP_RUNTER_1);
		MsgSendPulse(auswertungID1,SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, MOTOR_STOP_AUS);
		break;

	case MOT_R_AN_1:
		MsgSendPulse(inputID, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, MOTOR_AN);
		break;

	case MOT_R_AUS_1:
		MsgSendPulse(inputID, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, MOTOR_AUS);
		break;

	case MOT_LANGSAM_AN_1:
		MsgSendPulse(inputID, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, MOTOR_LANGSAM_AN);
		break;

	case MOT_LANGSAM_AUS_1:
		MsgSendPulse(inputID, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, MOTOR_LANGSAM_AUS);
		break;

	case MOT_STOP_AN_1:
		MsgSendPulse(inputID, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, MOTOR_STOP_AN);
		break;

	case MOT_STOP_AUS_1:
		MsgSendPulse(inputID, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, MOTOR_STOP_AUS);
		break;

	case WARNUNG_AUS:
		MsgSendPulse(inputID, SIGEV_PULSE_PRIO_INHERIT,_PULSE_CODE_MINAVAIL,RUTSCHE_FREI);
		warnungsCount--;
		break;

	case WARNUNG_AN:
		MsgSendPulse(inputID, SIGEV_PULSE_PRIO_INHERIT,_PULSE_CODE_MINAVAIL,RUTSCHE_VOLL);
		warnungsCount++;
		break;

		/*
		 * AKTORIK FBM1
		 */
	case SEP_AN:
		if (MsgSendPulse(inputID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, SEP_AN)== -1) {
			perror("[LOGIK_Betriebszustand] MsgSendPulse failed");
			exit(EXIT_FAILURE);
		}
		break;
	case SEP_AUS:
		if (MsgSendPulse(inputID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, SEP_AUS)== -1) {
			perror("[LOGIK_Betriebszustand] MsgSendPulse failed");
			exit(EXIT_FAILURE);
		}
		break;


		/*
		 * TIMER FBM1
		 */
	case TIMER_RUTSCHE:
		MsgSendPulse(rutschenID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, TIMER_RUTSCHE);
		break;

	case TIMER_START_AUSWERFER:
		zeitFBM1->startMessung(50 + zeitFBM1->getTime(), ZEIT_AUSWERFER, 0);//0, da Timer keinem WS zugeordnet werden muss (muss nicht zerstoert werden)
		break;

	case TIMER_START_WEICHE:
		zeitFBM1->startMessung(1000 + zeitFBM1->getTime(), ZEIT_WEICHE, 0);	//0, da Timer keinem WS zugeordnet werden muss (muss nicht zerstoert werden)
		break;

	case HS_LEEREN:
		MsgSendPulse(auswertungID1, SIGEV_PULSE_PRIO_INHERIT,_PULSE_CODE_MINAVAIL, HS_LEEREN);
		break;


		/*
		 * SIGNALE SUBSTATES FBM1
		 */

	case WS_ERSTELLT:
		zeitFBM1->startMessung(2000 + zeitFBM1->getTime(), FEHLER_WS_STECKT_FEST_LSA, wsListen->ws_LSAnfang->getiD());
		break;

	case WS_IN_LS_A_BIS_HS:
		if (MsgSendPulse(fsmLSAbisHS1_ID, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, WS_IN_LS_A_BIS_HS)
				== -1) {
			perror("[LOGIK_Betriebszustand] MsgSendPulse failed");
			exit(EXIT_FAILURE);
		}
		// TODO Zeit geändert für die SIM vorher war da 3000
		zeitFBM1->startMessung(3500 + zeitFBM1->getTime(), FEHLER_WS_VERSCHWUNDEN, wsListen->ws_list_LSAnfang_bis_HS.back().getiD());
		if(dateiManager->get_value_of(Konfi_Codes::FBM1_AUSWERFER_TRUE)==1){
			zeitFBM1->startMessung(500 + zeitFBM1->getTime(), ZEIT_WS_ABSTAND, 0);	//0, da keine ws ID zugehoerig
		}
		else{
			zeitFBM1->startMessung(1550 + zeitFBM1->getTime(), ZEIT_WS_ABSTAND, 0);	//0, da keine ws ID zugehoerig
		}
		break;

	case HS_AKTIV:
		// cout << "Zeit HS_AKTIV im Betriebszustand " << zeitFBM1->getTime() << endl;
		if (MsgSendPulse(fsmLSAbisHS1_ID, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, HS_AKTIV)
				== -1) {
			perror("[LOGIK_Betriebszustand] MsgSendPulse failed");
			exit(EXIT_FAILURE);
		}
		break;

	case WS_IN_HS:
		//		cout << "WS_IN_HS im Betriebzustand: " << wsListen->ws_Hoehensensor_1->getTimestamp() << endl;
		if (MsgSendPulse(fsmWsErkennung1_ID, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, WS_IN_HS)
				== -1) {
			perror("[LOGIK_Betriebszustand] MsgSendPulse failed");
			exit(EXIT_FAILURE);
		}
		zeitFBM1->startMessung(1500 + zeitFBM1->getTime(), FEHLER_HOEHENMESSUNG, wsListen->ws_Hoehensensor_1->getiD());
		break;

	case WS_TYP:
		//cout << "Zeit WS_TYP im Betriebzustand " << wsListen->ws_Hoehensensor_1->getTimestamp() << endl;
		//cout << "Zeit WS_TYP im Betriebzustand " << wsListen->ws_list_LSAnfang_bis_HS.front().getTimestamp() << endl;
		if (MsgSendPulse(fsmWsErkennung1_ID, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, WS_TYP)
				== -1) {
			perror("[LOGIK_Betriebszustand] MsgSendPulse failed");
			exit(EXIT_FAILURE);
		}
		break;

	case WS_IN_HS_BIS_SEPERATOR:
		if (MsgSendPulse(fsmHSbisSep1_ID, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, WS_IN_HS_BIS_SEPERATOR)
				== -1) {
			perror("[LOGIK_Betriebszustand] MsgSendPulse failed");
			exit(EXIT_FAILURE);
		}
		// TODO Hier Timer geändert vorher 1300 jetzt 1500
		zeitFBM1->startMessung(1500 + zeitFBM1->getTime(), FEHLER_WS_VERSCHWUNDEN_HS_BIS_SEP, wsListen->ws_list_HS_bis_Seperator.back().getiD());
		break;

	case WS_PASSIEREN:
//		cout << "[Betriebszustand] WS soll passieren" << endl;
		if (MsgSendPulse(fsmPassieren_ID, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, WS_PASSIEREN)
				== -1) {
			perror("[LOGIK_Betriebszustand] MsgSendPulse failed");
			exit(EXIT_FAILURE);
		}
		break;

	case WS_AUF_WEG_ZU_LSE:
		if (MsgSendPulse(fsmSepBisLSEnde1_ID, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, WS_AUF_WEG_ZU_LSE)
				== -1) {
			perror("[LOGIK_Betriebszustand] MsgSendPulse failed");
			exit(EXIT_FAILURE);
		}
		zeitFBM1->startMessung(4000 + zeitFBM1->getTime(), FEHLER_WS_VERSCHWUNDEN_SEP_BIS_LSE, wsListen->ws_list_sep_bis_lsende.back().getiD());
		break;

	case WS_AUSSORTIEREN:
//		cout << "[F] WS soll aussortiert werden" << endl;
		if (MsgSendPulse(fsmSepBisRut1_ID, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, WS_AUSSORTIEREN)
				== -1) {
			perror("[LOGIK_Betriebszustand] MsgSendPulse failed");
			exit(EXIT_FAILURE);
		}
		zeitFBM1->startMessung(3000 + zeitFBM1->getTime(), FEHLER_WS_VERSCHWUNDEN_SEP_BIS_RUT, wsListen->ws_list_aussortieren.back().getiD());
		break;

	case UNQUITTIERT_ABGELAUFEN:
		MsgSendPulse(inputID, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, FEHLER_AUS);
		MsgSendPulse(kommID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, FEHLER_AUS);
		break;

	case WS_NICHT_AUSSORTIERBAR:
		//		cout << "WS_NICHT_AUSSORTIERBAR Betriebszustand"<<endl;
		MsgSendPulse(fsmWsNichtAussortierbar_ID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, WS_NICHT_AUSSORTIERBAR);
		break;
	case QUITTIERT:
		MsgSendPulse(inputID, SIGEV_PULSE_PRIO_INHERIT,_PULSE_CODE_MINAVAIL,FEHLER_QUITTIERT);
		MsgSendPulse(kommID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_1,FEHLER_QUITTIERT);
		break;


		/*
		 * FÜR KOMMUNIKATION FBM1 - FBM2
		 */
	case FBM1_BEREIT:
		if (MsgSendPulse(fsmLSA2_ID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, FBM1_BEREIT)
				== -1) {
			perror("[LOGIK_Betriebszustand] MsgSendPulse failed");
			exit(EXIT_FAILURE);
		}
		break;

	case FBM1_WS_LOSGESCHICKT:
		if (MsgSendPulse(fsmLSA2_ID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, FBM1_WS_LOSGESCHICKT)
				== -1) {
			perror("[LOGIK_Betriebszustand] MsgSendPulse failed");
			exit(EXIT_FAILURE);
		}
		//EXAKTE Zeit, nach der das Werkstueck auf FBM2 ankommt:
		//wenn Wert zu klein, koennte das WS FBM2 nicht erreichen (wegen SCHNELL_RUNTER_1 Signal)
		//wenn Wert zu gross, wird die LSA auf FBM2 durchbrochen, bevor wir in der FSM LSA2 im richtigen State sind
		//(dieser wird erst nach Ablauf dieses Timers und anschliessendes Senden des Signals erreicht)
		//idealerweise erreicht das WS die LSA auf FBM2 sehr kurz nach Ablauf dieses Timers -> Testen!
		//TODO Wert nicht getestet
		zeitFBM1->startMessung(500 + zeitFBM1->getTime(), ZEIT_UEBERGABE_AN_FBM2, 0);//0, da Timer keinem WS zugeordnet werden muss (muss nicht zerstoert werden)
		//Zeit, nach der der Fehler WS verschwunden in LSA2 ausgeloest wird
		//TODO Zeit extra hoch fuer Simulation
		zeitFBM2->startMessung(2000 + zeitFBM2->getTime(), FEHLER_WS_VERSCHWUNDEN_LSA2, wsListen->ws_list_passieren.front().getiD());
		break;

	case FBM1_WS_UEBERGEBEN:
		if (MsgSendPulse(fsmLSA2_ID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, FBM1_WS_UEBERGEBEN)
				== -1) {
			perror("[LOGIK_Betriebszustand] MsgSendPulse failed");
			exit(EXIT_FAILURE);
		}
		break;
	}
}

/**
 *
 * PULSE VON FBM2
 *
 */
void FehlerQuittiert::pulseFBM2(int value){
	switch(value){

	case E_STOP_AN:
		eStop(2);
		break;

	case LS_RUTSCHE_AUS:	//active low+
		MsgSendPulse(rutschenID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_2,LS_RUTSCHE_AUS);
		MsgSendPulse(fsmWsNichtAussortierbar_ID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_2,LS_RUTSCHE_AUS);
		break;
	case LS_RUTSCHE_AN: //active low+
		MsgSendPulse(rutschenID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_2,LS_RUTSCHE_AN);
		if (MsgSendPulse(fsmSepBisRut2_ID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_2, LS_RUTSCHE_AN) == -1) {
			perror("[LOGIK_Betriebszustand] MsgSendPulse failed");
			exit(EXIT_FAILURE);
		}
		break;

	case FEHLER_HOCH:
		fehlerCount++;
		MsgSendPulse(kommID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, FEHLER_AN);
		MsgSendPulse(inputID, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, FEHLER_AN);
		new (this) Fehlerzustand;
		break;

	case FEHLER_RUNTER:
		fehlerCount--;
		break;

	case T_START_AUS:
		keinFehler();
		break;

	case SCHNELL_HOCH_2:
		MsgSendPulse(motorID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_2,SCHNELL_HOCH_2);
		break;

	case SCHNELL_RUNTER_2:
		MsgSendPulse(motorID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_2,SCHNELL_RUNTER_2);
		break;

	case LANGSAM_HOCH_2:
		MsgSendPulse(motorID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_2,LANGSAM_HOCH_2);
		break;

	case LANGSAM_RUNTER_2:
		MsgSendPulse(motorID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_2,LANGSAM_RUNTER_2);
		break;

	case STOP_HOCH_2:
		MsgSendPulse(motorID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_2,STOP_HOCH_2);
		break;

	case STOP_RUNTER_2:
		MsgSendPulse(motorID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_2,STOP_RUNTER_2);
		break;

	case MOT_LANGSAM_AN_2:
		MsgSendPulse(kommID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_1,MOTOR_LANGSAM_AN);
		break;

	case MOT_LANGSAM_AUS_2:
		MsgSendPulse(kommID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_1,MOTOR_LANGSAM_AUS);
		break;

	case MOT_R_AN_2:
		MsgSendPulse(kommID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_1,MOTOR_AN);
		break;

	case MOT_R_AUS_2:
		MsgSendPulse(kommID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_1,MOTOR_AUS);
		break;

	case MOT_STOP_AN_2:
		MsgSendPulse(kommID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_1,MOTOR_STOP_AN);
		MsgSendPulse(auswertungID2,SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, MOTOR_STOP_AN);
		break;

	case MOT_STOP_AUS_2:
		MsgSendPulse(kommID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_1,MOTOR_STOP_AUS);
		MsgSendPulse(auswertungID2,SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, MOTOR_STOP_AUS);
		break;

	case WARNUNG_AUS:
		MsgSendPulse(kommID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, RUTSCHE_FREI);
		warnungsCount--;
		break;

	case WARNUNG_AN:
		MsgSendPulse(kommID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, RUTSCHE_VOLL);
		warnungsCount++;
		break;

		/*
		 * AKTORIK
		 */
	case SEP_AN:
		if (MsgSendPulse(kommID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, SEP_AN)== -1) {
			perror("[LOGIK_Betriebszustand] MsgSendPulse failed");
			exit(EXIT_FAILURE);
		}
		break;
	case SEP_AUS:
		if (MsgSendPulse(kommID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, SEP_AUS)== -1) {
			perror("[LOGIK_Betriebszustand] MsgSendPulse failed");
			exit(EXIT_FAILURE);
		}
		break;
		/*
		 * SIGNALE SUBSTATES FBM2
		 */
	case FBM2_BEREIT:
		MsgSendPulse(fsmLSA2_ID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_2, FBM2_BEREIT);
		MsgSendPulse(fsmSepBisLSEnde1_ID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_2, FBM2_BEREIT);
		break;

	case WS_IN_LS_A_BIS_HS:
		if (MsgSendPulse(fsmLSAbisHS2_ID, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, WS_IN_LS_A_BIS_HS)
				== -1) {
			perror("[LOGIK_Betriebszustand] MsgSendPulse failed");
			exit(EXIT_FAILURE);
		}
		zeitFBM2->startMessung(3500 + zeitFBM2->getTime(), FEHLER_WS_VERSCHWUNDEN, wsListen->ws_ls_anfang_bis_hs_2->getiD());
		break;

	case HS_AKTIV:
//		cout << "Betriebszustand recv: HS_AKTIV" << endl;
		if (MsgSendPulse(fsmLSAbisHS2_ID, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, HS_AKTIV)
				== -1) {
			perror("[LOGIK_Betriebszustand] MsgSendPulse failed");
			exit(EXIT_FAILURE);
		}
		break;

	case WS_IN_HS:
		if (MsgSendPulse(fsmWsErkennung2_ID, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, WS_IN_HS)
				== -1) {
			perror("[LOGIK_Betriebszustand] MsgSendPulse failed");
			exit(EXIT_FAILURE);
		}
		zeitFBM2->startMessung(1500 + zeitFBM2->getTime(), FEHLER_HOEHENMESSUNG, wsListen->ws_Hoehensensor_2->getiD());
		break;

	case WS_TYP:
		if (MsgSendPulse(fsmWsErkennung2_ID, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, WS_TYP)
				== -1) {
			perror("[LOGIK_Betriebszustand] MsgSendPulse failed");
			exit(EXIT_FAILURE);
		}
		break;

	case WS_IN_HS_BIS_SEPERATOR:
//		cout << "WS_IN_HS_BIS_SEPERATOR Betriebzustand" << endl;
		if (MsgSendPulse(fsmHSbisSep2_ID, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, WS_IN_HS_BIS_SEPERATOR)
				== -1) {
			perror("[LOGIK_Betriebszustand] MsgSendPulse failed");
			exit(EXIT_FAILURE);
		}
		// TODO Timer anpassen ggf.
		zeitFBM2->startMessung(1500 + zeitFBM2->getTime(), FEHLER_WS_VERSCHWUNDEN_HS_BIS_SEP, wsListen->ws_hs_bis_seperator_2->getiD());
		break;

	case WS_NICHT_AUSSORTIERBAR:
		//		cout << "WS_NICHT_AUSSORTIERBAR Betriebszustand"<<endl;
		MsgSendPulse(fsmWsNichtAussortierbar_ID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_2, WS_NICHT_AUSSORTIERBAR);
		break;

	case WS_PASSIEREN:
		if (MsgSendPulse(fsmSepBisLSEnde2_ID, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, WS_PASSIEREN)
				== -1) {
			perror("[LOGIK_Betriebszustand] MsgSendPulse failed");
			exit(EXIT_FAILURE);
		}
		// TODO Timer anpassen ggf.
		zeitFBM2->startMessung(4000 + zeitFBM2->getTime(), FEHLER_WS_VERSCHWUNDEN_SEP_BIS_LSE, wsListen->ws_passieren_2->getiD());
		break;

	case WS_AUSSORTIEREN:
		if (MsgSendPulse(fsmSepBisRut2_ID, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, WS_AUSSORTIEREN)
				== -1) {
			perror("[LOGIK_Betriebszustand] MsgSendPulse failed");
			exit(EXIT_FAILURE);
		}
		// TODO Timer anpassen ggf.
		zeitFBM2->startMessung(3000 + zeitFBM2->getTime(), FEHLER_WS_VERSCHWUNDEN_SEP_BIS_RUT, wsListen->ws_aussortieren_2->getiD());
		break;

		/*
		 * TIMER FBM2
		 */
	case TIMER_RUTSCHE:
		MsgSendPulse(rutschenID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_2, TIMER_RUTSCHE);
		break;

	case TIMER_START_AUSWERFER:
		zeitFBM2->startMessung(50 + zeitFBM2->getTime(), ZEIT_AUSWERFER, 0); //0, da Timer keinem WS zugeordnet werden muss (muss nicht zerstoert werden)
		break;

	case TIMER_START_WEICHE:
		zeitFBM2->startMessung(1000 + zeitFBM2->getTime(), ZEIT_WEICHE, 0);	//0, da Timer keinem WS zugeordnet werden muss (muss nicht zerstoert werden)
		break;

	case HS_LEEREN:
		MsgSendPulse(auswertungID2, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, HS_LEEREN);
		break;
	}
}

/**
 *
 * PULSE VON zeitFBM2
 *
 */
void FehlerQuittiert::pulseZeit1(int value){
	switch (value) {
	case FEHLER_WS_STECKT_FEST_LSA:
		if (MsgSendPulse(fsmLSA1_ID, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, FEHLER_WS_STECKT_FEST_LSA) == -1) {
			perror("[LOGIK_Betriebszustand] MsgSendPulse failed");
			exit(EXIT_FAILURE);
		}
		break;

	case FEHLER_WS_VERSCHWUNDEN:
		if (MsgSendPulse(fsmLSAbisHS1_ID, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, FEHLER_WS_VERSCHWUNDEN) == -1) {
			perror("[LOGIK_Betriebszustand] MsgSendPulse failed");
			exit(EXIT_FAILURE);
		}
		break;

	case FEHLER_HOEHENMESSUNG:
		if (MsgSendPulse(fsmWsErkennung1_ID, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, FEHLER_HOEHENMESSUNG) == -1) {
			perror("[LOGIK_Betriebszustand] MsgSendPulse failed");
			exit(EXIT_FAILURE);
		}
		break;

	case FEHLER_WS_VERSCHWUNDEN_HS_BIS_SEP:
		if (MsgSendPulse(fsmHSbisSep1_ID, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, FEHLER_WS_VERSCHWUNDEN_HS_BIS_SEP)
				== -1) {
			perror("[LOGIK_Betriebszustand] MsgSendPulse failed");
			exit(EXIT_FAILURE);
		}
		break;

	case ZEIT_WS_ABSTAND:
		if (MsgSendPulse(fsmLSA1_ID, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, ZEIT_WS_ABSTAND) == -1) {
			perror("[LOGIK_Betriebszustand] MsgSendPulse failed");
			exit(EXIT_FAILURE);
		}
		break;

	case FEHLER_WS_VERSCHWUNDEN_SEP_BIS_RUT:
		if (MsgSendPulse(fsmSepBisRut1_ID, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, FEHLER_WS_VERSCHWUNDEN_SEP_BIS_RUT)
				== -1) {
			perror("[LOGIK_Betriebszustand] MsgSendPulse failed");
			exit(EXIT_FAILURE);
		}
		break;

	case ZEIT_AUSWERFER:
		if (MsgSendPulse(fsmSepBisRut1_ID, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, ZEIT_AUSWERFER) == -1) {
			perror("[LOGIK_Betriebszustand] MsgSendPulse failed");
			exit(EXIT_FAILURE);
		}
		break;

	case FEHLER_WS_VERSCHWUNDEN_SEP_BIS_LSE:
		if (MsgSendPulse(fsmSepBisLSEnde1_ID, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, FEHLER_WS_VERSCHWUNDEN_SEP_BIS_LSE)
				== -1) {
			perror("[LOGIK_Betriebszustand] MsgSendPulse failed");
			exit(EXIT_FAILURE);
		}
		break;

	case ZEIT_WEICHE:
		if (MsgSendPulse(fsmPassieren_ID, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, ZEIT_WEICHE) == -1) {
			perror("[LOGIK_Betriebszustand] MsgSendPulse failed");
			exit(EXIT_FAILURE);
		}
		break;

	case ZEIT_UEBERGABE_AN_FBM2:
		if (MsgSendPulse(fsmSepBisLSEnde1_ID, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, ZEIT_UEBERGABE_AN_FBM2) == -1) {
			perror("[LOGIK_Betriebszustand] MsgSendPulse failed");
			exit(EXIT_FAILURE);
		}
		break;

	}
}

/**
 *
 * PULSE VON zeitFBM2
 *
 */
void FehlerQuittiert::pulseZeit2(int value){
	switch(value){
	case FEHLER_WS_VERSCHWUNDEN_LSA2:
		if (MsgSendPulse(fsmLSA2_ID, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, FEHLER_WS_VERSCHWUNDEN_LSA2) == -1) {
			perror("[LOGIK_Betriebszustand] MsgSendPulse failed");
			exit(EXIT_FAILURE);
		}
		break;

	case FEHLER_WS_VERSCHWUNDEN:
		if (MsgSendPulse(fsmLSAbisHS2_ID, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, FEHLER_WS_VERSCHWUNDEN) == -1) {
			perror("[LOGIK_Betriebszustand] MsgSendPulse failed");
			exit(EXIT_FAILURE);
		}
		break;

	case FEHLER_HOEHENMESSUNG:
		if (MsgSendPulse(fsmWsErkennung2_ID, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, FEHLER_HOEHENMESSUNG) == -1) {
			perror("[LOGIK_Betriebszustand] MsgSendPulse failed");
			exit(EXIT_FAILURE);
		}
		break;

	case FEHLER_WS_VERSCHWUNDEN_HS_BIS_SEP:
		if (MsgSendPulse(fsmHSbisSep2_ID, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, FEHLER_WS_VERSCHWUNDEN_HS_BIS_SEP) == -1) {
			perror("[LOGIK_Betriebszustand] MsgSendPulse failed");
			exit(EXIT_FAILURE);
		}
		break;

	case FEHLER_WS_VERSCHWUNDEN_SEP_BIS_LSE:
		if (MsgSendPulse(fsmSepBisLSEnde2_ID, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, FEHLER_WS_VERSCHWUNDEN_SEP_BIS_LSE) == -1) {
			perror("[LOGIK_Betriebszustand] MsgSendPulse failed");
			exit(EXIT_FAILURE);
		}
		break;

	case FEHLER_WS_VERSCHWUNDEN_SEP_BIS_RUT:
		if (MsgSendPulse(fsmSepBisRut2_ID, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, FEHLER_WS_VERSCHWUNDEN_SEP_BIS_RUT) == -1) {
			perror("[LOGIK_Betriebszustand] MsgSendPulse failed");
			exit(EXIT_FAILURE);
		}
		break;

	case ZEIT_WEICHE:
		if (MsgSendPulse(fsmSepBisLSEnde2_ID, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, ZEIT_WEICHE) == -1) {
			perror("[LOGIK_Betriebszustand] MsgSendPulse failed");
			exit(EXIT_FAILURE);
		}
		break;

	case ZEIT_AUSWERFER:
		if (MsgSendPulse(fsmSepBisRut2_ID, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, ZEIT_AUSWERFER) == -1) {
			perror("[LOGIK_Betriebszustand] MsgSendPulse failed");
			exit(EXIT_FAILURE);
		}
		break;
	}
}

void FehlerQuittiert::updateAuswertung(){

}

void FehlerQuittiert::eStop(int estop){
	MsgSendPulse(inputID, sched_get_priority_max(SCHED_FIFO),_PULSE_CODE_MINAVAIL,BETRIEBSMODUS_AUS );
	MsgSendPulse(motorID, sched_get_priority_max(SCHED_FIFO),CODE_FBM_1,E_STOP_AN );
	MsgSendPulse(motorID, sched_get_priority_max(SCHED_FIFO),CODE_FBM_2,E_STOP_AN);
	MsgSendPulse(fsmLSA1_ID, sched_get_priority_max(SCHED_FIFO),_PULSE_CODE_MINAVAIL, E_STOP_AN);
	MsgSendPulse(fsmLSA2_ID, sched_get_priority_max(SCHED_FIFO),_PULSE_CODE_MINAVAIL, E_STOP_AN);
	MsgSendPulse(auswertungID1, sched_get_priority_max(SCHED_FIFO),_PULSE_CODE_MINAVAIL, HS_LEEREN);
	MsgSendPulse(auswertungID2, sched_get_priority_max(SCHED_FIFO),_PULSE_CODE_MINAVAIL, HS_LEEREN);
	MsgSendPulse(auswertungID1, sched_get_priority_max(SCHED_FIFO),_PULSE_CODE_MINAVAIL, MOTOR_STOP_AN);
	MsgSendPulse(auswertungID2, sched_get_priority_max(SCHED_FIFO),_PULSE_CODE_MINAVAIL, MOTOR_STOP_AN);
	MsgSendPulse(fsmLSAbisHS1_ID, sched_get_priority_max(SCHED_FIFO),_PULSE_CODE_MINAVAIL, E_STOP_AN);
	MsgSendPulse(fsmLSAbisHS2_ID, sched_get_priority_max(SCHED_FIFO),_PULSE_CODE_MINAVAIL, E_STOP_AN);
	MsgSendPulse(fsmWsErkennung1_ID, sched_get_priority_max(SCHED_FIFO),_PULSE_CODE_MINAVAIL, E_STOP_AN);
	MsgSendPulse(fsmWsErkennung2_ID, sched_get_priority_max(SCHED_FIFO),_PULSE_CODE_MINAVAIL, E_STOP_AN);
	MsgSendPulse(fsmWsNichtAussortierbar_ID, sched_get_priority_max(SCHED_FIFO),_PULSE_CODE_MINAVAIL, E_STOP_AN);
	MsgSendPulse(rutschenID, sched_get_priority_max(SCHED_FIFO),_PULSE_CODE_MINAVAIL, E_STOP_AN);
	MsgSendPulse(fsmHSbisSep1_ID, sched_get_priority_max(SCHED_FIFO),_PULSE_CODE_MINAVAIL, E_STOP_AN);
	MsgSendPulse(fsmHSbisSep2_ID, sched_get_priority_max(SCHED_FIFO),_PULSE_CODE_MINAVAIL, E_STOP_AN);
	MsgSendPulse(fsmSepBisRut1_ID, sched_get_priority_max(SCHED_FIFO),_PULSE_CODE_MINAVAIL, E_STOP_AN);
	MsgSendPulse(fsmSepBisRut2_ID, sched_get_priority_max(SCHED_FIFO),_PULSE_CODE_MINAVAIL, E_STOP_AN);
	MsgSendPulse(fsmPassieren_ID, sched_get_priority_max(SCHED_FIFO),_PULSE_CODE_MINAVAIL, E_STOP_AN);
	MsgSendPulse(fsmSepBisLSEnde1_ID, sched_get_priority_max(SCHED_FIFO),_PULSE_CODE_MINAVAIL, E_STOP_AN);
	MsgSendPulse(fsmSepBisLSEnde2_ID, sched_get_priority_max(SCHED_FIFO),_PULSE_CODE_MINAVAIL, E_STOP_AN);

	zeitFBM1->clearLists();
	zeitFBM2->clearLists();

	fehlerCount=0;
	warnungsCount=0;

	wsListen->sortierReihenfolge.clear();
	wsListen->sortierReihenfolge2.clear();

	if(estop==1){
		MsgSendPulse(kommID, sched_get_priority_max(SCHED_FIFO), CODE_FBM_1, ESTOP_AN);
		eStop1=true;
	} else{
		eStop2=true;
	}

	new (this) EStop;
	cout << "switched to EStop " << estop << endl;
}
void FehlerQuittiert::keinFehler(){
	if(fehlerCount==0){
		//TODO Quittiert an alle FSMs schicken
		MsgSendPulse(kommID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, FEHLER_AUS);
		MsgSendPulse(inputID, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, FEHLER_AUS);
		MsgSendPulse(kommID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, BETRIEBSMODUS_AN);
		MsgSendPulse(inputID, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, BETRIEBSMODUS_AN);
		MsgSendPulse(motorID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, STOP_RUNTER_1);
		MsgSendPulse(motorID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_2, STOP_RUNTER_2);
		MsgSendPulse(fsmLSA1_ID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, KEIN_FEHLER);
		MsgSendPulse(fsmLSA2_ID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, KEIN_FEHLER);
		MsgSendPulse(fsmLSAbisHS1_ID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, KEIN_FEHLER);
		MsgSendPulse(fsmLSAbisHS2_ID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, KEIN_FEHLER);
		MsgSendPulse(fsmWsErkennung1_ID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, KEIN_FEHLER);
		MsgSendPulse(fsmWsErkennung2_ID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, KEIN_FEHLER);
		MsgSendPulse(fsmHSbisSep1_ID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, KEIN_FEHLER);
		MsgSendPulse(fsmHSbisSep2_ID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, KEIN_FEHLER);
		MsgSendPulse(fsmSepBisRut1_ID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, KEIN_FEHLER);
		MsgSendPulse(fsmSepBisRut2_ID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, KEIN_FEHLER);
		MsgSendPulse(fsmPassieren_ID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, KEIN_FEHLER);
		MsgSendPulse(fsmSepBisLSEnde1_ID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, KEIN_FEHLER);
		MsgSendPulse(fsmSepBisLSEnde2_ID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, KEIN_FEHLER);
		MsgSendPulse(inputID, SIGEV_PULSE_PRIO_INHERIT,_PULSE_CODE_MINAVAIL,LED_START_AUS );
		MsgSendPulse(kommID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, LED_START_AUS);
		new (this) Betriebszustand;
	} else{
		new (this) Fehlerzustand;
		MsgSendPulse(kommID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, FEHLER_AN);
		MsgSendPulse(inputID, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, FEHLER_AN);
		MsgSendPulse(inputID, SIGEV_PULSE_PRIO_INHERIT,_PULSE_CODE_MINAVAIL,LED_RESET_AN );
		MsgSendPulse(kommID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, LED_RESET_AN);
		MsgSendPulse(inputID, SIGEV_PULSE_PRIO_INHERIT,_PULSE_CODE_MINAVAIL,LED_START_AUS );
		MsgSendPulse(kommID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, LED_START_AUS);
		cout << fehlerCount<<"  UNBEHANDELTE FEHLER!" << endl;
	}
}
