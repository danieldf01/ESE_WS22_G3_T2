/*
 * LogikTest.h
 *
 *  Created on: 30.11.2022
 *      Author: acy003
 */

#ifndef LOGIK_LOGIKMAIN_H_
#define LOGIK_LOGIKMAIN_H_

#include "../dispatcher/QnetHandler.h"
#include <thread>
#include "Hauptzustaende/BaseState.h"
#include "Hauptzustaende/Ruhezustand.h"
#include "Hauptzustaende/Betriebszustand.h"
#include "Hauptzustaende/ServiceMode.h"
#include "Hauptzustaende/Fehlerzustand.h"
#include "Hauptzustaende/FehlerQuittiert.h"
#include "Hauptzustaende/EStop.h"
#include "Defines.h"
#include "Hauptzustaende/FehlerWsNichtAussortierbar/ActionsWsNichtAussortierbar.h"
#include "Hauptzustaende/FehlerWsNichtAussortierbar/ContextWsNichtAussortierbar.h"
#include "Hauptzustaende/FBM1/LSAnfang/ActionsLSA1.h"
#include "Hauptzustaende/FBM1/LSAnfang/ContextLSA1.h"
#include "Hauptzustaende/FBM1/LSAnfangBisHS/ActionsLSAbisHS1.h"
#include "Hauptzustaende/FBM1/LSAnfangBisHS/ContextLSAbisHS1.h"
#include "Hauptzustaende/FBM1/WsErkennung/ActionsWsErkennung1.h"
#include "Hauptzustaende/FBM1/WsErkennung/ContextWsErkennung1.h"
#include "Hauptzustaende/FBM1/HSBisSep/ActionsHSBisSep1.h"
#include "Hauptzustaende/FBM1/HSBisSep/ContextHSBisSep1.h"
#include "Hauptzustaende/FBM1/SepBisRut/ActionsSepBisRut1.h"
#include "Hauptzustaende/FBM1/SepBisRut/ContextSepBisRut1.h"
#include "Hauptzustaende/FBM1/Passieren/ActionsPassieren.h"
#include "Hauptzustaende/FBM1/Passieren/ContextPassieren.h"
#include "Hauptzustaende/FBM1/SepBisLSEnde/ActionsSepBisLSE1.h"
#include "Hauptzustaende/FBM1/SepBisLSEnde/ContextSepBisLSE1.h"
#include "WsListen.h"
#include "Hauptzustaende/Motorsteuerung/Motorsteuerung.h"
#include "Hauptzustaende/Rutsche/Rutsche.h"
#include "Zeit/Zeitmanager.h"

#include "Hauptzustaende/FBM2/LSAnfang/ActionsLSA2.h"
#include "Hauptzustaende/FBM2/LSAnfang/ContextLSA2.h"
#include "Hauptzustaende/FBM2/LSAnfangBisHS/ActionsLSAbisHS2.h"
#include "Hauptzustaende/FBM2/LSAnfangBisHS/ContextLSAbisHS2.h"
#include "Hauptzustaende/FBM2/WsErkennung/ActionsWsErkennung2.h"
#include "Hauptzustaende/FBM2/WsErkennung/ContextWsErkennung2.h"
#include "Hauptzustaende/FBM2/HSBisSep/ActionsHSBisSep2.h"
#include "Hauptzustaende/FBM2/HSBisSep/ContextHSBisSep2.h"
#include "Hauptzustaende/FBM2/SepBisRut/ActionsSepBisRut2.h"
#include "Hauptzustaende/FBM2/SepBisRut/ContextSepBisRut2.h"
#include "Hauptzustaende/FBM2/SepBisLSEnde/ActionsSepBisLSE2.h"
#include "Hauptzustaende/FBM2/SepBisLSEnde/ContextSepBisLSE2.h"

#define LOGIK "server_logik"
#define INPUTDISPATCHER "server_inputdispatcher"
#define SERVER_KOM_MASTER "KommunikationMaster"
#define AUSWERTUNG "server_auswertung"

class LogikMain{
private:

	QnetHandler *qnetHandler;
	name_attach_t *attach;
	BaseState *state = nullptr;
	WsListen *wsListen =nullptr;
	int inputID=0;

public:
	LogikMain();
	virtual ~LogikMain();
	void init();
	void receiveSignal();
	void startFSMs();
};

#endif /* LOGIK_LOGIKMAIN_H_ */
