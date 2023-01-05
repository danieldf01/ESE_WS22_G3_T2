/*
 * Watchdog.h
 *
 *  Created on: 13.11.2022
 *      Author: Daniel Drefs Fernandes
 */

#ifndef WATCHDOG_H_
#define WATCHDOG_H_

class Watchdog {
public:
	Watchdog();
	virtual ~Watchdog();
	void notify();
	void sendSignal();
	void eStopp();
};

#endif /* WATCHDOG_H_ */
