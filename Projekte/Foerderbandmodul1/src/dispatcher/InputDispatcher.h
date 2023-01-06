/*
 * InputDispatcher.h
 *
 *  Created on: Nov 13, 2022
 *      Author: bardia
 */

#ifndef INPUTDISPATCHER_H_
#define INPUTDISPATCHER_H_

#include <string.h>
#include "../hal/demo/HALAktorik.h"
#include "QnetHandler.h"
#include "../Logik/Defines.h"

class InputDispatcher {

private:
	HALAktorik *hal=nullptr;
	name_attach_t *attach;
	QnetHandler qnetHandler;
	bool estop=false;

public:
	InputDispatcher(HALAktorik &hal);
	virtual ~InputDispatcher();
	void receiveSignal();
	void test();
	void test2();
	void fehlerQuittiert();
};

#endif /* INPUTDISPATCHER_H_ */
