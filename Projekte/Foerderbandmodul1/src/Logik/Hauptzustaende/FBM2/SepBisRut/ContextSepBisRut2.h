/*
 * ContextSepBisRut2.h
 *
 *  Created on: 11.12.2022
 *      Author: Daniel
 */

#ifndef LOGIK_HAUPTZUSTAENDE_FBM2_SEPBISRUT_CONTEXTSEPBISRUT2_H_
#define LOGIK_HAUPTZUSTAENDE_FBM2_SEPBISRUT_CONTEXTSEPBISRUT2_H_

#include "../../../../dispatcher/QnetHandler.h"
#include "../../../WsListen.h"
#include "../../../Zeit/Zeitmanager.h"
#include "../../../Defines.h"
#include "ActionsSepBisRut2.h"
#include "BaseStateSepBisRut2.h"
#include "WarteSepBisRut2.h"

class ContextSepBisRut2 {
private:
	BaseStateSepBisRut2 *state;
	ActionsSepBisRut2 *actions;
	WsListen *wsListen;
	QnetHandler *qnetHandler;
	name_attach_t *attach;
	Zeitmanager *zeitmanager;
	KonfigurationsdateiManager *konfig;
public:
	ContextSepBisRut2(ActionsSepBisRut2 *shared_action, WsListen *werkstueckListen, Zeitmanager *zeitmanager, KonfigurationsdateiManager *konfigManager);
	virtual ~ContextSepBisRut2();

	void receiveSignal();

	//normales Verhalten
	void LsRutAn();
	void WsAussortieren();
	void AuswerferEinfahren();

	//Fehlerverhalten
	void quittiert();
	void keinFehler();
	void Fverschwunden();

	//E-Stop
	void eStop();
};

#endif /* LOGIK_HAUPTZUSTAENDE_FBM2_SEPBISRUT_CONTEXTSEPBISRUT2_H_ */
