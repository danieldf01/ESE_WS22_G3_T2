/*
 * MQTTClientHandler.h
 *
 *  Created on: 15.12.2022
 *      Author: Marek
 */

#ifndef SRC_MQTTCLIENTHANDLER_H_
#define SRC_MQTTCLIENTHANDLER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "MQTTClient.h"

//#define ADDRESS     "tcp://192.168.101.201:1883"
//#define CLIENTID    "ExampleClientPub"
//#define TOPIC       "werkstueck"
//#define PAYLOAD     "\"Team\": \"3.2\", \"id\": 1, \"type\": \"HOCH\", \"meanheight\": 20, \"height\": 25"
#define QOS         1
#define TIMEOUT     1000L

class MQTTClientHandler {
public:
	MQTTClientHandler(std::string address, std::string clientID);
	virtual ~MQTTClientHandler();
	void senden(std::string topic, std::string payload);
	void senden(std::string topic,int ID, std::string WStype, double meanheight, double height);
	void destroy();
private:
	MQTTClient client;
	MQTTClient_message pubmsg;
	MQTTClient_deliveryToken token;
	std::string clientID;
	int rc;
};

#endif /* SRC_MQTTCLIENTHANDLER_H_ */
