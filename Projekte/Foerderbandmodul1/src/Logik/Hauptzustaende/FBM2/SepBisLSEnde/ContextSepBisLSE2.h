/*
 * ContextSepBisLSEnde.h
 *
 *  Created on: 21.12.2022
 *      Author: acx514
 */

#ifndef LOGIK_HAUPTZUSTAENDE_FBM2_SEPBISLSENDE_CONTEXTSEPBISLSE2_H_
#define LOGIK_HAUPTZUSTAENDE_FBM2_SEPBISLSENDE_CONTEXTSEPBISLSE2_H_

#include "../../../../dispatcher/QnetHandler.h"
#include "../../../WsListen.h"
#include "../../../Zeit/Zeitmanager.h"
#include "../../../Defines.h"
#include "ActionsSepBisLSE2.h"
#include "BaseStateSepBisLSE2.h"
#include "WarteSepBisLSE2.h"

class ContextSepBisLSE2 {
private:
	BaseStateSepBisLSE2 *state;
	ActionsSepBisLSE2 *actions;
	WsListen *wsListen;
	QnetHandler *qnetHandler;
	name_attach_t *attach;
	Zeitmanager *zeitmanager;
	KonfigurationsdateiManager *konfig;
public:
	ContextSepBisLSE2(ActionsSepBisLSE2 *shared_action, WsListen *werkstueckListen, Zeitmanager *zeitmanager, KonfigurationsdateiManager *konfigManager);
	virtual ~ContextSepBisLSE2();

	void receiveSignal();

	//normales Verhalten
	void LsEAn();
	void LsEAus();
	void WsPassieren();
	void WeicheSchliessen();

	//Fehlerverhalten
	void quittiert();
	void keinFehler();
	void fehlerVerschwunden();

	//E-Stop
	void eStop();
};

#endif /* LOGIK_HAUPTZUSTAENDE_FBM2_SEPBISLSENDE_CONTEXTSEPBISLSE2_H_ */
