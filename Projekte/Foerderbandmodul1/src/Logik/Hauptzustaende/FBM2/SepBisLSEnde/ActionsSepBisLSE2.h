/*
 * ActionsSepBisLSEnde.h
 *
 *  Created on: 21.12.2022
 *      Author: acx514
 */

#ifndef LOGIK_HAUPTZUSTAENDE_FBM2_SEPBISLSENDE_ACTIONSSEPBISLSE2_H_
#define LOGIK_HAUPTZUSTAENDE_FBM2_SEPBISLSENDE_ACTIONSSEPBISLSE2_H_

#include <iostream>
#include <sys/dispatch.h>
#include "../../../Defines.h"
#include "../../../WsListen.h"
#include "../../../Werkstueck.h"
#include "../../../Zeit/Zeitmanager.h"

class ActionsSepBisLSE2 {
protected:
	int logikID;
	WsListen *wsListen;
	Zeitmanager *zeitmanager;
public:
	virtual ~ActionsSepBisLSE2();

	void setWsListen(WsListen *wsListen) {this->wsListen = wsListen;};
	void setZeitmanager(Zeitmanager *zeitmanager) {this->zeitmanager = zeitmanager;};

	virtual void setupConnection();

	virtual void seperatorAn();
	virtual void seperatorAus();

	virtual void fehlerHoch();
	virtual void fehlerRunter();

	virtual void entferneWsPassieren();

	virtual void schnellRunter();

	virtual void deleteTimerVerschwunden();
	virtual void sendFBM2Bereit();

	virtual void eStop();
};

#endif /* LOGIK_HAUPTZUSTAENDE_FBM2_SEPBISLSENDE_ACTIONSSEPBISLSE2_H_ */
