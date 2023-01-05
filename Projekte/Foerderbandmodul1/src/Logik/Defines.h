/*
 * Defines.h
 *
 *  Created on: Dec 11, 2022
 *      Author: bardi
 */

#ifndef LOGIK_DEFINES_H_
#define LOGIK_DEFINES_H_

//Pulse values der Interrupts, unterscheidung durch code
#define LS_ANFANG_AN 2		//active low+
#define HS_HOCH_OK_AUS 4	//active high+
#define LS_SEPERATOR_AN 5	//active low+
#define METALLSENSOR_AUS 7	//active high+
#define LS_ZUSTAND_SEPERATOR_AUS 14	//active high+
#define LS_RUTSCHE_AN 15	//active low+
#define LS_ENDE_AN 20		//active low+
#define T_START_AUS  22		//active high+
#define T_STOP_AN 23		//active low+
#define T_RESET_AUS 26		//active high+
#define E_STOP_AN 27		//active low+


#define LS_ANFANG_AUS 102		//active low+
#define HS_HOCH_OK_AN 104	//active high+
#define LS_SEPERATOR_AUS 105	//active low+
#define METALLSENSOR_AN 107	//active high+
#define LS_ZUSTAND_SEPERATOR_AN 114	//active high+
#define LS_RUTSCHE_AUS 115	//active low+
#define LS_ENDE_AUS 120		//active low+
#define T_START_AN  122		//active high+
#define T_STOP_AUS 123		//active low+
#define T_RESET_AN 126		//active high+
#define E_STOP_AUS 127		//active low+

#define FEHLER_HOCH 128
#define FEHLER_RUNTER 129
#define QUITTIERT 130
#define KEIN_FEHLER 131

//Signale fuer an die Motorsteuerung
#define SCHNELL_HOCH_1 200
#define SCHNELL_RUNTER_1 201
#define SCHNELL_HOCH_2 202
#define SCHNELL_RUNTER_2 203
#define LANGSAM_HOCH_1 204
#define LANGSAM_HOCH_2 205
#define LANGSAM_RUNTER_1 206
#define LANGSAM_RUNTER_2 207
#define STOP_HOCH_1 208
#define STOP_HOCH_2 209
#define STOP_RUNTER_1 210
#define STOP_RUNTER_2 211

//Signale aus der Motorsteuerung in die LogikMain
#define MOT_R_AN_1 212
#define MOT_R_AUS_1 213
#define MOT_LANGSAM_AN_1 214
#define MOT_LANGSAM_AUS_1 215
#define MOT_LANGSAM_AN_2 216
#define MOT_LANGSAM_AUS_2 217
#define MOT_R_AN_2 218
#define MOT_R_AUS_2 219
#define MOT_STOP_AN_1 220
#define MOT_STOP_AUS_1 221
#define MOT_STOP_AN_2 222
#define MOT_STOP_AUS_2 223




//pulse values von FSMs
#define WS_IN_LS_A_BIS_HS		250
#define WS_IN_HS				251
#define HS_AKTIV				252
#define WS_TYP					253
#define HS_LEEREN				254
#define WS_ERSTELLT				255
#define TIMER_RUTSCHE 			256
#define WS_IN_HS_BIS_SEPERATOR	257
#define WARNUNG_AN				258
#define WARNUNG_AUS				259
#define WS_PASSIEREN			260
#define WS_AUSSORTIEREN			261
#define WS_NICHT_AUSSORTIERBAR	262
#define TIMER_START_AUSWERFER	263
#define TIMER_START_WEICHE		264
#define FBM1_BEREIT				265
#define FBM1_WS_LOSGESCHICKT	266
#define FBM1_WS_UEBERGEBEN		267
#define FBM2_BEREIT				268


