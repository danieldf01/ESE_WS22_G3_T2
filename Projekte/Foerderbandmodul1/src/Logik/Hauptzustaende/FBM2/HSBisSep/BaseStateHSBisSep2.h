/*
 * BaseStateHSBisSep2.h
 *
 *  Created on: 15.12.2022
 *      Author: Daniel Drefs Fernandes
 */

#ifndef LOGIK_HAUPTZUSTAENDE_FBM2_HSBISSEP_BASESTATEHSBISSEP2_H_
#define LOGIK_HAUPTZUSTAENDE_FBM2_HSBISSEP_BASESTATEHSBISSEP2_H_

#include <iostream>
#include <algorithm>
#include "ActionsHSBisSep2.h"
#include "../../FBM1/Rutsche/Rutsche.h"

class BaseStateHSBisSep2 {
protected:
	ActionsHSBisSep2 *actions;
	WsListen *wsListen;
	Zeitmanager *zeitmanager;
	Rutsche *rutsche;
public:
	virtual ~BaseStateHSBisSep2() {};

	void setActions(ActionsHSBisSep2 *actions){this->actions = actions;};
	void setWsListen(WsListen *wsListen) {this->wsListen = wsListen;};
	void setZeitmanager(Zeitmanager *zeitmanager) {this->zeitmanager = zeitmanager;};
	void setRutsche(Rutsche *rutsche) {this->rutsche = rutsche;};

	virtual void entry() = 0;
	virtual void exit() = 0;

	//normales Verhalten
	virtual void WSinHSbisSep() = 0;
	virtual void MetSenAn() = 0;		//auch fuer Fehler WS zu viel
	virtual void LSSepAn() = 0;			//auch fuer Fehler WS zu viel und WS zu frueh
	virtual void aussortieren1() = 0;	// fuer den Zweig F_WS_zu_frueh
	virtual void aussortieren2() = 0;	// fuer den Zweig geforderterWSTyp
	virtual void aussortieren3() = 0;	// fuer den Zweig Rutsche voll

	//Fehlerverhalten
	virtual void quittiert() = 0;
	virtual void keinFehler() = 0;
	virtual void fehlerCntDown() = 0;
	//Werkstueck verschwunden
	virtual void fehlerVerschwunden() = 0;
	//E-Stop
	virtual void eStop() = 0;
};

#endif /* LOGIK_HAUPTZUSTAENDE_FBM2_HSBISSEP_BASESTATEHSBISSEP2_H_ */
