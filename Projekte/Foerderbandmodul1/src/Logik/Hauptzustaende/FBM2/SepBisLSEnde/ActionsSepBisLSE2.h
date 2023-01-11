/*
 * ActionsSepBisLSEnde.h
 *
 *  Created on: 21.12.2022
 *      Author: acx514
 */

#ifndef LOGIK_HAUPTZUSTAENDE_FBM2_SEPBISLSENDE_ACTIONSSEPBISLSE2_H_
#define LOGIK_HAUPTZUSTAENDE_FBM2_SEPBISLSENDE_ACTIONSSEPBISLSE2_H_

#include <string>
#include <iostream>
#include <sys/dispatch.h>
#include "../../../Defines.h"
#include "../../../WsListen.h"
#include "../../../Werkstueck.h"
#include "../../../WsTyp.h"
#include "../../../Zeit/Zeitmanager.h"
#include "../../../MQTTClientHandler/MQTTClientHandler.h"
#include "../../../konfigurationsdateiManager/KonfigurationsdateiManager.h"

class ActionsSepBisLSE2 {
protected:
	int logikID;
	WsListen *wsListen;
	Zeitmanager *zeitmanager;
	KonfigurationsdateiManager *dateiManager;
public:
	virtual ~ActionsSepBisLSE2();

	void setWsListen(WsListen *wsListen) {this->wsListen = wsListen;};
	void setZeitmanager(Zeitmanager *zeitmanager) {this->zeitmanager = zeitmanager;};
	void setKonfigurationsdateiManager(KonfigurationsdateiManager *dateiManager) {this->dateiManager = dateiManager;};

	virtual void setupConnection();

	virtual void seperatorAn();
	virtual void seperatorAus();

	virtual void fehlerHoch();
	virtual void fehlerRunter();

	virtual void entferneWsPassieren();

	virtual void schnellRunter();

	virtual void deleteTimerVerschwunden();
	virtual void sendFBM2Bereit();
	virtual void augabeKonsoleMQTT();

	virtual void eStop();
};

#endif /* LOGIK_HAUPTZUSTAENDE_FBM2_SEPBISLSENDE_ACTIONSSEPBISLSE2_H_ */
