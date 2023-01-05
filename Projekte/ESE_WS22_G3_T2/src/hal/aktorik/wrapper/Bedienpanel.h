/*
 * Bedienpanel.h
 *
 *  Created on: 17.10.2022
 *  Author: Tobias Thoelen
 */

#ifndef HAL_AKTORIK_WRAPPER_BEDIENPANEL_H_
#define HAL_AKTORIK_WRAPPER_BEDIENPANEL_H_

#include "../Aktorik.h"
#include "interfaces/IBedienpanel.h"


#define LED_START 0x00000004
#define LED_RESET 0x00000008
#define SL_Q1 0x00000010
#define SL_Q2 0x00000020

class Bedienpanel : public IBedienpanel{
private:
	//variables
	uintptr_t gpio_bank_2;
public:
	Bedienpanel();
	virtual ~Bedienpanel();
	void ledStartAn() override;
	void ledStartAus() override;
	void ledResetAn() override;
	void ledResetAus() override;
	void signalleuchteQ1An() override;
	void signalleuchteQ1Aus() override;
	void signalleuchteQ2An() override;
	void signalleuchteQ2Aus() override;
};

#endif /* HAL_AKTORIK_WRAPPER_BEDIENPANEL_H_ */
