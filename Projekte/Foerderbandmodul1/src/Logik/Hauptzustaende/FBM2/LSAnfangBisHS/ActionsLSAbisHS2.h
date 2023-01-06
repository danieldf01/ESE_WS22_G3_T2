/*
 * ActionsLSAbisHS2.h
 *
 *  Created on: 14.12.2022
 *      Author: Daniel Drefs Fernandes
 */

#ifndef LOGIK_HAUPTZUSTAENDE_FBM2_LSANFANGBISHS_ACTIONSLSABISHS2_H_
#define LOGIK_HAUPTZUSTAENDE_FBM2_LSANFANGBISHS_ACTIONSLSABISHS2_H_

#include <iostream>
#include <sys/dispatch.h>
#include "../../../Defines.h"
#include "../../../WsListen.h"
#include "../../../Werkstueck.h"
#include "../../../Zeit/Zeitmanager.h"

class ActionsLSAbisHS2 {
protected:
	int logikID;
	WsListen *wsListen;
	Zeitmanager *zeitmanager;
public:
	virtual ~ActionsLSAbisHS2();

	void setWsListen(WsListen *wsListen) {this->wsListen = wsListen;};
	void setZeitmanager(Zeitmanager *zeitmanager) {this->zeitmanager = zeitmanager;};

	virtual void setupConnection();
	virtual void WSinHS();
	virtual void fehlerHoch();
	virtual void fehlerRunter();
	virtual void entferneWsLSAbisHS();
	virtual void schnellRunter();
	virtual void HSleeren();
	virtual void sendFBM2Bereit();
	virtual void eStop();
};

#endif /* LOGIK_HAUPTZUSTAENDE_FBM2_LSANFANGBISHS_ACTIONSLSABISHS2_H_ */
