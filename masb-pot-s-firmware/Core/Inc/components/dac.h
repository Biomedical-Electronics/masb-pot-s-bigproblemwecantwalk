/*
 * dac.h
 *
 *  Created on: May 26, 2020
 *      Author: Carles
 */

#ifndef INC_COMPONENTS_DAC_H_
#define INC_COMPONENTS_DAC_H_

#include "stm32f4xx_hal.h"
#include "math.h"

#define MCP4725 0x60 // Adress of the device

#define DAC_SIZE 3 // Size of the transmited buffer

#define CONTROL_BYTE  0b01000000 // DAC control byte

#define RELAY_PORT	GPIOA
#define RELAY_PIN	GPIO_PIN_5



// Prototypes
void SendVoltageToDac(double Voltage);
void ClockConfiguration(uint32_t Ts);

#endif /* INC_COMPONENTS_DAC_H_ */
