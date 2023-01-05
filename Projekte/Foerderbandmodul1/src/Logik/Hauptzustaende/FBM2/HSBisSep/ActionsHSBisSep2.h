/*
 * ActionsHSBisSep1.h
 *
 *  Created on: 15.12.2022
 *      Author: Daniel Drefs Fernandes
 */

#ifndef LOGIK_HAUPTZUSTAENDE_FBM2_HSBISSEP_ACTIONSHSBISSEP2_H_
#define LOGIK_HAUPTZUSTAENDE_FBM2_HSBISSEP_ACTIONSHSBISSEP2_H_

#include <iostream>
#include <sys/dispatch.h>
#include "../../../Defines.h"
#include "../../../WsListen.h"
#include "../../../Werkstueck.h"
#include "../../../Zeit/Zeitmanager.h"

class ActionsHSBisSep2 {
protected:
	int logikID;
	WsListen *wsListen;
	Zeitmanager *zeitmanager;
public:
	virtual ~ActionsHSBisSep2();

	void setWsListen(WsListen *wsListen) {this->wsListen = wsListen;};
	void setZeitmanager(Zeitmanager *zeitmanager) {this->zeitmanager = zeitmanager;};

	virtual void setupConnection();
	virtual void setMetallTrue();
	virtual void WsPassierenGefordert();
	virtual void WsPassierenNichtGefordert();
	virtual void WsNichtAussortierbar();
	virtual void WsAussortieren();
	virtual void fehlerHoch();
	virtual void fehlerRunter();
	virtual void entferneWsHSbisSep();
	virtual void schnellRunter();
	virtual void deleteTimerVerschwunden();
	virtual void eStop();
};

#endif /* LOGIK_HAUPTZUSTAENDE_FBM2_HSBISSEP_ACTIONSHSBISSEP2_H_ */
