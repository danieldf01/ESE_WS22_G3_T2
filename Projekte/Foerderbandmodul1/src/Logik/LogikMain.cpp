/*
 * LogikTest.cpp
 *
 *  Created on: 30.11.2022
 *      Author: acy003
 */

#include "LogikMain.h"

using namespace std;

LogikMain::LogikMain() {
	qnetHandler = new QnetHandler();
	wsListen = new WsListen();
	state = new Ruhezustand();
	state->dateiManager = new KonfigurationsdateiManager("/Team3_2_conf.txt"); //Starte KonfigurationsdateiManager
	state->wsListen = wsListen;
	state->fehlerCount=0;
	state->warnungsCount=0;
	attach = qnetHandler->openServer(LOGIK);

	state->hoehenauswertung1 = new VerarbeitungHoehenmessdaten(1,
			wsListen,
			state->dateiManager->get_value_of(Konfi_Codes::ADC_WS_HOCH_LEVEL_1),
			state->dateiManager->get_value_of(Konfi_Codes::ADC_BAND_LEVEL_1));

	state->hoehenauswertung2 = new VerarbeitungHoehenmessdaten(2,
			wsListen,
			state->dateiManager->get_value_of(Konfi_Codes::ADC_WS_HOCH_LEVEL_2),
			state->dateiManager->get_value_of(Konfi_Codes::ADC_BAND_LEVEL_2));
}

LogikMain::~LogikMain() {
	delete state;
}

void LogikMain::init(){
	inputID=qnetHandler->connectServer(INPUTDISPATCHER);
	state->inputID= inputID;
	state->kommID = qnetHandler->connectServer(SERVER_KOM_MASTER);

}

void LogikMain::receiveSignal(){

	state->updateAuswertung();												//Update die Werte fuer die Hoehenauswertung

	thread auswertung1(&VerarbeitungHoehenmessdaten::receivingADCValueFromHAL, ref(state->hoehenauswertung1)); //Hoehenauswertung1 thread
	thread auswertung2(&VerarbeitungHoehenmessdaten::receivingADCValueFromHAL, ref(state->hoehenauswertung2)); //Hoehenauswertung2 thread

	_pulse pulse;

	state->auswertungID1= qnetHandler->connectServer(AUSWERTUNG_1); //Verbindung an Hoehenauswertung1
	state->auswertungID2= qnetHandler->connectServer(AUSWERTUNG_2); //Verbindung an Hoehenauswertung2

	//Liste mit der Sortierreihenfolge
	wsListen->sortierReihenfolge.push_back(state->dateiManager->get_value_of(Konfi_Codes::WS_Reihung_Nr_1));
	wsListen->sortierReihenfolge.push_back(state->dateiManager->get_value_of(Konfi_Codes::WS_Reihung_Nr_2));
	wsListen->sortierReihenfolge.push_back(state->dateiManager->get_value_of(Konfi_Codes::WS_Reihung_Nr_3));

	state->zeitFBM1 = new Zeitmanager(10, 6, attach->chid, CODE_ZEIT_1); //Erstellen des Zeitmanagers fuer FBM1
	thread t_startZeit(&Zeitmanager::threadStartZeit, ref(state->zeitFBM1));

	state->zeitFBM2 = new Zeitmanager(10, 6, attach->chid, CODE_ZEIT_2); // Erstellen des Zeitmanagers fuer FBM2
	thread t_startZeit2(&Zeitmanager::threadStartZeit, ref(state->zeitFBM2));

	thread t_startFSMs(&LogikMain::startFSMs, this);

	while (1) {

		int rcvid = MsgReceive(attach->chid, &pulse, sizeof(_pulse), NULL);

		if (rcvid == -1) { // Error occurred
			perror("Server: MsgReceived failed");
		}
		if (rcvid == 0) { // Pulse was received
			state->handlePulse(pulse.code, pulse.value.sival_int);
		}
		// some sync msg was received
		if ((_IO_BASE <= pulse.type) && (pulse.type <= _IO_MAX)) {
			if (pulse.type == _IO_CONNECT) {
				cout << LOGIK << " received _IO_CONNECT via sync. message" << endl;
				MsgReply(rcvid, EOK, NULL, 0);
			}
		}
	}

	t_startFSMs.join();
	t_startZeit2.join();
	t_startZeit.join();
	auswertung2.join();
	auswertung1.join();

}

