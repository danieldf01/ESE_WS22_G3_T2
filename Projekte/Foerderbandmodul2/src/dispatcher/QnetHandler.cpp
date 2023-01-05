/*
 * QnetHandler.cpp
 *
 *  Created on: 24.11.2022
 *      Author: acy003
 */

#include "QnetHandler.h"

using namespace std;

QnetHandler::QnetHandler() {
	// TODO Auto-generated constructor stub

}

QnetHandler::~QnetHandler() {
	// TODO Auto-generated destructor stub
}

name_attach_t* QnetHandler::openServer(const char* server) {
	name_attach_t *attach;

	if ((attach = name_attach(NULL, server, NAME_FLAG_ATTACH_GLOBAL)) == NULL) {
		perror("name_attach failed");
	}
	else{

	cout << "[" << server << "] successfully attached name" << endl;
	return attach;
	}
}
int QnetHandler::connectServer(const char* server) {
	int server_coid;
	if ((server_coid = name_open(server, NAME_FLAG_ATTACH_GLOBAL)) == -1) {
		perror("[Client] name_open failed");
		return EXIT_FAILURE;
	}
	cout << "[Client] opened name and connected to channel: " << server << "\n";
	return server_coid;
}

int QnetHandler::handle_pulse(_pulse pulse, int rcvid, const char* server) {
	switch (pulse.code) {
	case _PULSE_CODE_DISCONNECT:
		cout << "[" << server << "] received _PULSE_CODE_DISCONNECT" << endl;
		ConnectDetach(pulse.scoid);
		break;
	case _PULSE_CODE_UNBLOCK:
		cout << "[" << server << "] received _PULSE_CODE_UNBLOCK" << endl;
		break;
	default:
		printf("[%s] received some pulse message: %d\n", server, pulse.value);
	}
}
