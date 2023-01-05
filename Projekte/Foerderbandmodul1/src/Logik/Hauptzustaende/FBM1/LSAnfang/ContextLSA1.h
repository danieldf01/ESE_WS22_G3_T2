/*
 * ContextLSAnfang.h
 *
 *  Created on: 11.12.2022
 *      Author: Daniel
 */

#ifndef LOGIK_HAUPTZUSTAENDE_FBM1_LSANFANG_CONTEXTLSA1_H_
#define LOGIK_HAUPTZUSTAENDE_FBM1_LSANFANG_CONTEXTLSA1_H_

#include "../../../../dispatcher/QnetHandler.h"
#include "../../../WsListen.h"
#include "../../../Zeit/Zeitmanager.h"
#include "../../../Defines.h"
#include "ActionsLSA1.h"
#include "BaseStateLSA1.h"
#include "WarteAufWsLSA1.h"


class ContextLSA1 {
private:
	BaseStateLSA1 *state;
	ActionsLSA1 *actions;
	WsListen *wsListen;
	QnetHandler *qnetHandler;
	name_attach_t *attach;
	Zeitmanager *zeitmanager;
public:
	ContextLSA1(ActionsLSA1 *shared_action, WsListen *werkstueckListen, Zeitmanager *zeitmanager);
	virtual ~ContextLSA1();

	void receiveSignal();

	//normales Verhalten
	void LSan();
	void LSaus();
	void timerAbstand();

	//Fehlerverhalten
	void WSstecktFest();
	void quittiert();
	void keinFehler();
	//E-Stop
	void eStop();
};

#endif /* LOGIK_HAUPTZUSTAENDE_FBM1_LSANFANG_CONTEXTLSA1_H_ */
