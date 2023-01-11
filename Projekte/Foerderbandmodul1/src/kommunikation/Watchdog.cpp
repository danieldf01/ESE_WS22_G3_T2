/*
 * Watchdog.cpp
 *
 *  Created on: 25.11.2022
 *      Author: Daniel Drefs Fernandes
 */

#include "Watchdog.h"

#include <iostream>

using namespace std;

Watchdog::Watchdog(int iD_master) {
	//initialize connection
	qnetHandler = new QnetHandler();
	chid_master = iD_master;
	coid_master = ConnectAttach(0,0,chid_master,0,0);
}

Watchdog::~Watchdog() {

}

void Watchdog::initTimer() {
	cout << "Watchdog::initTimer 1" << endl;
	//initialize EStoppTimer
	SIGEV_PULSE_INIT(&timerEvent, coid_master, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, WATCHDOG_ESTOP); // TODO Signal umbennen

	if ((timer_create(CLOCK_REALTIME, &timerEvent, &timerID)) != 0) {
		perror("[Watchdog] timer_create failed");
	}

	timer.it_value.tv_sec = 0;
	timer.it_value.tv_nsec = 0;
	timer.it_interval.tv_sec = 0;
	timer.it_interval.tv_nsec = 700000000;
}

void Watchdog::notify() {
	//cout << "notify 1" << endl;

	timer_settime(timerID, 0, &timer, NULL);
}

