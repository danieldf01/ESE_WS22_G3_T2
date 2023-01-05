/*
 * BaseStateSepBisRut2.h
 *
 *  Created on: 11.12.2022
 *      Author: Daniel
 */

#ifndef LOGIK_HAUPTZUSTAENDE_FBM2_SEPBISRUT_BASESTATESEPBISRUT2_H_
#define LOGIK_HAUPTZUSTAENDE_FBM2_SEPBISRUT_BASESTATESEPBISRUT2_H_

#include "ActionsSepBisRut2.h"
#include "../../../konfigurationsdateiManager/KonfigurationsdateiManager.h"

class BaseStateSepBisRut2 {
protected:
	ActionsSepBisRut2 *actions;
	WsListen *wsListen;
	KonfigurationsdateiManager *konfig;
public:
	virtual ~BaseStateSepBisRut2() {};

	void setActions(ActionsSepBisRut2 *actions){this->actions = actions;};
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

#endif /* LOGIK_HAUPTZUSTAENDE_FBM2_LSANFANG_BASESTATESEPBISRUT2_H_ */
