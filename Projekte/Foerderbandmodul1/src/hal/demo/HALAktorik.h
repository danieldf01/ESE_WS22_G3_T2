/*
 * HALDemo.h
 *
 *  Created on: 17.10.2022
 *  Author: Tobias Thoelen
 */
#ifndef HAL_DEMO_HALAKTORIK_H_
#define HAL_DEMO_HALAKTORIK_H_


#include "../aktorik/wrapper/Ampel.h"
#include "../aktorik/wrapper/interfaces/IBedienpanel.h"
#include "../aktorik/wrapper/interfaces/ILampe.h"
#include "../aktorik/wrapper/interfaces/ISeperator.h"
#include "../aktorik/wrapper/interfaces/ILaufband.h"

#include "../aktorik/wrapper/Bedienpanel.h"
#include "../aktorik/wrapper/Lampe.h"
#include "../aktorik/wrapper/Laufband.h"
#include "../aktorik/wrapper/Seperator.h"

class HALAktorik {
public:
	ILampe *lampe = nullptr;
	ISeperator *sortierer = nullptr;
	IBedienpanel *bedienpanel = nullptr;
	ILaufband *laufband = nullptr;
	Ampel *ampel = nullptr;

	HALAktorik();
	virtual ~HALAktorik();
	void runDemo();
	void eStopp();
};

#endif /* HAL_DEMO_HALAKTORIK_H_ */
