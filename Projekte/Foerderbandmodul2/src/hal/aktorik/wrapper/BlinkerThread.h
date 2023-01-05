/*
 * BlinkerThread.h
 *
 *  Created on: 13.11.2022
 *      Author: User
 */

#ifndef HAL_SENSORIK_BLINKERTHREAD_H_
#define HAL_SENSORIK_BLINKERTHREAD_H_

#include "interfaces/IAmpel.h"
#include "Lampe.h"
#include "interfaces/ILampe.h"
#include <iostream>

// Sekunde und eine halbe Sekunde fuer das Blinken. Es wird usleep verwendet!
#define SEKUNDE 10*1000*100
#define HALBESEKUNDE 5000*100


class BlinkerThread {
private:
	ILampe *lampe = nullptr;
public:
	bool blinkenAktiv = true;
	int zeit;
	Farbe farbe;

	BlinkerThread();
	virtual ~BlinkerThread();
	void blinken();
};

#endif /* HAL_SENSORIK_BLINKERTHREAD_H_ */
