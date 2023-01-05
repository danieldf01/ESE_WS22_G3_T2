/*
 * ILampen.h
 *
 *  Created on: 16.10.2022
 *  Author: Tobias Thoelen
 */

#ifndef HAL_AKTORIK_INTERFACES_ILAMPE_H_
#define HAL_AKTORIK_INTERFACES_ILAMPE_H_

#include "../Farbe.h"

class ILampe {
public:
	virtual void lampeGruenAn() = 0;
	virtual void lampeGruenAus() = 0;
	virtual void lampeGelbAn() = 0;
	virtual void lampeGelbAus() = 0;
	virtual void lampeRotAn() = 0;
	virtual void lampeRotAus() = 0;
};

#endif /* HAL_AKTORIK_INTERFACES_ILAMPE_H_ */
