/*
 * HALDemo.h
 *
 *  Created on: 17.10.2022
 *  Author: Tobias Thoelen
 */
#ifndef HAL_DEMO_DEMOHAL_H_
#define HAL_DEMO_DEMOHAL_H_


#include "../aktorik/wrapper/interfaces/IBedienpanel.h"
#include "../aktorik/wrapper/interfaces/ILampe.h"
#include "../aktorik/wrapper/interfaces/ISeperator.h"
#include "../aktorik/wrapper/interfaces/ILaufband.h"
#include "../aktorik/wrapper/interfaces/IAmpel.h"

#include "../aktorik/wrapper/Bedienpanel.h"
#include "../aktorik/wrapper/Lampe.h"
#include "../aktorik/wrapper/Laufband.h"
#include "../aktorik/wrapper/Seperator.h"
#include "../aktorik/wrapper/Ampel.h"

class HALAktorikDemo {
private:
	ILampe *lampe = nullptr;
	ISeperator *sortierer = nullptr;
	IBedienpanel *bedienpanel = nullptr;
	ILaufband *laufband = nullptr;
	IAmpel *ampel = nullptr;
public:
	HALAktorikDemo();
	virtual ~HALAktorikDemo();
	void runDemo();
};

#endif /* HAL_DEMO_DEMOHAL_H_ */
