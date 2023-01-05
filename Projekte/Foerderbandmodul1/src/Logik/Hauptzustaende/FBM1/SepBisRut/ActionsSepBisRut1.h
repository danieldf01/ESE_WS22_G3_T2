/*
 * ActionsSepBisRut1.h
 *
 *  Created on: 11.12.2022
 *      Author: Daniel
 */
// DONE
#ifndef LOGIK_HAUPTZUSTAENDE_FBM1_SEPBISRUT_ACTIONSSEPBISRUT1_H_
#define LOGIK_HAUPTZUSTAENDE_FBM1_SEPBISRUT_ACTIONSSEPBISRUT1_H_

#include "../../../Defines.h"
#include "../../../WsListen.h"
#include "../../../Werkstueck.h"
#include "../../../Zeit/Zeitmanager.h"

class ActionsSepBisRut1 {
protected:
	int logikID;
	WsListen *wsListen;
	Zeitmanager *zeitmanager;
public:
	virtual ~ActionsSepBisRut1();

	void setWsListen(WsListen *wsListen){this->wsListen = wsListen;};
	void setZeitmanager(Zeitmanager *zeitmanager){this->zeitmanager = zeitmanager;};

	virtual void setupConnection();

	virtual void seperatorAn();
	virtual void seperatorAus();

	virtual void fehlerHoch();
	virtual void fehlerRunter();

	virtual void schnellRunter();
	virtual void zerstoereWsAussortieren();
	virtual void deleteTimerVerschwunden();
};

#endif /* LOGIK_HAUPTZUSTAENDE_FBM1_SEPBISRUT_ACTIONSSEPBISRUT1_H_ */
