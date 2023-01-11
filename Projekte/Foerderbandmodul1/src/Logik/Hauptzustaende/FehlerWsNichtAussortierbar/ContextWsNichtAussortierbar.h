/*
 * ContextWsNichtAussortierbar.h
 *
 *  Created on: 21.12.2022
 *      Author: Daniel Drefs Fernandes
 */

#ifndef LOGIK_HAUPTZUSTAENDE_FEHLERWSNICHTAUSSORTIERBAR_CONTEXTWSNICHTAUSSORTIERBAR_H_
#define LOGIK_HAUPTZUSTAENDE_FEHLERWSNICHTAUSSORTIERBAR_CONTEXTWSNICHTAUSSORTIERBAR_H_

#include "../../../dispatcher/QnetHandler.h"
#include "../../Defines.h"
#include "ActionsWsNichtAussortierbar.h"
#include "BaseStateWsNichtAussortierbar.h"
#include "WartenWsNichtAussortierbar.h"

class ContextWsNichtAussortierbar {
private:
	BaseStateWsNichtAussortierbar *state;
	ActionsWsNichtAussortierbar *actions;
	QnetHandler *qnetHandler;
	name_attach_t *attach;
	Rutsche *rutsche;
public:

	int chID;
	ContextWsNichtAussortierbar(ActionsWsNichtAussortierbar *shared_action, Rutsche *r);
	virtual ~ContextWsNichtAussortierbar();

	void receiveSignal();

	void entry();
	void exit();

	void WsNichtAussortierbar();
	void LsRutscheAus1();
	void LsRutscheAus2();

	void eStop();
};

#endif /* LOGIK_HAUPTZUSTAENDE_FEHLERWSNICHTAUSSORTIERBAR_CONTEXTWSNICHTAUSSORTIERBAR_H_ */
