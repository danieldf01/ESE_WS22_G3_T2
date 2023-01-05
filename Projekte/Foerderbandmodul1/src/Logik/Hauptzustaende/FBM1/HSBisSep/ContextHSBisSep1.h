/*
 * ContextHSBisSep1.h
 *
 *  Created on: 15.12.2022
 *      Author: Daniel Drefs Fernandes
 */

#ifndef LOGIK_HAUPTZUSTAENDE_FBM1_HSBISSEP_CONTEXTHSBISSEP1_H_
#define LOGIK_HAUPTZUSTAENDE_FBM1_HSBISSEP_CONTEXTHSBISSEP1_H_

#include "../../../../dispatcher/QnetHandler.h"
#include "../../../WsListen.h"
#include "../../../Zeit/Zeitmanager.h"
#include "../../../Defines.h"
#include "ActionsHSBisSep1.h"
#include "BaseStateHSBisSep1.h"
#include "WartenHSBisSep1.h"

class ContextHSBisSep1 {
private:
	BaseStateHSBisSep1 *state;
	ActionsHSBisSep1 *actions;
	WsListen *wsListen;
	QnetHandler *qnetHandler;
	name_attach_t *attach;
	Zeitmanager *zeitmanager;
	Rutsche *rutsche;
public:
	ContextHSBisSep1(ActionsHSBisSep1 *shared_action, WsListen *werkstueckListen, Zeitmanager *zeitmanager, Rutsche *r);
	virtual ~ContextHSBisSep1();

	void receiveSignal();

	//normales Verhalten
	void WSinHSbisSep();
	void MetSenAn();		//auch fuer Fehler WS zu viel
	void LSSepAn();			//auch fuer Fehler WS zu viel und WS zu frueh

	//Fehlerverhalten
	void quittiert();
	void keinFehler();
	void fehlerCntDown();
	//Werkstueck verschwunden
	void fehlerVerschwunden();
	//E-Stop
	void eStop();
};

#endif /* LOGIK_HAUPTZUSTAENDE_FBM1_HSBISSEP_CONTEXTHSBISSEP1_H_ */
