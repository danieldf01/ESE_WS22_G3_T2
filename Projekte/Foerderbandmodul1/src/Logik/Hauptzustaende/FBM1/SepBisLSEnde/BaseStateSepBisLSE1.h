/*
 * BaseStateSepBisLSEnde.h
 *
 *  Created on: 21.12.2022
 *      Author: acx514
 */

#ifndef LOGIK_HAUPTZUSTAENDE_FBM1_SEPBISLSENDE_BASESTATESEPBISLSE1_H_
#define LOGIK_HAUPTZUSTAENDE_FBM1_SEPBISLSENDE_BASESTATESEPBISLSE1_H_

#include "ActionsSepBisLSE1.h"
#include "../../../konfigurationsdateiManager/KonfigurationsdateiManager.h"

class BaseStateSepBisLSE1 {
protected:
	ActionsSepBisLSE1 *actions;
	WsListen *wsListen;
	KonfigurationsdateiManager *konfig;
	Zeitmanager *zeitmanager;
public:
	virtual ~BaseStateSepBisLSE1() {};

	void setActions(ActionsSepBisLSE1 *actions){this->actions = actions;};
	void setWsListen(WsListen *wsListen) {this->wsListen = wsListen;};
	void setKonfig(KonfigurationsdateiManager *konfig) {this->konfig = konfig;};
	void setZeitmanager(Zeitmanager *zeitmanager) {this->zeitmanager = zeitmanager;};

	virtual void entry() = 0;
	virtual void exit() = 0;

	//normales Verhalten
	virtual void LsEAn() = 0;
	virtual void WsAufWegZuLSE() = 0;
	virtual void FBM2bereit() = 0;
	virtual void WsWurdeUebergeben() = 0;

	//Fehlerverhalten
	virtual void quittiert() = 0;
	virtual void keinFehler() = 0;
	virtual void fehlerVerschwunden() = 0;

	//E-Stop
	virtual void eStop() = 0;
};



#endif /* LOGIK_HAUPTZUSTAENDE_FBM1_SEPBISLSENDE_BASESTATESEPBISLSE1_H_ */
