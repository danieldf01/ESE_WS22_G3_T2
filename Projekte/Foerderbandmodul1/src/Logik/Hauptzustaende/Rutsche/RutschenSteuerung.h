/*
 * RutscheLeer.h
 *
 *  Created on: 15.12.2022
 *      Author: acy003
 */

#ifndef LOGIK_HAUPTZUSTAENDE_FBM1_RUTSCHE_RUTSCHENSTEUERUNG_H_
#define LOGIK_HAUPTZUSTAENDE_FBM1_RUTSCHE_RUTSCHENSTEUERUNG_H_
#include "../../Defines.h"
#include <iostream>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <thread>
#include <sys/dispatch.h>
#include <sys/dispatch.h>

class RutschenSteuerung{
public:

	int logikID;
	bool rutscheVoll1;
	bool rutscheFrei1;
	bool rutscheVoll2;
	bool rutscheFrei2;

	timer_t pruefTimerID1;
	timer_t pruefTimerID2;
	struct sigevent pruefTimerEvent;
	struct itimerspec pruefTimer;

	RutschenSteuerung();
	virtual ~RutschenSteuerung();
	void handlePulse(int,int);
	void initTimer(int);
	void destroyTimer(int);
};

#endif /* LOGIK_HAUPTZUSTAENDE_FBM1_RUTSCHE_RUTSCHENSTEUERUNG_H_ */
