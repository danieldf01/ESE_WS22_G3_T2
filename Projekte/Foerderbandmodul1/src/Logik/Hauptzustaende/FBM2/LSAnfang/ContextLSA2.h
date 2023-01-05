/*
 * ContextLSA2.h
 *
 *  Created on: 22.12.2022
 *      Author: tobias
 */

#ifndef LOGIK_HAUPTZUSTAENDE_FBM2_LSANFANG_CONTEXTLSA2_H_
#define LOGIK_HAUPTZUSTAENDE_FBM2_LSANFANG_CONTEXTLSA2_H_

#include "../../../../dispatcher/QnetHandler.h"
#include "../../../WsListen.h"
#include "../../../Zeit/Zeitmanager.h"
#include "../../../Defines.h"
#include "ActionsLSA2.h"
#include "BaseStateLSA2.h"
#include "WarteAufFBM2.h"

class ContextLSA2 {
private:
	BaseStateLSA2 *state;
	ActionsLSA2 *actions;
	WsListen *wsListen;
	QnetHandler *qnetHandler;
	name_attach_t *attach;
	Zeitmanager *zeitmanager;
public:
	ContextLSA2(ActionsLSA2 *shared_action, WsListen *werkstueckListen, Zeitmanager *zeitmanagerFSM);
	virtual ~ContextLSA2();

	void receiveSignal();

	//normales Verhalten
	void lsAnfangAn();
	void fbm1Bereit();
	void fbm2Bereit();
	void lsAnfangAus();
	void fbm1WsLosgeschickt();
	void fbm1WsUebergeben();

	//Fehlerverhalten
	void fehlerVerschwunden();
	void quittiert();
	void keinFehler();
	//E-Stop
	void eStop();
};

#endif /* LOGIK_HAUPTZUSTAENDE_FBM2_LSANFANG_CONTEXTLSA2_H_ */
