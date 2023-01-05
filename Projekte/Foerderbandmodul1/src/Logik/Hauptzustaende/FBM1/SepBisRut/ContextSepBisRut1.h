/*
 * ContextSepBisRut1.h
 *
 *  Created on: 11.12.2022
 *      Author: Daniel
 */

#ifndef LOGIK_HAUPTZUSTAENDE_FBM1_SEPBISRUT_CONTEXTSEPBISRUT1_H_
#define LOGIK_HAUPTZUSTAENDE_FBM1_SEPBISRUT_CONTEXTSEPBISRUT1_H_

#include "../../../../dispatcher/QnetHandler.h"
#include "../../../WsListen.h"
#include "../../../Zeit/Zeitmanager.h"
#include "../../../Defines.h"
#include "ActionsSepBisRut1.h"
#include "BaseStateSepBisRut1.h"
#include "WarteSepBisRut1.h"

class ContextSepBisRut1 {
private:
	BaseStateSepBisRut1 *state;
	ActionsSepBisRut1 *actions;
	WsListen *wsListen;
	QnetHandler *qnetHandler;
	name_attach_t *attach;
	Zeitmanager *zeitmanager;
	KonfigurationsdateiManager *konfig;
public:
	ContextSepBisRut1(ActionsSepBisRut1 *shared_action, WsListen *werkstueckListen, Zeitmanager *zeitmanager,
			KonfigurationsdateiManager *konfigManager);
	virtual ~ContextSepBisRut1();

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

#endif /* LOGIK_HAUPTZUSTAENDE_FBM1_SEPBISRUT_CONTEXTSEPBISRUT1H_ */
