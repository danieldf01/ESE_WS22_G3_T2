/*
 * ActionsLSAnfang.h
 *
 *  Created on: 11.12.2022
 *      Author: Daniel
 */

#ifndef LOGIK_HAUPTZUSTAENDE_FBM1_LSANFANG_ACTIONSLSA1_H_
#define LOGIK_HAUPTZUSTAENDE_FBM1_LSANFANG_ACTIONSLSA1_H_

#include <iostream>
#include <sys/dispatch.h>
#include "../../../Defines.h"
#include "../../../WsListen.h"
#include "../../../Werkstueck.h"
#include "../../../Zeit/Zeitmanager.h"

class ActionsLSA1 {
protected:
	int wsID;
	int logikID;
	WsListen *wsListen;
	Werkstueck *werkstueck;
	Zeitmanager *zeitmanager;
public:
	ActionsLSA1();
	virtual ~ActionsLSA1();

	void setWsListen(WsListen *wsListen){this->wsListen = wsListen;};
	void setZeitmanager(Zeitmanager *zeitmanager){this->zeitmanager = zeitmanager;};

	virtual void setupConnection();
	virtual void schnellHoch();
	virtual void erstelleWS();
	virtual void schnellRunter();
	virtual void WSinLSAbisHS();
	virtual void fehlerHoch();
	virtual void fehlerRunter();
	virtual void eStop();
	virtual void slq1_an();
	virtual void slq1_aus();
};

#endif /* LOGIK_HAUPTZUSTAENDE_FBM1_LSANFANG_ACTIONSLSA1_H_ */
