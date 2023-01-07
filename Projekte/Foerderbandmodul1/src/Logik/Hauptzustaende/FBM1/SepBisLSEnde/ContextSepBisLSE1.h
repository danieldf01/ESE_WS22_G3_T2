/*
 * ContextSepBisLSEnde.h
 *
 *  Created on: 21.12.2022
 *      Author: acx514
 */

#ifndef LOGIK_HAUPTZUSTAENDE_FBM1_SEPBISLSENDE_CONTEXTSEPBISLSE1_H_
#define LOGIK_HAUPTZUSTAENDE_FBM1_SEPBISLSENDE_CONTEXTSEPBISLSE1_H_

#include "../../../../dispatcher/QnetHandler.h"
#include "../../../WsListen.h"
#include "../../../Zeit/Zeitmanager.h"
#include "../../../Defines.h"
#include "ActionsSepBisLSE1.h"
#include "BaseStateSepBisLSE1.h"
#include "WarteSepBisLSE1.h"

class ContextSepBisLSE1 {
private:
	BaseStateSepBisLSE1 *state;
	ActionsSepBisLSE1 *actions;
	WsListen *wsListen;
	QnetHandler *qnetHandler;
	name_attach_t *attach;
	Zeitmanager *zeitmanager;
	KonfigurationsdateiManager *konfig;
public:
	ContextSepBisLSE1(ActionsSepBisLSE1 *shared_action, WsListen *werkstueckListen, Zeitmanager *zeitmanager,
			KonfigurationsdateiManager *konfigManager);
	virtual ~ContextSepBisLSE1();

	void receiveSignal();

	//normales Verhalten
	void LsEAn();
	void WsAufWegZuLSE();
	void FBM2bereit();
	void WsWurdeUebergeben();

	//Fehlerverhalten
	void quittiert();
	void keinFehler();
	void fehlerVerschwunden();

	//E-Stop
	void eStop();
};

#endif /* LOGIK_HAUPTZUSTAENDE_FBM1_SEPBISLSENDE_CONTEXTSEPBISLSE1_H_ */
