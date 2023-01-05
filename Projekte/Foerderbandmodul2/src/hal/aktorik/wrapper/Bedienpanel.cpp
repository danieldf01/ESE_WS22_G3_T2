/*
 * Bedienpanel.cpp
 *
 *  Created on: 17.10.2022
 *  Author: Tobias Thoelen
 */

#include "Bedienpanel.h"



Bedienpanel::Bedienpanel() {
	gpio_bank_2 = mmap_device_io(0x1000, (uint64_t) 0x481AC000);
	out32((uintptr_t) (gpio_bank_2 + GPIO_OE_REGISTER_AKT), 0x00000000);
}

Bedienpanel::~Bedienpanel() {
	// TODO Auto-generated destructor stub
}


void Bedienpanel::ledStartAn() {
	out32((uintptr_t) (gpio_bank_2 + GPIO_SETDATAOUT_AKT), LED_START);
}

void Bedienpanel::ledStartAus() {
	out32((uintptr_t) (gpio_bank_2 + GPIO_CLEARDATAOUT_AKT), LED_START);
}

void Bedienpanel::ledResetAn() {
	out32((uintptr_t) (gpio_bank_2 + GPIO_SETDATAOUT_AKT), LED_RESET);
}

void Bedienpanel::ledResetAus() {
	out32((uintptr_t) (gpio_bank_2 + GPIO_CLEARDATAOUT_AKT), LED_RESET);
}

void Bedienpanel::signalleuchteQ1An() {
	out32((uintptr_t) (gpio_bank_2 + GPIO_SETDATAOUT_AKT), SL_Q1);
}

void Bedienpanel::signalleuchteQ1Aus() {
	out32((uintptr_t) (gpio_bank_2 + GPIO_CLEARDATAOUT_AKT), SL_Q1);
}

void Bedienpanel::signalleuchteQ2An() {
	out32((uintptr_t) (gpio_bank_2 + GPIO_SETDATAOUT_AKT), SL_Q2);
}

void Bedienpanel::signalleuchteQ2Aus() {
	out32((uintptr_t) (gpio_bank_2 + GPIO_CLEARDATAOUT_AKT), SL_Q2);
}
