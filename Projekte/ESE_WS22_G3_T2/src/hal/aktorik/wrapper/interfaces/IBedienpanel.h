/*
 * IBedienpanel.h
 *
 *  Created on: 17.10.2022
 *  Author: Tobias Thoelen
 */

#ifndef HAL_AKTORIK_WRAPPER_INTERFACES_IBEDIENPANEL_H_
#define HAL_AKTORIK_WRAPPER_INTERFACES_IBEDIENPANEL_H_

class IBedienpanel {
public:
	virtual void ledStartAn() = 0;
	virtual void ledStartAus() = 0;
	virtual void ledResetAn() = 0;
	virtual void ledResetAus() = 0;
	virtual void signalleuchteQ1An() = 0;
	virtual void signalleuchteQ1Aus() = 0;
	virtual void signalleuchteQ2An() = 0;
	virtual void signalleuchteQ2Aus() = 0;
};



#endif /* HAL_AKTORIK_WRAPPER_INTERFACES_IBEDIENPANEL_H_ */
