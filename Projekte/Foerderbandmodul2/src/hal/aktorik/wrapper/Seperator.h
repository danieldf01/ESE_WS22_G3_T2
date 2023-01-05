/*
 * Sortierer.h
 *
 *  Created on: 16.10.2022
 *  Author: Tobias Thoelen
 */

#ifndef HAL_AKTORIK_WRAPPER_SEPERATOR_H_
#define HAL_AKTORIK_WRAPPER_SEPERATOR_H_

#include "../Aktorik.h"
#include "interfaces/ISeperator.h"
#include <thread>
#include <iostream>
#include <errno.h>
#include <sys/dispatch.h>

#define SORTIERER 0x00080000

class Seperator : public ISeperator {
private:
	//variables
	uintptr_t gpio_bank_1;

public:
	Seperator();
	virtual ~Seperator();
	void sortiererEinfahren()override;
	void sortiererAusfahren()override;
};

#endif /* HAL_AKTORIK_WRAPPER_SEPERATOR_H_ */
