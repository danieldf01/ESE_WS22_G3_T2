/*
 * Watchdog.cpp
 *
 *  Created on: 25.11.2022
 *      Author: Daniel Drefs Fernandes
 */

#include "Watchdog.h"

#include <iostream>

using namespace std;

Watchdog::Watchdog(int chid_s) {
	this->chid_slave = chid_s;
	coid_slave = ConnectAttach(0, 0, chid_slave, 0, 0);
}

Watchdog::~Watchdog() {
	// TODO Auto-generated destructor stub
}

void Watchdog::initTimer() {
	cout << "Watchdog::initTimer 2" << endl;
	//initialize EStoppTimer
	SIGEV_PULSE_INIT(&timerEvent, coid_slave, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_2, WATCHDOG_ESTOP);

	if ((timer_create(CLOCK_REALTIME, &timerEvent, &timerID)) == -1) {
		perror("[Watchdog] timer_create for EStopTimer failed");
	}

	timer.it_value.tv_sec = 0;
	timer.it_value.tv_nsec = 0;
	timer.it_interval.tv_sec = 0;
	timer.it_interval.tv_nsec = 700000000;
}

void Watchdog::notify() {
	timer_settime(timerID, 0, &timer, NULL);
}

