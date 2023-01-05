/*
 * Ampel.h
 *
 *  Created on: 24.10.2022
 *      Author: tobias
 */

#ifndef HAL_AKTORIK_WRAPPER_AMPEL_H_
#define HAL_AKTORIK_WRAPPER_AMPEL_H_

#include "interfaces/IAmpel.h"
#include "interfaces/ILampe.h"
#include "Lampe.h"

// Sekunde und eine halbe Sekunde fuer das Blinken. Es wird usleep verwendet!
#define SEKUNDE 100000
#define HALBESEKUNDE 50000

class Ampel : public IAmpel{
private:
	ILampe *lampe = nullptr;
public:
	Ampel();
	virtual ~Ampel();
	void lampeSchnellBlinken(Farbe farbe) override;
	void lampeLangsamBlinken(Farbe farbe) override;
	void lampeAn(Farbe farbe) override;
	void lampeAus(Farbe farbe) override;
};

#endif /* HAL_AKTORIK_WRAPPER_AMPEL_H_ */
