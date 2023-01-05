/*
 * QnetHandler.cpp
 *
 * Stellt Methoden bereit wie erstellen und loeschen von Kanaelen
 * und Verbindungsauf- und abbau.
 *
 *  Created on: 15.11.2022
 *      Author: Tobias Thoelen
 */

#include "SensorikQnet.h"

SensorikQnet::SensorikQnet() {
	// TODO Auto-generated constructor stub

}

SensorikQnet::~SensorikQnet() {
	// TODO Auto-generated destructor stub
}

/**
 * Erstellt einen Qnet Kanal
 */
int SensorikQnet::createConnection(){
		int chanID = ChannelCreate(0); //Create channel to receive interrupt pulse messages.
		if (chanID < 0) {
			perror("Could not create a channel!\n");
			return EXIT_FAILURE;
		}
		return chanID;
}

/**
 * Verbindung
 */
int SensorikQnet::openConnection(int chanID){
	int conID = ConnectAttach(0, 0, chanID, _NTO_SIDE_CHANNEL, 0); //Connect to channel.
	if (conID < 0) {
		perror("Could not connect to channel!");
		return EXIT_FAILURE;
	}
	return conID;
}

void SensorikQnet::closeConnection(int conID){
	int detach_status = ConnectDetach(conID);
	if (detach_status != EOK) {
		perror("Detaching channel failed!");
		exit(EXIT_FAILURE);
	}
}

void SensorikQnet::destroyConnection(int chanID){
	int destroy_status = ChannelDestroy(chanID);
	if (destroy_status != EOK) {
		perror("Destroying channel failed!");
		exit(EXIT_FAILURE);
	}
}
