/*
 * QnetHandler.cpp
 *
 *  Created on: 15.11.2022
 *      Author: User
 */

#include "QnetHandler.h"

QnetHandler::QnetHandler() {
	// TODO Auto-generated constructor stub

}

QnetHandler::~QnetHandler() {
	// TODO Auto-generated destructor stub
}

int QnetHandler::createConnection(){
		int chanID = ChannelCreate(0); //Create channel to receive interrupt pulse messages.
		if (chanID < 0) {
			perror("Could not create a channel!\n");
			return EXIT_FAILURE;
		}
		return chanID;
}

int QnetHandler::openConnection(int *chanID){
	int conID = ConnectAttach(0, 0, *chanID, _NTO_SIDE_CHANNEL, 0); //Connect to channel.
	if (conID < 0) {
		perror("Could not connect to channel!");
		return EXIT_FAILURE;
	}
	return conID;
}

void QnetHandler::closeConnection(int *conID){
	int detach_status = ConnectDetach(*conID);
	if (detach_status != EOK) {
		perror("Detaching channel failed!");
		exit(EXIT_FAILURE);
	}
}

void QnetHandler::destroyConnection(int *chanID){
	int destroy_status = ChannelDestroy(*chanID);
	if (destroy_status != EOK) {
		perror("Destroying channel failed!");
		exit(EXIT_FAILURE);
	}
}