void LogikMain::startFSMs() {
	Rutsche *rutschenSteuerung = new Rutsche();
	thread t_rutsche(&Rutsche::receiveSignal, ref(rutschenSteuerung));
	t_rutsche.detach();
	state->rutschenID= qnetHandler->connectServer(S_RUTSCHE);

	Motorsteuerung *motorSteuerung = new Motorsteuerung(state->zeitFBM1, state->zeitFBM2); //Erstellen der Motorsteuerung
	thread t_motor(&Motorsteuerung::receiveSignal, ref(motorSteuerung));
	t_motor.detach();
	state->motorID= qnetHandler->connectServer(S_MOTORSTEUERUNG);

//	ContextWsNichtAussortierbar *contextWsNichtAussortierbar = new ContextWsNichtAussortierbar(new ActionsWsNichtAussortierbar, ref(rutschenSteuerung));
//	thread t_WsNichtAussortierbar(&ContextWsNichtAussortierbar::receiveSignal, ref(contextWsNichtAussortierbar));
//	t_WsNichtAussortierbar.detach();
//	state->fsmWsNichtAussortierbar_ID = qnetHandler->connectServer(S_F_WS_NICHT_AUSSORTIERBAR);

	ContextLSA1 *contextLSAnfang = new ContextLSA1(new ActionsLSA1, ref(wsListen), ref(state->zeitFBM1));
	thread t_LSA1(&ContextLSA1::receiveSignal, ref(contextLSAnfang));
	t_LSA1.detach();
	state->fsmLSA1_ID = qnetHandler->connectServer(S_LSANFANG1);

	ContextLSAbisHS1 *contextLSAnfangBisHS = new ContextLSAbisHS1(new ActionsLSAbisHS1, ref(wsListen), ref(state->zeitFBM1));
	thread t_LSAbisHS1(&ContextLSAbisHS1::receiveSignal, ref(contextLSAnfangBisHS));
	t_LSAbisHS1.detach();
	state->fsmLSAbisHS1_ID = qnetHandler->connectServer(S_LSA_BIS_HS1);

	ContextWsErkennung1 *contextWsErkennung = new ContextWsErkennung1(new ActionsWsErkennung1, ref(wsListen), ref(state->zeitFBM1));
	thread t_WsErkennung1(&ContextWsErkennung1::receiveSignal, ref(contextWsErkennung));
	t_WsErkennung1.detach();
	state->fsmWsErkennung1_ID = qnetHandler->connectServer(S_WS_ERKENNUNG1);

	ContextHSBisSep1 *contextHSbisSep = new ContextHSBisSep1(new ActionsHSBisSep1, ref(wsListen), ref(state->zeitFBM1), ref(rutschenSteuerung));
	thread t_HSbisSep1(&ContextHSBisSep1::receiveSignal, ref(contextHSbisSep));
	t_HSbisSep1.detach();
	state->fsmHSbisSep1_ID = qnetHandler->connectServer(S_HS_BIS_SEP1);

	ContextSepBisRut1 *contextSepBisRut1 = new ContextSepBisRut1(new ActionsSepBisRut1, ref(wsListen), ref(state->zeitFBM1), ref(state->dateiManager));
	thread t_SepBisRut1(&ContextSepBisRut1::receiveSignal, ref(contextSepBisRut1));
	t_SepBisRut1.detach();
	state->fsmSepBisRut1_ID = qnetHandler->connectServer(S_SEP_BIS_RUT1);

	ContextSepBisLSE1 *contextSepBisLSEnde = new ContextSepBisLSE1(new ActionsSepBisLSE1, ref(wsListen), ref(state->zeitFBM1), ref(state->dateiManager));
	thread t_SepBisLSEnde(&ContextSepBisLSE1::receiveSignal, ref(contextSepBisLSEnde));
	t_SepBisLSEnde.detach();
	state->fsmSepBisLSEnde_ID = qnetHandler->connectServer(S_SEP_BIS_LSENDE);


	// TODO NEED TO BE TESTED
	ContextLSA2 *contextLSAnfang2 = new ContextLSA2(new ActionsLSA2, ref(wsListen), ref(state->zeitFBM2));
	thread t_LSA2(&ContextLSA2::receiveSignal, ref(contextLSAnfang2));
	t_LSA2.detach();
	state->fsmLSA2_ID = qnetHandler->connectServer(S_LSANFANG2);
}
