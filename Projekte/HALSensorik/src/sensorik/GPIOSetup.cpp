/*
 * GPIOSetup.cpp
 *
 *  Created on: 15.11.2022
 *      Author: User
 */

#include "GPIOSetup.h"

GPIOSetup::GPIOSetup() {
	// TODO Auto-generated constructor stub

}

GPIOSetup::~GPIOSetup() {
	// TODO Auto-generated destructor stub
}

void GPIOSetup::requestGPIOAbiltiys(){
	// Request interrupt and IO abilities.
	int procmgr_status = procmgr_ability(0,
			PROCMGR_ADN_ROOT | PROCMGR_AOP_ALLOW | PROCMGR_AID_INTERRUPT,
			PROCMGR_ADN_NONROOT | PROCMGR_AOP_ALLOW | PROCMGR_AID_INTERRUPT,
			PROCMGR_ADN_ROOT | PROCMGR_AOP_ALLOW | PROCMGR_AID_IO,
			PROCMGR_ADN_NONROOT | PROCMGR_AOP_ALLOW | PROCMGR_AID_IO,
			PROCMGR_AID_EOL);
	if (procmgr_status != EOK) {
		perror("Requested abilities failed or denied!");
		exit (EXIT_FAILURE);
	}
}

void GPIOSetup::configGPIOIRQEventTypes(uintptr_t port0BaseAddr){
	// Set irq event types.
		unsigned int temp;
		// Enable interrupts on pins.
		temp = (
				BIT_MASK(LS_ANFANG_PIN) |
				BIT_MASK(HS_HOCH_OK_PIN) |
				BIT_MASK(LS_SEPERATOR_PIN) |
				BIT_MASK(METALLSENSOR_PIN) |
				BIT_MASK(LS_ZUSTAND_SEPERATOR_PIN) |
				BIT_MASK(LS_RUTSCHE_PIN) |
				BIT_MASK(LS_ENDE_PIN) |
				BIT_MASK(T_START_PIN) |
				BIT_MASK(T_STOP_PIN) |
				BIT_MASK(T_RESET_PIN) |
				BIT_MASK(E_STOP_PIN)
				);//Add desired pins.
		out32((uintptr_t) port0BaseAddr + GPIO_IRQSTATUS_SET_1, temp);



		//	(for rising edge detection)
		temp = in32((uintptr_t) (port0BaseAddr + GPIO_RISINGDETECT));			//Read current config.
		temp |= (
				BIT_MASK(LS_ANFANG_PIN) |
				BIT_MASK(HS_HOCH_OK_PIN) |
				BIT_MASK(LS_SEPERATOR_PIN) |
				BIT_MASK(METALLSENSOR_PIN) |
				BIT_MASK(LS_ZUSTAND_SEPERATOR_PIN) |
				BIT_MASK(LS_RUTSCHE_PIN) |
				BIT_MASK(LS_ENDE_PIN) |
				BIT_MASK(T_START_PIN) |
				BIT_MASK(T_STOP_PIN) |
				BIT_MASK(T_RESET_PIN) |
				BIT_MASK(E_STOP_PIN)
				);//Add desired pins.

		out32((uintptr_t) (port0BaseAddr + GPIO_RISINGDETECT), temp);			//Write new config back.

		// 	(for falling edge detection)
		temp = in32((uintptr_t) (port0BaseAddr + GPIO_FALLINGDETECT));			//Read current config.
		temp |= (
				BIT_MASK(LS_ANFANG_PIN) |
				BIT_MASK(HS_HOCH_OK_PIN) |
				BIT_MASK(LS_SEPERATOR_PIN) |
				BIT_MASK(METALLSENSOR_PIN) |
				BIT_MASK(LS_ZUSTAND_SEPERATOR_PIN) |
				BIT_MASK(LS_RUTSCHE_PIN) |
				BIT_MASK(LS_ENDE_PIN) |
				BIT_MASK(T_START_PIN) |
				BIT_MASK(T_STOP_PIN) |
				BIT_MASK(T_RESET_PIN) |
				BIT_MASK(E_STOP_PIN)
				);//Add desired pins.
		out32((uintptr_t) (port0BaseAddr + GPIO_FALLINGDETECT), temp);			//Write new config back.
}
