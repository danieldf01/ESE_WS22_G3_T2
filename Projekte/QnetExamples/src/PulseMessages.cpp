/*
 * PulseMessages.cpp
 *
 *  Created on: 02.11.2022
 *      Author: mario
 */

#include "PulseMessages.h"

using namespace std;

PulseMessages::PulseMessages() {
	// TODO Auto-generated constructor stub

}

PulseMessages::~PulseMessages() {
	// TODO Auto-generated destructor stub
}

/*
 * SERVER SIDE OF THE CODE
 */

int PulseMessages::serverPulse(int server) {
	MsgHandler *msgHandler = new MsgHandler();
	name_attach_t *attach;
	const char* attach_point = "";
	if (server % 2 == 0) {
		attach_point = ATTACH_POINT;
	} else {
		attach_point = ATTACH_POINT_2;
	}
// Create a unique global name known within the network

	if ((attach = name_attach(NULL, attach_point, NAME_FLAG_ATTACH_GLOBAL))
			== NULL) {
		perror("Server: name_attach failed");
		return EXIT_FAILURE;
	}
	cout << "Server: channel successfully opened with name " << attach_point
			<< "\n";

	while (1) {
		int rcvid;
		_pulse pulse;
		rcvid = MsgReceive(attach->chid, &pulse, sizeof(_pulse), NULL);

		if (rcvid == -1) { // Error occurred
			perror("Server: MsgReceived failed");
			break;
		}
		if (rcvid == 0) { // Pulse was received
			msgHandler->handle_pulse(pulse, rcvid, server);
			continue;
		}
		// some sync msg was received
		if ((_IO_BASE <= pulse.type) && (pulse.type <= _IO_MAX)) {
			// Some QNX IO msg generated by gns was received
			msgHandler->handle_ONX_IO_msg(pulse, rcvid);
			continue;
		}
		// A sync msg (presumable ours) was received; handle it
		cout << "Server: received unexpected sync message" << endl;
	}
	name_detach(attach, 0);
	return EXIT_SUCCESS;
}

/*
 * CLIENT SIDE OF THE CODE
 */

int PulseMessages::clientPulse(int server) {
	int server_coid;
	const char* attach_point = "";
// Use GNS for setting up the connection to the server
	if (server % 2 == 0) {
		attach_point = ATTACH_POINT;
	} else {
		attach_point = ATTACH_POINT_2;
	}
	if ((server_coid = name_open(attach_point, NAME_FLAG_ATTACH_GLOBAL))
			== -1) {
		perror("Client: name_open failed");
		return EXIT_FAILURE;
	}
	cout << "Client: opened name and connected to channel: " << attach_point
			<< "\n";

// send msg
	for (int i = 0; i < NO_MSGS; i++) {
		if (i % 2 == 0) {
			if (MsgSendPulse(server_coid, SIGEV_PULSE_PRIO_INHERIT,
					_PULSE_CODE_MINAVAIL + 10, 808) != 0) {
				perror("Client: sendPulse failed");
				return EXIT_FAILURE;
			}
		} else {
			if (MsgSendPulse(server_coid, SIGEV_PULSE_PRIO_INHERIT,
					_PULSE_CODE_MINAVAIL + 10, 404) != 0) {
				perror("Client: sendPulse failed");
				return EXIT_FAILURE;
			}
		}
		sleep(5);
	}

	if (name_close(server_coid) != 0) { // close connection
		perror("Client: name_close failed");
	}
	cout << "Client: disconnected from channel: " << attach_point << "\n";
	return EXIT_SUCCESS;
}
