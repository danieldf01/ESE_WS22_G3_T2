/*
 * lampen.h
 *
 *  Created on: 16.10.2022
 *  Author: Tobias Thoelen
 */

#ifndef HAL_AKTORIK_LAMPEN_H_
#define HAL_AKTORIK_LAMPEN_H_

#include "../Aktorik.h"
#include "interfaces/ILampe.h"

#define ROTE_LAMPE 0x00010000
#define GELBE_LAMPE 0x00020000
#define GRUENE_LAMPE 0x00040000

class Lampe : public ILampe{
private:
	//variables
	uintptr_t gpio_bank_1;
public:
	//ctor
	Lampe();
	//dtor
	virtual ~Lampe();
	//functions
	void lampeGruenAn() override;
	void lampeGruenAus() override;
	void lampeGelbAn() override;
	void lampeGelbAus() override;
	void lampeRotAn() override;
	void lampeRotAus() override;
};

#endif /* HAL_AKTORIK_LAMPEN_H_ */
