/*
 * Rutsche.h
 *
 *  Created on: 15.12.2022
 *      Author: acy003
 */
#include "../../../dispatcher/QnetHandler.h"
#include "RutschenSteuerung.h"
#ifndef LOGIK_HAUPTZUSTAENDE_FBM1_RUTSCHE_RUTSCHE_H_
#define LOGIK_HAUPTZUSTAENDE_FBM1_RUTSCHE_RUTSCHE_H_

class Rutsche {
public:
	RutschenSteuerung *rutsche1;
	RutschenSteuerung *rutsche2;

	name_attach_t *attach;
	QnetHandler *qnetHandler=nullptr;
	Rutsche();
	virtual ~Rutsche();
	void receiveSignal();
};

#endif /* LOGIK_HAUPTZUSTAENDE_FBM1_RUTSCHE_RUTSCHE_H_ */