//zeit pulse values
#define FEHLER_WS_STECKT_FEST_LSA			300
#define FEHLER_WS_VERSCHWUNDEN				301
#define FEHLER_HOEHENMESSUNG				302
#define FEHLER_WS_VERSCHWUNDEN_HS_BIS_SEP	303
#define ZEIT_WS_ABSTAND						304
#define ZEIT_AUSWERFER						305
#define FEHLER_WS_VERSCHWUNDEN_SEP_BIS_RUT	306
#define ZEIT_WEICHE							307
#define ZEIT_UEBERGABE_AN_FBM2				308
#define FEHLER_WS_VERSCHWUNDEN_SEP_BIS_LSE	309
#define FEHLER_WS_VERSCHWUNDEN_LSA2			310

//Defines fuer den InputDispatcher
#define ESTOP_AUS	1
#define ESTOP_AN	0
#define FEHLER_AN	2
#define FEHLER_AUS	3
#define STOP_AN		4
#define STOP_AUS	5
#define MOTOR_AN	6
#define MOTOR_AUS	7
#define MOTOR_STOP_AN	8
#define MOTOR_STOP_AUS	9
#define MOTOR_LANGSAM_AN	10
#define MOTOR_LANGSAM_AUS	11
#define AUSSORTIEREN	12
#define DURCHLASSEN	13
#define RUTSCHE_VOLL 14
#define RUTSCHE_FREI 15
#define ESTOP_AN_2 100
#define ESTOP_AUS_2 101
#define BETRIEBSMODUS_AN 20
#define BETRIEBSMODUS_AUS 21
#define FEHLER_QUITTIERT 22
//23 bereits vergeben an T_STOP_AN Signal
#define SERVICE_MODE_AN 24
#define SERVICE_MODE_AUS 25
#define SL_Q1_AN 28
#define SL_Q1_AUS 29
#define SEP_AN 30
#define SEP_AUS 31
#define FEHLER_G_UNQUITTIERT 32

//Watchdog defines fuer die Kommunikation
#define WATCHDOG_NOTIF		50
#define WATCHDOG_ESTOP		51
#define WATCHDOG_INIT		52
#define INIT_NOTIF			55
#define WATCHDOG_SEND_NOTIF 666



//Code defines
#define CODE_FBM_1 		_PULSE_CODE_MINAVAIL+1
#define CODE_FBM_2 		_PULSE_CODE_MINAVAIL+2
#define CODE_ADC_1		_PULSE_CODE_MINAVAIL+3
#define CODE_ADC_2		_PULSE_CODE_MINAVAIL+4
#define CODE_ZEIT_1		_PULSE_CODE_MINAVAIL+5
#define CODE_ZEIT_2		_PULSE_CODE_MINAVAIL+6

//server names
#define LOGIK				"server_logik"
#define INPUTDISPATCHER		"server_inputdispatcher"
#define SERVER_KOM_MASTER	"KommunikationMaster"
#define SERVER_KOM_SLAVE	"KommunikationSlave"

//fsm server names
#define AUSWERTUNG_1				"server_auswertung_1"
#define AUSWERTUNG_2				"server_auswertung_2"
#define S_LSANFANG1					"server_lsanfang1"
#define S_LSANFANG2					"server_lsanfang2" // TODO das hier hinzugefügt
#define S_MOTORSTEUERUNG			"server_motorsteuerung"
#define S_LSA_BIS_HS1				"server_lsanfang_bis_hs1"
#define S_LSA_BIS_HS2				"server_lsanfang_bis_hs2"
#define S_RUTSCHE 					"server_rutsche"
#define S_WS_ERKENNUNG1				"server_ws_erkennung1"
#define S_WS_ERKENNUNG2				"server_ws_erkennung2"
#define S_HS_BIS_SEP1				"server_hs_bis_sep1"
#define S_HS_BIS_SEP2				"server_hs_bis_sep2"
#define S_F_WS_NICHT_AUSSORTIERBAR	"server_f_ws_nicht_aussortierbar"
#define S_SEP_BIS_RUT1				"server_sep_bis_rut1"
#define S_SEP_BIS_RUT2				"server_sep_bis_rut2"
#define S_SEP_BIS_LSENDE			"server_sep_bis_lsende"
#endif /* LOGIK_DEFINES_H_ */
