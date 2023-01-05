/*
 * QnetHandler.h
 *
 *  Created on: 24.11.2022
 *      Author: acy003
 */

#ifndef DISPATCHER_QNETHANDLER_H_
#define DISPATCHER_QNETHANDLER_H_
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/dispatch.h>
#include <iostream>
#include <sys/iofunc.h>

class QnetHandler {
public:
	QnetHandler();
	virtual ~QnetHandler();
	name_attach_t* openServer(const char*);
	int connectServer(const char*);
	int handle_pulse(_pulse, int, const char*);
};

#endif /* DISPATCHER_QNETHANDLER_H_ */
