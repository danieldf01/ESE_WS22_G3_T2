/*
 * Motorsteuerung.h
 *
 *  Created on: 12.12.2022
 *      Author: acy003
 */
#include "Motor.h"
#ifndef LOGIK_HAUPTZUSTAENDE_FBM1_MOTORSTEUERUNG_MOTORSTEUERUNG_H_
#define LOGIK_HAUPTZUSTAENDE_FBM1_MOTORSTEUERUNG_MOTORSTEUERUNG_H_

class Motorsteuerung {
public:

	name_attach_t *attach;
	QnetHandler *qnetHandler=nullptr;
	Motor *stateM1=nullptr;
	Motor *stateM2=nullptr;
	Motorsteuerung(Zeitmanager *fbm1, Zeitmanager *fmb2);
	virtual ~Motorsteuerung();
	void receiveSignal();
};

#endif /* LOGIK_HAUPTZUSTAENDE_FBM1_MOTORSTEUERUNG_MOTORSTEUERUNG_H_ */
