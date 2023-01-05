/*
 * BaseStateSepBisRut1.h
 *
 *  Created on: 11.12.2022
 *      Author: Daniel
 */

#ifndef LOGIK_HAUPTZUSTAENDE_FBM1_SEPBISRUT_BASESTATESEPBISRUT1_H_
#define LOGIK_HAUPTZUSTAENDE_FBM1_SEPBISRUT_BASESTATESEPBISRUT1_H_

#include "ActionsSepBisRut1.h"
#include "../../../konfigurationsdateiManager/KonfigurationsdateiManager.h"

class BaseStateSepBisRut1 {
protected:
	ActionsSepBisRut1 *actions;
	WsListen *wsListen;
	KonfigurationsdateiManager *konfig;
public:
	virtual ~BaseStateSepBisRut1() {};

	void setActions(ActionsSepBisRut1 *actions){this->actions = actions;};
	void setWsListen(WsListen *wsListen) {this->wsListen = wsListen;};
	void setKonfig(KonfigurationsdateiManager *konfig) {this->konfig = konfig;};

	virtual void entry() = 0;
	virtual void exit() = 0;

	//normales Verhalten
	virtual void LsRutAn() = 0;
	virtual void WsAussortieren() = 0;
	virtual void AuswerferEinfahren() = 0;

	//Fehlerverhalten
	virtual void quittiert() = 0;
	virtual void keinFehler() = 0;
	virtual void Fverschwunden() = 0;

	//E-Stop
	virtual void eStop() = 0;
};

#endif /* LOGIK_HAUPTZUSTAENDE_FBM1_LSANFANG_BASESTATESEPBISRUT1_H_ */
