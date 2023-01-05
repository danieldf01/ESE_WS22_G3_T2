/*
 * BaseStateLSAbisHS2.h
 *
 *  Created on: 23.12.2022
 *      Author: Daniel Drefs Fernandes
 */

#ifndef LOGIK_HAUPTZUSTAENDE_FBM2_LSANFANGBISHS_BASESTATELSABISHS2_H_
#define LOGIK_HAUPTZUSTAENDE_FBM2_LSANFANGBISHS_BASESTATELSABISHS2_H_

#include <iostream>
#include "ActionsLSAbisHS2.h"

class BaseStateLSAbisHS2 {
protected:
	ActionsLSAbisHS2 *actions;
	WsListen *wsListen;
	Zeitmanager *zeitmanager;
public:
	virtual ~BaseStateLSAbisHS2() {};

	void setActions(ActionsLSAbisHS2 *actions){this->actions = actions;};
	void setWsListen(WsListen *wsListen) {this->wsListen = wsListen;};
	void setZeitmanager(Zeitmanager *zeitmanager) {this->zeitmanager = zeitmanager;};

	virtual void entry() = 0;
	virtual void exit() = 0;

	//normales Verhalten
	virtual void WSinLSAbisHS() = 0;
	virtual void HSaktiv() = 0;			//auch fuer Fehler WS zu frueh beim HS (WS vorgeschoben oder Hand drunter)
										//und Werkstueck verschwunden

	//Fehlerverhalten
	virtual void quittiert() = 0;
	virtual void keinFehler() = 0;
	//Werkstueck verschwunden
	virtual void Fverschwunden() = 0;
	//E-Stop
	virtual void eStop() = 0;
};

#endif /* LOGIK_HAUPTZUSTAENDE_FBM2_LSANFANGBISHS_BASESTATELSABISHS2_H_ */
