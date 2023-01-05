#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/dispatch.h>
#include <gtest/gtest.h>
#include <iostream>

#define ATTACH_POINT "server"

using namespace std;

class Client {

	int server_coid;

public:

	int clientOpen() { // Client side of the code
// Use GNS for setting up the connection to the server
		if ((server_coid = name_open(ATTACH_POINT, NAME_FLAG_ATTACH_GLOBAL))
				== -1) {
			perror("Client: name_open failed");
			return EXIT_FAILURE;
		}
		cout << "Client: opened name and connected to channel: " << ATTACH_POINT
				<< "\n";
		return EXIT_SUCCESS;
	}

	int sendMsg() {
// send msg
		if (MsgSendPulse(server_coid, SIGEV_PULSE_PRIO_INHERIT,
		_PULSE_CODE_MINAVAIL + 10, 808) != 0) {
			perror("Client: sendPulse failed");
			return EXIT_FAILURE;
		}
		return EXIT_SUCCESS;
	}

	int closeName() {
		if (name_close(server_coid) != 0) { // close connection
			perror("Client: name_close failed");
		}
		return EXIT_SUCCESS;
	}
};
