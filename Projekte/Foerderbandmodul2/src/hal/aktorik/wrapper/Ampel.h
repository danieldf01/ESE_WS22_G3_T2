/*
 * Ampel.h
 *
 *  Created on: 24.10.2022
 *      Author: tobias
 */

#ifndef HAL_AKTORIK_WRAPPER_AMPEL_H_
#define HAL_AKTORIK_WRAPPER_AMPEL_H_

#include <unistd.h>
#include <thread>         // std::thread
#include "Farbe.h"
#include "Lampe.h"
#include "interfaces/ILampe.h"
#include <mutex>

// Sekunde und eine halbe Sekunde fuer das Blinken. Es wird usleep verwendet!
#define SEKUNDE 10*1000*100
#define HALBESEKUNDE 5000*100

class Ampel {
private:
	std::mutex mutexGruen;
	std::mutex mutexGelb;
	std::mutex mutexRot;
	ILampe *lampe = nullptr;
public:
	bool blinkenGelb=true;
	bool blinkenRot=true;
	bool blinkenGruen = true;
//	bool blinkenAktiv=true;
//	int langsam;
//	int schnell;
//	int zeitRot=0;
//	int zeitGelb=0;
//	int zeitGruen=0;

	Ampel();
	virtual ~Ampel();
	void lampeSchnellBlinken(Farbe farbe);
	void lampeLangsamBlinken(Farbe farbe);
	void lampeBlinkenAus(Farbe farbe) ;
	void blinken(Farbe farbe,int zeit);
};

class AmpelWrapper{
private:
	Ampel &ampel;
public:
	AmpelWrapper(Ampel &ampel);
	void operator()(Farbe farbe, int zeit);
};
#endif /* HAL_AKTORIK_WRAPPER_AMPEL_H_ */
