/*
 * ContextWsErkennung1.h
 *
 *  Created on: 15.12.2022
 *      Author: Daniel Drefs Fernandes
 */

#ifndef LOGIK_HAUPTZUSTAENDE_FBM1_WSERKENNUNG_CONTEXTWSERKENNUNG1_H_
#define LOGIK_HAUPTZUSTAENDE_FBM1_WSERKENNUNG_CONTEXTWSERKENNUNG1_H_

#include "../../../../dispatcher/QnetHandler.h"
#include "../../../WsListen.h"
#include "../../../Zeit/Zeitmanager.h"
#include "../../../Defines.h"
#include "ActionsWsErkennung1.h"
#include "BaseStateWsErkennung1.h"
#include "WartenWsErkennung1.h"

class ContextWsErkennung1 {
private:
	BaseStateWsErkennung1 *state;
	ActionsWsErkennung1 *actions;
	WsListen *wsListen;
	QnetHandler *qnetHandler;
	name_attach_t *attach;
	Zeitmanager *zeitmanager;
public:
	ContextWsErkennung1(ActionsWsErkennung1 *shared_action, WsListen *werkstueckListen, Zeitmanager *zeitmanager);
	virtual ~ContextWsErkennung1();

	void receiveSignal();

	//normales Verhalten
	void WSinHS();
	void WsTyp();		//auch fuer Fehler Hoehenmessung (WS zu schnell oder verschwunden)

	//Fehlerverhalten
	void quittiert();
	void keinFehler();
	//Werkstueck zu schnell oder verschwunden
	void fehlerHoehenmessung();
	//E-Stop
	void eStop();
};

#endif /* LOGIK_HAUPTZUSTAENDE_FBM1_WSERKENNUNG_CONTEXTWSERKENNUNG1_H_ */
