/*
 * SyncMessages.cpp
 *
 *  Created on: 02.11.2022
 *      Author: mario
 */

#include "SyncMessages.h"

using namespace std;

SyncMessages::SyncMessages() {
	// TODO Auto-generated constructor stub

}

SyncMessages::~SyncMessages() {
	// TODO Auto-generated destructor stub
}

int SyncMessages::clientSync() { // Client side of the code
	int server_coid;
	char payload0[] = "Dies ist ein sehr grosser Datenbereich ...";
	char payload1[] = "Eine andere Payload ...";
	_pulse header;
	app_header_t app_header;
	iov_t iov[3]; // multi part msg
	char r_msg[512]; // buffer for the answer

// Use GNS for setting up the connection to the server
	if ((server_coid = name_open(ATTACH_POINT, NAME_FLAG_ATTACH_GLOBAL))
			== -1) {
		perror("Client: name_open failed");
		return EXIT_FAILURE;
	}

// Do whatever work you wanted with server connection
	for (int no = 0; no < NO_OF_MSGS; no++) {
		printf("Client sending msg %d \n", no);
// Construct payload with dummy values
		char * payload = ((no % 2) == 0) ? payload0 : payload1;
		int payload_size = strlen(payload) + 1; // +1 due to string end (\0)
// Compose the msg using an IOV
		header.type = STR_MSG; // define msg type
		header.subtype = 0x00;
		app_header.size = payload_size; // fill application header
		app_header.count = no;
		SETIOV(iov + 0, &header, sizeof(header));
		SETIOV(iov + 1, &app_header, sizeof(app_header));
		SETIOV(iov + 2, payload, payload_size);
// send msg
		if (-1 == MsgSendvs(server_coid, iov, 3, r_msg, sizeof(r_msg))) {
			perror("Client: MsgSend failed");
			exit(EXIT_FAILURE);
		}
// Answer form server should be structured, too.
		printf("Client: Answer from server: %s \n", r_msg);
	}
	name_close(server_coid); // close connection
	return EXIT_SUCCESS;
}

int SyncMessages::serverSync() { // Server side of the code
	MsgHandler *msgHandler = new MsgHandler();
	name_attach_t *attach;
// Create a unique global name known within the network
	if ((attach = name_attach(NULL, ATTACH_POINT, NAME_FLAG_ATTACH_GLOBAL))
			== NULL) {
		perror("Server: name_attach failed");
		return EXIT_FAILURE;
	}
	while (1) {
// Waiting for a message and read first header
		_pulse header;
		int rcvid = MsgReceive(attach->chid, &header, sizeof(_pulse), NULL);
		if (rcvid == -1) { // Error occurred
			perror("Server: MsgReceived failed");
			break;
		}
		if (rcvid == 0) { // Pulse was received
			msgHandler->handle_pulse(header, rcvid, 0);		// letzter Parameter noch falsch, muss eine server-Var. sein
			continue;
		}
		// some sync msg was received
		if ((_IO_BASE <= header.type) && (header.type <= _IO_MAX)) {
			// Some QNX IO msg generated by gns was received
			msgHandler->handle_ONX_IO_msg(header, rcvid);
			continue;
		}
		// A sync msg (presumable ours) was received; handle it
		msgHandler->handle_app_msg(header, rcvid);
	}
	// Server stopped; remove the name from the space
	name_detach(attach, 0);
	return EXIT_SUCCESS;
}
