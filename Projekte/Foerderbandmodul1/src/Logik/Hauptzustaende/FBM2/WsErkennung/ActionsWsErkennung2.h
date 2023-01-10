/*
 * ActionsWsErkennung1.h
 *
 *  Created on: 15.12.2022
 *      Author: Daniel Drefs Fernandes
 */

#ifndef LOGIK_HAUPTZUSTAENDE_FBM2_WSERKENNUNG_ACTIONSWSERKENNUNG2_H_
#define LOGIK_HAUPTZUSTAENDE_FBM2_WSERKENNUNG_ACTIONSWSERKENNUNG2_H_

#include <iostream>
#include <sys/dispatch.h>
#include "../../../Defines.h"
#include "../../../WsListen.h"
#include "../../../Werkstueck.h"
#include "../../../Zeit/Zeitmanager.h"

class ActionsWsErkennung2 {
protected:
	int logikID;
	WsListen *wsListen;
	Zeitmanager *zeitmanager;
	WsTyp wsTyp;
public:
	virtual ~ActionsWsErkennung2();

	void setWsListen(WsListen *wsListen) {this->wsListen = wsListen;};
	void setZeitmanager(Zeitmanager *zeitmanager) {this->zeitmanager = zeitmanager;};

	virtual void setupConnection();

	// normales verhalten
	virtual void speicherWSTyp();
	virtual void checkWSueberschlagen();
	virtual void WSinHSbisSeperator();
	virtual void sendFBM2Bereit();

	virtual void fehlerHoch();
	virtual void fehlerRunter();
	virtual void deleteWsHoehensensor();

	virtual void langsamRunter();
	virtual void schnellRunter();

	virtual void eStop();
};

#endif /* LOGIK_HAUPTZUSTAENDE_FBM2_WSERKENNUNG_ACTIONSWSERKENNUNG2_H_ */
