/*
 * Laufband.h
 *
 *  Created on: 17.10.2022
 *  Author: Tobias Thoelen
 */

#ifndef HAL_AKTORIK_WRAPPER_LAUFBAND_H_
#define HAL_AKTORIK_WRAPPER_LAUFBAND_H_


#include "../Aktorik.h"
#include "interfaces/ILaufband.h"


#define LAUFBANDRECHTS 0x00001000
#define LAUFBANDLINKS 0x00002000
#define LAUFBANDLANGSAM 0x00004000
#define LAUFBANDSTOP 0x00008000


class Laufband : public ILaufband{
private:
	//variables
	uintptr_t gpio_bank_1;
public:
	//ctor
	Laufband();
	//dtor
	virtual ~Laufband();
	//functions
	void laufbandRechtsAn() override;
	void laufbandRechtsAus() override;
	void laufbandLinksAn() override;
	void laufbandLinksAus() override;
	void laufbandLangsamAn() override;
	void laufbandLangsamAus() override;
	void laufbandStopAn() override;
	void laufbandStopAus() override;
};

#endif /* HAL_AKTORIK_WRAPPER_LAUFBAND_H_ */
