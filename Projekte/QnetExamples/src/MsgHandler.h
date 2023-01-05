/*
 * MsgHandler.h
 *
 *  Created on: 02.11.2022
 *      Author: mario
 */

#ifndef MSGHANDLER_H_
#define MSGHANDLER_H_

//includes
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/dispatch.h>
#include <iostream>

#define ATTACH_POINT "server"
#define ATTACH_POINT_2 "server_2"

/* First header used by GNS and application */
//typedef struct _pulse header_t;
/* header types
 * 0 .. _IO_BASE -1 : Pulse msg
 * _IO_BASE = 0x100 .. _IO_MAX = 0x1FF : Sync. msg of the System
 * _IO_MAX + 1 .. : Sync. msg of application
 */

// Messages types of application
#define STR_MSG (_IO_MAX + 1)
#define DATA_MSG (_IO_MAX + 2)

/* Second header: used by application - if required */
typedef struct {
	int size; // size of data block
	int count; // some counter used by the application
	// further data fields required by application
} app_header_t;

class MsgHandler {
public:
	MsgHandler();
	virtual ~MsgHandler();
	void handle_pulse(_pulse pulse, int rcvid, int server);
	void handle_ONX_IO_msg(_pulse hdr, int rcvid);
	void handle_app_msg(_pulse hdr, int rcvid);
};

#endif /* MSGHANDLER_H_ */
