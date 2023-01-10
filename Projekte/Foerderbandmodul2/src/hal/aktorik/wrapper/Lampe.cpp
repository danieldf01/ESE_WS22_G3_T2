/*
 * lampen.cpp
 *
 *  Created on: 16.10.2022
 *  Author: Tobias Thoelen
 */
#include "Lampe.h"




using namespace std;

Lampe::Lampe() {
	gpio_bank_1 = mmap_device_io(0x1000, (uint64_t) 0x4804C000);
	out32((uintptr_t) (gpio_bank_1 + GPIO_OE_REGISTER_AKT), 0x00000000);
}

Lampe::~Lampe() {
}


void Lampe::lampeGruenAn() {
	out32((uintptr_t) (gpio_bank_1 + GPIO_SETDATAOUT_AKT), GRUENE_LAMPE);
}

void Lampe::lampeGruenAus() {
	out32((uintptr_t) (gpio_bank_1 + GPIO_CLEARDATAOUT_AKT), GRUENE_LAMPE);
}

void Lampe::lampeGelbAn() {
	out32((uintptr_t) (gpio_bank_1 + GPIO_SETDATAOUT_AKT), GELBE_LAMPE);
}

void Lampe::lampeGelbAus() {
	out32((uintptr_t) (gpio_bank_1 + GPIO_CLEARDATAOUT_AKT), GELBE_LAMPE);
}

void Lampe::lampeRotAn() {
	out32((uintptr_t) (gpio_bank_1 + GPIO_SETDATAOUT_AKT), ROTE_LAMPE);
}

void Lampe::lampeRotAus() {
	out32((uintptr_t) (gpio_bank_1 + GPIO_CLEARDATAOUT_AKT), ROTE_LAMPE);
}
