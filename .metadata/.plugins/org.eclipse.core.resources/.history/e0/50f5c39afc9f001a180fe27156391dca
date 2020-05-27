/*
 * dac.c
 *
 *  Created on: May 26, 2020
 *      Author: Carles
 */

#include "components/dac.h"

extern I2C_HandleTypeDef hi2c1;

const uint8_t MCP4725_ADDR = MCP4725 << 1; // 8-bit DAC address
uint8_t DacBuffer[DAC_SIZE] = {0}; // buffer to save the transmitted values


void SendVoltageToDac(double Voltage){

	uint16_t DAC_voltage = round(Voltage*4096/4); // Conversión
	DacBuffer[0] = CONTROL_BYTE;
	DacBuffer[1] = DAC_voltage >> 4; // MSB 11-4 shift right 4 places
	DacBuffer[2] = DAC_voltage << 4; // LSB 3-0 shift left 4 places

		  // Transmits data
	HAL_I2C_Master_Transmit(&hi2c1, MCP4725_ADDR, DacBuffer, DAC_SIZE, HAL_MAX_DELAY);
}
