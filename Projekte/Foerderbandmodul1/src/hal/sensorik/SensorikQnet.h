/*
 * QnetHandler.h
 *
 *  Created on: 15.11.2022
 *      Author: User
 */

#ifndef SENSORIK_QNETHANDLER_H_
#define SENSORIK_QNETHANDLER_H_

#include <stdio.h>
#include <errno.h>
#include <sys/neutrino.h>
#include <sys/procmgr.h>
#include <iostream>
#include <thread>
#include <chrono>
#include <sys/mman.h>
#include <hw/inout.h>

class SensorikQnet {
public:
	SensorikQnet();
	virtual ~SensorikQnet();

	int createConnection();
	int openConnection(int chanID);
	void closeConnection(int conID);
	void destroyConnection(int chanID);
};

#endif /* SENSORIK_QNETHANDLER_H_ */
