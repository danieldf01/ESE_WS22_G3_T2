/*
 * FehlerWsAbstand.h
 *
 *  Created on: 21.12.2022
 *      Author: Marek
 */

#ifndef LOGIK_HAUPTZUSTAENDE_FBM1_LSANFANG_FEHLERWSABSTAND_H_
#define LOGIK_HAUPTZUSTAENDE_FBM1_LSANFANG_FEHLERWSABSTAND_H_

#include "BaseStateLSA1.h"
#include "QuittiertWsAbstand.h"

class FehlerWsAbstand : public BaseStateLSA1{
public:
	void entry() override;
	void exit() override;
	void LSan() override;
	void WSstecktFest() override;
	void quittiert() override;
	void keinFehler() override;
	void LSaus() override;
	void eStop() override;
	void timerAbstand() override;
};

#endif /* LOGIK_HAUPTZUSTAENDE_FBM1_LSANFANG_FEHLERWSABSTAND_H_ */
