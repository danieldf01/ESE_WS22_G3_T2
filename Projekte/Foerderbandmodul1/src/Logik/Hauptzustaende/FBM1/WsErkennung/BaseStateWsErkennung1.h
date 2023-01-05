/*
 * BaseStateWsErkennung1.h
 *
 *  Created on: 15.12.2022
 *      Author: Daniel Drefs Fernandes
 */

#ifndef LOGIK_HAUPTZUSTAENDE_FBM1_WSERKENNUNG_BASESTATEWSERKENNUNG1_H_
#define LOGIK_HAUPTZUSTAENDE_FBM1_WSERKENNUNG_BASESTATEWSERKENNUNG1_H_

#include <iostream>
#include "ActionsWsErkennung1.h"

class BaseStateWsErkennung1 {
protected:
	ActionsWsErkennung1 *actions;
	WsListen *wsListen;
	Zeitmanager *zeitmanager;
public:
	virtual ~BaseStateWsErkennung1() {};

	void setActions(ActionsWsErkennung1 *actions){this->actions = actions;};
	void setWsListen(WsListen *wsListen) {this->wsListen = wsListen;};
	void setZeitmanager(Zeitmanager *zeitmanager) {this->zeitmanager = zeitmanager;};

	virtual void entry() = 0;
	virtual void exit() = 0;

	//normales Verhalten
	virtual void WSinHS() = 0;
	virtual void WsTyp() = 0;		//auch fuer Fehler Hoehenmessung (WS zu schnell oder verschwunden)

	//Fehlerverhalten
	virtual void quittiert() = 0;
	virtual void keinFehler() = 0;
	//Werkstueck zu schnell oder verschwunden
	virtual void fehlerHoehenmessung() = 0;
	//E-Stop
	virtual void eStop() = 0;
};

#endif /* LOGIK_HAUPTZUSTAENDE_FBM1_WSERKENNUNG_BASESTATEWSERKENNUNG1_H_ */
