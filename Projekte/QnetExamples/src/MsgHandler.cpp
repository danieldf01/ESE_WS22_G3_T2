/*
 * MsgHandler.cpp
 *
 *  Created on: 02.11.2022
 *      Author: mario
 */

#include "MsgHandler.h"

MsgHandler::MsgHandler() {
	// TODO Auto-generated constructor stub

}

MsgHandler::~MsgHandler() {
	// TODO Auto-generated destructor stub
}

void MsgHandler::handle_pulse(_pulse pulse, int rcvid, int server) {
	const char* attach_point = "";
	if (server % 2 == 0) {
		attach_point = ATTACH_POINT;
	} else {
		attach_point = ATTACH_POINT_2;
	}
	switch (pulse.code) {
	case _PULSE_CODE_DISCONNECT:
		printf("Server received _PULSE_CODE_DISCONNECT\n");
		/* A client disconnected all its connections (called
		 * name_close() for each name_open() of our name) or
		 * terminated. */
		ConnectDetach(pulse.scoid);
		break;
	case _PULSE_CODE_UNBLOCK:
		printf("Server received _PULSE_CODE_UNBLOCK\n");
		/* REPLY blocked client wants to unblock (was hit by
		 * a signal or timed out). It's up to you if you
		 * reply now or later. */
		break;
	default:
		/* A pulse sent by one of your processes or a
		 * _PULSE_CODE_COIDDEATH or _PULSE_CODE_THREADDEATH
		 * from the kernel? */
		printf("Server: received some pulse msg on %s: %d\n", attach_point, pulse.value);
		break;
	}
}

void MsgHandler::handle_ONX_IO_msg(_pulse hdr, int rcvid) {
	if (hdr.type == _IO_CONNECT) {
// QNX IO msg _IO_CONNECT was received; answer with EOK
		printf("Server received _IO_CONNECT (sync. msg) \n");
		MsgReply(rcvid, EOK, NULL, 0);
		return;
	}
// Some other QNX IO message was received; reject it
	printf("Server received unexpected (sync.) msg type = 0x%04X\n", hdr.type);
	MsgError(rcvid, ENOSYS);
}

void MsgHandler::handle_app_msg(_pulse hdr, int rcvid) {
	const char *ret_msg = "Got the message";
	if (DATA_MSG == hdr.type) {
		printf("Server: DATA_MSG not supported.\n");
		MsgError(rcvid, EPERM);
	} else if (STR_MSG == hdr.type) {
		printf("Server: STR_MSG received.\n");
// read app header
		app_header_t app_header;
		MsgRead(rcvid, &app_header, sizeof(app_header), sizeof(_pulse));
// ToDo Check return value of MsgRead, in particular number of read bytes
// read payload
		char * buf = (char *) malloc(app_header.size); // ToDo check return value of malloc
		MsgRead(rcvid, buf, app_header.size,
				sizeof(_pulse) + sizeof(app_header_t));
// ToDo Check return value of MsgRead, in particular number of read bytes
		printf("Server: got STR_MSG (count = %d): %s \n", app_header.count,
				buf);
		MsgReply(rcvid, EOK, ret_msg, strlen(ret_msg) + 1); // send reply
		free(buf);
	} else { // Wrong msg type
		printf("Server: Wrong message type 0x%04X\n", hdr.type);
		MsgError(rcvid, EPERM);
	}
}
