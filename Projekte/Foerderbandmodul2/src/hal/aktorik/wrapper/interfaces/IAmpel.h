/*
 * IAmpel.h
 *
 *  Created on: 24.10.2022
 *      Author: tobias
 */

#ifndef HAL_AKTORIK_WRAPPER_INTERFACES_IAMPEL_H_
#define HAL_AKTORIK_WRAPPER_INTERFACES_IAMPEL_H_

#include "../Farbe.h"

class IAmpel {
public:
	virtual void lampeBlinkenAus(Farbe) = 0;
	virtual void blinken(Farbe, int) = 0;
};


#endif /* HAL_AKTORIK_WRAPPER_INTERFACES_IAMPEL_H_ */
