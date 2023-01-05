/*
 * ISortierer.h
 *
 *  Created on: 16.10.2022
 *  Author: Tobias Thoelen
 */

#ifndef HAL_AKTORIK_WRAPPER_ISEPERATOR_H_
#define HAL_AKTORIK_WRAPPER_ISEPERATOR_H_

class ISeperator {
public:
	virtual void sortiererEinfahren() = 0;
	virtual void sortiererAusfahren() = 0;
};

#endif /* HAL_AKTORIK_WRAPPER_ISORTIERER_H_ */
