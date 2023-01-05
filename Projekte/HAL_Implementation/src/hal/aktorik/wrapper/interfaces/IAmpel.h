/*
 * IAmpel.h
 *
 *  Created on: 24.10.2022
 *      Author: tobias
 */

#ifndef HAL_AKTORIK_WRAPPER_INTERFACES_IAMPEL_H_
#define HAL_AKTORIK_WRAPPER_INTERFACES_IAMPEL_H_

enum Farbe {Gruen, Gelb, Rot};


class IAmpel {
public:
	virtual void lampeSchnellBlinken(Farbe farbe) = 0;
	virtual void lampeLangsamBlinken(Farbe farbe) = 0;
	virtual void lampeBlinkenAus() = 0;
	virtual void lampeAn(Farbe farbe) = 0;
	virtual void lampeAus(Farbe farbe) = 0;
};


#endif /* HAL_AKTORIK_WRAPPER_INTERFACES_IAMPEL_H_ */
