/*
 * ActionsLSA2.h
 *
 *  Created on: 22.12.2022
 *      Author: tobias
 */

#ifndef LOGIK_HAUPTZUSTAENDE_FBM2_LSANFANG_ACTIONSLSA2_H_
#define LOGIK_HAUPTZUSTAENDE_FBM2_LSANFANG_ACTIONSLSA2_H_

#include <iostream>
#include <sys/dispatch.h>
#include "../../../Defines.h"
#include "../../../WsListen.h"
#include "../../../Werkstueck.h"
#include "../../../Zeit/Zeitmanager.h"

class ActionsLSA2 {
protected:
	int wsID;
	int logikID;
	WsListen *wsListen;
	Werkstueck *werkstueck;
	Zeitmanager *zeitmanager;
public:
	ActionsLSA2();
	virtual ~ActionsLSA2();

	void setWsListen(WsListen *wsListen){this->wsListen = wsListen;};
	void setZeitmanager(Zeitmanager *zeitmanager){this->zeitmanager = zeitmanager;};

	virtual void setupConnection();

	virtual void WSinLSAbisHS();
	virtual void sendFBM2Bereit();
	virtual void schnellHoch();
	virtual void schnellRunter();
	virtual void schnellRunter1();
	virtual void fehlerHoch();
	virtual void fehlerRunter();
	virtual void entferneWsLSA2();
	virtual void eStop();
};

#endif /* LOGIK_HAUPTZUSTAENDE_FBM2_LSANFANG_ACTIONSLSA2_H_ */
