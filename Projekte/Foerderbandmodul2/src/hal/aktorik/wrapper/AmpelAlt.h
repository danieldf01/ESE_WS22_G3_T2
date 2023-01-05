/*
 * Ampel.h
 *
 *  Created on: 24.10.2022
 *      Author: tobias
 */

#ifndef HAL_AKTORIK_WRAPPER_AMPELALT_H_
#define HAL_AKTORIK_WRAPPER_AMPELALT_H_

#include <unistd.h>
#include <thread>         // std::thread
#include "interfaces/IAmpel.h"
#include "BlinkerThread.h"



class Ampel {
private:
	ILampe *lampe = nullptr;
	BlinkerThread blinker;
	//std::thread blinkerThread;
public:
	Ampel();
	virtual ~Ampel();
	void lampeSchnellBlinken(Farbe farbe);
	void lampeLangsamBlinken(Farbe farbe);
	void lampeBlinkenAus() ;
};

class AmpelWrapper{
private:
	Ampel &ampel;
public:
	AmpelWrapper(Ampel &ampel);
	void operator()(Farbe farbe);
};
#endif /* HAL_AKTORIK_WRAPPER_AMPELALT_H_ */
