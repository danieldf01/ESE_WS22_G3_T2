/*
 * ContextLSAbisHS.h
 *
 *  Created on: 14.12.2022
 *      Author: Daniel Drefs Fernandes
 */

#ifndef LOGIK_HAUPTZUSTAENDE_FBM2_LSANFANGBISHS_CONTEXTLSABISHS2_H_
#define LOGIK_HAUPTZUSTAENDE_FBM2_LSANFANGBISHS_CONTEXTLSABISHS2_H_

#include "../../../../dispatcher/QnetHandler.h"
#include "../../../WsListen.h"
#include "../../../Zeit/Zeitmanager.h"
#include "../../../Defines.h"
#include "ActionsLSAbisHS2.h"
#include "BaseStateLSAbisHS2.h"
#include "WartenLSAbisHS2.h"

class ContextLSAbisHS2 {
private:
	BaseStateLSAbisHS2 *state;
	ActionsLSAbisHS2 *actions;
	WsListen *wsListen;
	QnetHandler *qnetHandler;
	name_attach_t *attach;
	Zeitmanager *zeitmanager;
public:
	ContextLSAbisHS2(ActionsLSAbisHS2 *shared_action, WsListen *werkstueckListen, Zeitmanager *zeitmanager);
	virtual ~ContextLSAbisHS2();

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
