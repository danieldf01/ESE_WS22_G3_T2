/*
 * ContextLSAbisHS.h
 *
 *  Created on: 14.12.2022
 *      Author: Daniel Drefs Fernandes
 */

#ifndef LOGIK_HAUPTZUSTAENDE_FBM1_LSANFANGBISHS_CONTEXTLSABISHS1_H_
#define LOGIK_HAUPTZUSTAENDE_FBM1_LSANFANGBISHS_CONTEXTLSABISHS1_H_

#include "../../../../dispatcher/QnetHandler.h"
#include "../../../WsListen.h"
#include "../../../Zeit/Zeitmanager.h"
#include "../../../Defines.h"
#include "ActionsLSAbisHS1.h"
#include "BaseStateLSAbisHS1.h"
#include "WartenLSAbisHS1.h"

class ContextLSAbisHS1 {
private:
	BaseStateLSAbisHS1 *state;
	ActionsLSAbisHS1 *actions;
	WsListen *wsListen;
	QnetHandler *qnetHandler;
	name_attach_t *attach;
	Zeitmanager *zeitmanager;
public:
	ContextLSAbisHS1(ActionsLSAbisHS1 *shared_action, WsListen *werkstueckListen, Zeitmanager *zeitmanager);
	virtual ~ContextLSAbisHS1();

	void receiveSignal();

	//normales Verhalten
	void WSinLSAbisHS();
	void HSaktiv();			//auch fuer WS zu frueh beim HS (WS vorgeschoben),
							//Werkstueck verschwunden

	//Fehlerverhalten
	void quittiert();
	void keinFehler();
	//Werkstueck verschwunden
	void Fverschwunden();
	//E-Stop
	void eStop();

};

#endif /* LOGIK_HAUPTZUSTAENDE_FBM1_LSANFANGBISHS_CONTEXTLSABISHS1_H_ */
