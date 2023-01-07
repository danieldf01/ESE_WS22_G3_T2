/*
 * ContextPassieren.h
 *
 *  Created on: 07.01.2023
 *      Author: Daniel Drefs Fernandes
 */

#ifndef LOGIK_HAUPTZUSTAENDE_FBM1_PASSIEREN_CONTEXTPASSIEREN_H_
#define LOGIK_HAUPTZUSTAENDE_FBM1_PASSIEREN_CONTEXTPASSIEREN_H_

#include "../../../../dispatcher/QnetHandler.h"
#include "../../../WsListen.h"
#include "../../../Defines.h"
#include "ActionsPassieren.h"
#include "BaseStatePassieren.h"
#include "WartenPassieren.h"

class ContextPassieren {
private:
	BaseStatePassieren *state;
	ActionsPassieren *actions;
	WsListen *wsListen;
	QnetHandler *qnetHandler;
	name_attach_t *attach;
	KonfigurationsdateiManager *konfig;
public:
	ContextPassieren(ActionsPassieren *shared_action, WsListen *werkstueckListen, KonfigurationsdateiManager *konfigManager);
	virtual ~ContextPassieren();

	void receiveSignal();

	//normales Verhalten
	void WsPassieren();
	void WeicheSchliessen();

	//E-Stop
	void eStop();
};

#endif /* LOGIK_HAUPTZUSTAENDE_FBM1_PASSIEREN_CONTEXTPASSIEREN_H_ */
