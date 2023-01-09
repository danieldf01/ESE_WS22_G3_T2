/*
 * Sortierer.cpp
 *
 *  Created on: 16.10.2022
 *  Author: Tobias Thoelen
 */
#include "Seperator.h"


using namespace std;

Seperator::Seperator() {
	gpio_bank_1 = mmap_device_io(0x1000, (uint64_t) 0x4804C000);
	out32((uintptr_t) (gpio_bank_1 + GPIO_OE_REGISTER_AKT), 0x00000000);

	//this->seperatorTyp = in32((uintptr_t) (gpio_bank_1  & 14));
}

Seperator::~Seperator() {
}


void Seperator::sortiererEinfahren() {
	out32((uintptr_t) (gpio_bank_1 + GPIO_CLEARDATAOUT_AKT), SORTIERER);
}

void Seperator::sortiererAusfahren() {
	out32((uintptr_t) (gpio_bank_1 + GPIO_SETDATAOUT_AKT), SORTIERER);
}
