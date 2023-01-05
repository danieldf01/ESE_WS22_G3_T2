/*
 * BaseStateLSAnfang.h
 *
 *  Created on: 11.12.2022
 *      Author: Daniel
 */

#ifndef LOGIK_HAUPTZUSTAENDE_FBM1_LSANFANG_BASESTATELSA1_H_
#define LOGIK_HAUPTZUSTAENDE_FBM1_LSANFANG_BASESTATELSA1_H_

#include <iostream>
#include "ActionsLSA1.h"

class BaseStateLSA1 {
protected:
	ActionsLSA1 *actions;
public:
	virtual ~BaseStateLSA1(){};

	void setActions(ActionsLSA1 *actions){this->actions = actions;};

	virtual void entry() = 0;
	virtual void exit() = 0;

	//normales Verhalten
	virtual void LSan() = 0;
	virtual void LSaus() = 0;
	virtual void timerAbstand() = 0;

	//Fehlerverhalten
	virtual void WSstecktFest() = 0;
	virtual void quittiert() = 0;
	virtual void keinFehler() = 0;
	//E-Stop
	virtual void eStop() = 0;

};

#endif /* LOGIK_HAUPTZUSTAENDE_FBM1_LSANFANG_BASESTATELSA1_H_ */
