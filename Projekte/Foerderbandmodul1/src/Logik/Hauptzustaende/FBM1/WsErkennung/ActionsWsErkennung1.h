/*
 * ActionsWsErkennung1.h
 *
 *  Created on: 15.12.2022
 *      Author: Daniel Drefs Fernandes
 */

#ifndef LOGIK_HAUPTZUSTAENDE_FBM1_WSERKENNUNG_ACTIONSWSERKENNUNG1_H_
#define LOGIK_HAUPTZUSTAENDE_FBM1_WSERKENNUNG_ACTIONSWSERKENNUNG1_H_

#include <iostream>
#include <sys/dispatch.h>
#include "../../../Defines.h"
#include "../../../WsListen.h"
#include "../../../Werkstueck.h"
#include "../../../Zeit/Zeitmanager.h"

class ActionsWsErkennung1 {
protected:
	int logikID;
	WsListen *wsListen;
	Zeitmanager *zeitmanager;
public:
	virtual ~ActionsWsErkennung1();

	void setWsListen(WsListen *wsListen) {this->wsListen = wsListen;};
	void setZeitmanager(Zeitmanager *zeitmanager) {this->zeitmanager = zeitmanager;};

	virtual void setupConnection();
	virtual void langsamRunter();
	virtual void schnellRunter();
	virtual void WSinHSbisSeperator();
	virtual void fehlerHoch();
	virtual void fehlerRunter();
	virtual void deleteWsHoehensensor();
	virtual void eStop();
};

#endif /* LOGIK_HAUPTZUSTAENDE_FBM1_WSERKENNUNG_ACTIONSWSERKENNUNG1_H_ */
