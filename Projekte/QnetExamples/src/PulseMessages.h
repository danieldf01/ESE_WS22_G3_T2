/*
 * PulseMessages.h
 *
 *  Created on: 02.11.2022
 *      Author: mario
 */

#ifndef PULSEMESSAGES_H_
#define PULSEMESSAGES_H_

//#include "QnetExamples.h"
//class MsgHandler;

#include "MsgHandler.h"

#define NO_MSGS 4

class PulseMessages {
public:
	PulseMessages();
	virtual ~PulseMessages();
	int serverPulse(int server);
	int clientPulse(int server);
};

#endif /* PULSEMESSAGES_H_ */
