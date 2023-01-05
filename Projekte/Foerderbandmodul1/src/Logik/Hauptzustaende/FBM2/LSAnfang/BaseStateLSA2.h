/*
 * BaseStateLSA2.h
 *
 *  Created on: 22.12.2022
 *      Author: tobias
 */

#ifndef LOGIK_HAUPTZUSTAENDE_FBM2_LSANFANG_BASESTATELSA2_H_
#define LOGIK_HAUPTZUSTAENDE_FBM2_LSANFANG_BASESTATELSA2_H_

#include <iostream>
#include "ActionsLSA2.h"

class BaseStateLSA2 {
protected:
	ActionsLSA2 *actions;
public:
	virtual ~BaseStateLSA2(){};

	void setActions(ActionsLSA2 *actions){this->actions = actions;};

	virtual void entry() = 0;
	virtual void exit() = 0;

	//normales Verhalten
	virtual void lsAnfangAn() = 0;
	virtual void fbm1Bereit() = 0;
	virtual void fbm2Bereit() = 0;
	virtual void fbm1WsLosgeschickt() = 0;
	virtual void fbm1WsUebergeben() = 0;
	virtual void lsAnfangAus() = 0;

	//Fehlerverhalten
	virtual void fehlerVerschwunden() = 0;
	virtual void quittiert() = 0;
	virtual void keinFehler() = 0;
	//E-Stop
	virtual void eStop() = 0;
};

#endif /* LOGIK_HAUPTZUSTAENDE_FBM2_LSANFANG_BASESTATELSA2_H_ */
