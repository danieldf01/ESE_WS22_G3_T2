/*
 * Werkstueck.h
 *
 *  Created on: Dec 11, 2022
 *      Author: bardi
 */

#ifndef LOGIK_WERKSTUECK_H_
#define LOGIK_WERKSTUECK_H_

#include "WsTyp.h"

class Werkstueck {
private:
	//Felder
	unsigned int timestamp;
	int iD;
	WsTyp wsTyp;
	double mittlereHoehe;
	double hoehenmesswert;

public:
	Werkstueck(int, unsigned int);
	virtual ~Werkstueck();

	int getiD();
	unsigned int getTimestamp();
	void setTimestamp(unsigned int);
	WsTyp getWsTyp();
	void setWsTyp(WsTyp);
	double getMittlereHoehe();
	void setMittlereHoehe(double);
	double getHoehenmesswert();
	void setHoehenmesswert(double);
};

#endif /* LOGIK_WERKSTUECK_H_ */
