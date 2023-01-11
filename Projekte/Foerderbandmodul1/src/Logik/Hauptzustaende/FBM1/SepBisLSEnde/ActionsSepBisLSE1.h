/*
 * ActionsSepBisLSEnde.h
 *
 *  Created on: 21.12.2022
 *      Author: acx514
 */

#ifndef LOGIK_HAUPTZUSTAENDE_FBM1_SEPBISLSENDE_ACTIONSSEPBISLSE1_H_
#define LOGIK_HAUPTZUSTAENDE_FBM1_SEPBISLSENDE_ACTIONSSEPBISLSE1_H_

#include <iostream>
#include <sys/dispatch.h>
#include "../../../Defines.h"
#include "../../../WsListen.h"
#include "../../../Werkstueck.h"
#include "../../../Zeit/Zeitmanager.h"

class ActionsSepBisLSE1 {
protected:
	int logikID;
	WsListen *wsListen;
	Zeitmanager *zeitmanager;
public:
	virtual ~ActionsSepBisLSE1();

	void setWsListen(WsListen *wsListen) {this->wsListen = wsListen;};
	void setZeitmanager(Zeitmanager *zeitmanager) {this->zeitmanager = zeitmanager;};

	virtual void setupConnection();

	virtual void fehlerHoch();
	virtual void fehlerRunter();

	virtual void entferneWsPassieren();

	virtual void schnellRunter();
	virtual void stopHoch();
	virtual void stopRunter();

	virtual void FBM1bereit();
	virtual void FBM1WsLosgeschickt();
	virtual void FBM1WsUebergeben();

	virtual void deleteTimerVerschwunden();

	virtual void eStop();
};

#endif /* LOGIK_HAUPTZUSTAENDE_FBM1_SEPBISLSENDE_ACTIONSSEPBISLSE1_H_ */
