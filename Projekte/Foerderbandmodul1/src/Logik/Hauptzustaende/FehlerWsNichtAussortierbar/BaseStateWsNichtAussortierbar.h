/*
 * BaseStateWsNichtAussortierbar.h
 *
 *  Created on: 21.12.2022
 *      Author: Daniel Drefs Fernandes
 */

#ifndef LOGIK_HAUPTZUSTAENDE_FEHLERWSNICHTAUSSORTIERBAR_BASESTATEWSNICHTAUSSORTIERBAR_H_
#define LOGIK_HAUPTZUSTAENDE_FEHLERWSNICHTAUSSORTIERBAR_BASESTATEWSNICHTAUSSORTIERBAR_H_

#include <iostream>
#include "ActionsWsNichtAussortierbar.h"
#include "../FBM1/Rutsche/Rutsche.h"

class BaseStateWsNichtAussortierbar {
protected:
	ActionsWsNichtAussortierbar *actions;
	Rutsche *rutsche;
public:
	virtual ~BaseStateWsNichtAussortierbar() {};

	void setActions(ActionsWsNichtAussortierbar *actions){this->actions = actions;};
	void setRutsche(Rutsche *rutsche) {this->rutsche = rutsche;};

	virtual void entry() = 0;
	virtual void exit() = 0;

	virtual void WsNichtAussortierbar() = 0;
	virtual void LsRutscheAus1() = 0;
	virtual void LsRutscheAus2() = 0;

	virtual void eStop() = 0;
};

#endif /* LOGIK_HAUPTZUSTAENDE_FEHLERWSNICHTAUSSORTIERBAR_BASESTATEWSNICHTAUSSORTIERBAR_H_ */
