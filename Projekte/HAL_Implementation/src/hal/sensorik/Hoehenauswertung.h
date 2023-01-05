/*
 * Hoehenauswertung.h
 *
 *  Created on: 01.11.2022
 *      Author: User
 */

#ifndef HAL_SENSORIK_HOEHENAUSWERTUNG_H_
#define HAL_SENSORIK_HOEHENAUSWERTUNG_H_

#include <sys/neutrino.h>
#include <cstdio>
#include <stdint.h>
#include <sys/mman.h>

#include "Sensorik.h"

#define HOEHE_HOEHES_WS 2380
#define HOEHE_FLACHES_WS 2600
#define HOEHE_LOCH 3300
#define HOEHE_NICHTS 3630

enum WSOberflaeche {FLACH, HOCH_OHNE_BOHRUNG, HOCH_MIT_BOHRUNG};

class Hoehenauswertung {
private:
	int channelID;
	int clientID;
	int dispConID;
	uintptr_t gpio_bank_1;
public:
	Hoehenauswertung(int ID, int dispID);
	virtual ~Hoehenauswertung();
	int getChannelID();
	int createChannel();
	void evaluateSomething();
	void sendTestPulses(int pulse);
	void sendTestPulses(int pulse, uint32_t);
};

#endif /* HAL_SENSORIK_HOEHENAUSWERTUNG_H_ */
