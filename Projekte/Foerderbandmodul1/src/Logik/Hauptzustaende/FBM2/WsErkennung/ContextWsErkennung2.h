/*
 * ContextWsErkennung2.h
 *
 *  Created on: 15.12.2022
 *      Author: Daniel Drefs Fernandes
 */

#ifndef LOGIK_HAUPTZUSTAENDE_FBM2_WSERKENNUNG_CONTEXTWSERKENNUNG2_H_
#define LOGIK_HAUPTZUSTAENDE_FBM2_WSERKENNUNG_CONTEXTWSERKENNUNG2_H_

#include "../../../../dispatcher/QnetHandler.h"
#include "../../../WsListen.h"
#include "../../../Zeit/Zeitmanager.h"
#include "../../../Defines.h"
#include "ActionsWsErkennung2.h"
#include "BaseStateWsErkennung2.h"
#include "WartenWsErkennung2.h"

class ContextWsErkennung2 {
private:
	BaseStateWsErkennung2 *state;
	ActionsWsErkennung2 *actions;
	WsListen *wsListen;
	QnetHandler *qnetHandler;
	name_attach_t *attach;
	Zeitmanager *zeitmanager;
public:
	ContextWsErkennung2(ActionsWsErkennung2 *shared_action, WsListen *werkstueckListen, Zeitmanager *zeitmanager);
	virtual ~ContextWsErkennung2();

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

#endif /* LOGIK_HAUPTZUSTAENDE_FBM2_WSERKENNUNG_CONTEXTWSERKENNUNG2_H_ */
