/*
 * ActionsPassieren.h
 *
 *  Created on: 07.01.2023
 *      Author: Daniel Drefs Fernandes
 */

#ifndef LOGIK_HAUPTZUSTAENDE_FBM1_PASSIEREN_ACTIONSPASSIEREN_H_
#define LOGIK_HAUPTZUSTAENDE_FBM1_PASSIEREN_ACTIONSPASSIEREN_H_

#include <iostream>
#include <sys/dispatch.h>
#include "../../../Defines.h"
#include "../../../WsListen.h"
#include "../../../Werkstueck.h"

class ActionsPassieren {
protected:
	int logikID;
	WsListen *wsListen;
public:
	virtual ~ActionsPassieren();

	void setWsListen(WsListen *wsListen) {this->wsListen = wsListen;};

	virtual void setupConnection();

	virtual void seperatorAn();
	virtual void seperatorAus();

	virtual void WsAufWegZuLSE();

	virtual void eStop();
};

#endif /* LOGIK_HAUPTZUSTAENDE_FBM1_PASSIEREN_ACTIONSPASSIEREN_H_ */
