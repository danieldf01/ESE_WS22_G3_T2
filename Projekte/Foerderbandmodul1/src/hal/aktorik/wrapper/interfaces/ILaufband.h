/*
 * ILaufband.h
 *
 *  Created on: 17.10.2022
 *  Author: Tobias Thoelen
 */

#ifndef HAL_AKTORIK_INTERFACES_ILAUFBAND_H_
#define HAL_AKTORIK_INTERFACES_ILAUFBAND_H_


class ILaufband {
public:
	virtual void laufbandRechtsAn() = 0;
	virtual void laufbandRechtsAus() = 0;
	virtual void laufbandLinksAn() = 0;
	virtual void laufbandLinksAus() = 0;
	virtual void laufbandLangsamAn() = 0;
	virtual void laufbandLangsamAus() = 0;
	virtual void laufbandStopAn() = 0;
	virtual void laufbandStopAus() = 0;
};

#endif /* HAL_AKTORIK_INTERFACES_ILAUFBAND_H_ */
