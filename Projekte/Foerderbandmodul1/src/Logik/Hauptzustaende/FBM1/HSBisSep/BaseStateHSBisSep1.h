/*
 * BaseStateHSBisSep1.h
 *
 *  Created on: 15.12.2022
 *      Author: Daniel Drefs Fernandes
 */

#ifndef LOGIK_HAUPTZUSTAENDE_FBM1_HSBISSEP_BASESTATEHSBISSEP1_H_
#define LOGIK_HAUPTZUSTAENDE_FBM1_HSBISSEP_BASESTATEHSBISSEP1_H_

#include <iostream>
#include <algorithm>
#include "ActionsHSBisSep1.h"
#include "../../Rutsche/Rutsche.h"

class BaseStateHSBisSep1 {
protected:
	ActionsHSBisSep1 *actions;
	WsListen *wsListen;
	Zeitmanager *zeitmanager;
	Rutsche *rutsche;
public:
	virtual ~BaseStateHSBisSep1() {};

	void setActions(ActionsHSBisSep1 *actions){this->actions = actions;};
	void setWsListen(WsListen *wsListen) {this->wsListen = wsListen;};
	void setZeitmanager(Zeitmanager *zeitmanager) {this->zeitmanager = zeitmanager;};
	void setRutsche(Rutsche *rutsche) {this->rutsche = rutsche;};

	virtual void entry() = 0;
	virtual void exit() = 0;

	//normales Verhalten
	virtual void WSinHSbisSep() = 0;
	virtual void MetSenAn() = 0;		//auch fuer Fehler WS zu viel
	virtual void LSSepAn() = 0;			//auch fuer Fehler WS zu viel und WS zu frueh
	virtual void aussortieren1() = 0;
	virtual void aussortieren2() = 0;
	virtual void aussortieren3() = 0;
	virtual void aussortieren4() = 0;

	//Fehlerverhalten
	virtual void quittiert() = 0;
	virtual void keinFehler() = 0;
	virtual void fehlerCntDown() = 0;
	//Werkstueck verschwunden
	virtual void fehlerVerschwunden() = 0;
	//E-Stop
	virtual void eStop() = 0;
};

#endif /* LOGIK_HAUPTZUSTAENDE_FBM1_HSBISSEP_BASESTATEHSBISSEP1_H_ */
