/*
 * ActionsWsNichtAussortierbar.h
 *
 *  Created on: 21.12.2022
 *      Author: Daniel Drefs Fernandes
 */

#ifndef LOGIK_HAUPTZUSTAENDE_FEHLERWSNICHTAUSSORTIERBAR_ACTIONSWSNICHTAUSSORTIERBAR_H_
#define LOGIK_HAUPTZUSTAENDE_FEHLERWSNICHTAUSSORTIERBAR_ACTIONSWSNICHTAUSSORTIERBAR_H_

#include <iostream>
#include <sys/dispatch.h>
#include "../../Defines.h"

class ActionsWsNichtAussortierbar {
protected:
	int logikID;
public:
	virtual ~ActionsWsNichtAussortierbar();

	void setupConnection();
	void fehlerHoch();
	void fehlerRunter();
};

#endif /* LOGIK_HAUPTZUSTAENDE_FEHLERWSNICHTAUSSORTIERBAR_ACTIONSWSNICHTAUSSORTIERBAR_H_ */
