/*
 * ContextHSBisSep2.h
 *
 *  Created on: 15.12.2022
 *      Author: Daniel Drefs Fernandes
 */

#ifndef LOGIK_HAUPTZUSTAENDE_FBM2_HSBISSEP_CONTEXTHSBISSEP2_H_
#define LOGIK_HAUPTZUSTAENDE_FBM2_HSBISSEP_CONTEXTHSBISSEP2_H_

#include "../../../../dispatcher/QnetHandler.h"
#include "../../../WsListen.h"
#include "../../../Zeit/Zeitmanager.h"
#include "../../../Defines.h"
#include "ActionsHSBisSep2.h"
#include "BaseStateHSBisSep2.h"
#include "WartenHSBisSep2.h"

class ContextHSBisSep2 {
private:
	BaseStateHSBisSep2 *state;
	ActionsHSBisSep2 *actions;
	WsListen *wsListen;
	QnetHandler *qnetHandler;
	name_attach_t *attach;
	Zeitmanager *zeitmanager;
	Rutsche *rutsche;
public:
	ContextHSBisSep2(ActionsHSBisSep2 *shared_action, WsListen *werkstueckListen, Zeitmanager *zeitmanager, Rutsche *r);
	virtual ~ContextHSBisSep2();

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

#endif /* LOGIK_HAUPTZUSTAENDE_FBM2_HSBISSEP_CONTEXTHSBISSEP2_H_ */
