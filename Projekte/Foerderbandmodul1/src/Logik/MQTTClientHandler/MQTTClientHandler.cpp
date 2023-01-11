/*
 * MQTTClientHandler.cpp
 *
 *  Created on: 15.12.2022
 *      Author: Marek
 */

#include "MQTTClientHandler.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "MQTTClient.h"

MQTTClientHandler::MQTTClientHandler(std::string address, std::string clientID) {
	this->clientID=clientID;
	MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
	pubmsg = MQTTClient_message_initializer;


	if ((rc = MQTTClient_create(&client, address.c_str(), clientID.c_str(),
	MQTTCLIENT_PERSISTENCE_NONE, NULL)) != MQTTCLIENT_SUCCESS) {
		printf("Failed to create client, return code %d\n", rc);
		exit(EXIT_FAILURE);
	}

	conn_opts.keepAliveInterval = 20;
	conn_opts.cleansession = 1;
	if ((rc = MQTTClient_connect(client, &conn_opts)) != MQTTCLIENT_SUCCESS) {
		printf("Failed to connect, return code %d\n", rc);
		exit(EXIT_FAILURE);
	}
}

MQTTClientHandler::~MQTTClientHandler() {
	// TODO Auto-generated destructor stub
}

void MQTTClientHandler::senden(std::string topic,int ID, std::string WStype, double meanheight, double height){
	std::string payload="\"Team\": \"3.2\", \"id\": "+ std::to_string(ID) +", \"type\": \""+ WStype +"\", \"meanheight\": "+ std::to_string(meanheight) +", \"height\": "+ std::to_string(height);
	this->senden(topic, payload);
}
void MQTTClientHandler::senden(std::string topic, std::string payload) {

	char * cstr = new char [payload.length()+1];
	std::strcpy (cstr, payload.c_str());
	pubmsg.payload = cstr; //TODO
	pubmsg.payloadlen = (int) strlen(cstr);
	pubmsg.qos = QOS;
	pubmsg.retained = 0;

	if ((rc = MQTTClient_publishMessage(client, topic.c_str(), &pubmsg, &token))
			!= MQTTCLIENT_SUCCESS) {
		printf("Failed to publish message, return code %d\n", rc);
		exit(EXIT_FAILURE);
	}else{
		printf("[MQTT] SENDEN\n");
	}

	printf("Waiting for up to %d seconds for publication of %s\n"
			"on topic %s for client with ClientID: %s\n",
			(int) (TIMEOUT / 1000), cstr, topic.c_str(), clientID.c_str());
	rc = MQTTClient_waitForCompletion(client, token, TIMEOUT);
	printf("Message with delivery token %d delivered\n", token);


}

void MQTTClientHandler::destroy(){
	if ((rc = MQTTClient_disconnect(client, 10000)) != MQTTCLIENT_SUCCESS)
		printf("Failed to disconnect, return code %d\n", rc);
	MQTTClient_destroy(&client);
}


