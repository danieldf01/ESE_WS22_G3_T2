/*
 * SyncMessages.h
 *
 *  Created on: 02.11.2022
 *      Author: mario
 */

#ifndef SYNCMESSAGES_H_
#define SYNCMESSAGES_H_

//#include "QnetExamples.h"
//class MsgHandler;

#include "MsgHandler.h"

#define NO_OF_MSGS 5

//struct app_header_t;


class SyncMessages {
public:
	SyncMessages();
	virtual ~SyncMessages();
	int clientSync(void);
	int serverSync(void);
};

#endif /* SYNCMESSAGES_H_ */
