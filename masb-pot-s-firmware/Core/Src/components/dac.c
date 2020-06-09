/*
 * dac.c
 *
 *  Created on: May 26, 2020
 *      Author: Carles
 */

#include <components/dac.h>

extern I2C_HandleTypeDef hi2c1;

const uint8_t MCP4725_ADDR = MCP4725 << 1; // 8-bit DAC address
uint8_t DacBuffer[DAC_SIZE] = {0}; // buffer to save the transmitted values
uint32_t prescaler = 8.399; // Prescalado del reloj para reducir la frequancia a 10MHz
extern TIM_HandleTypeDef htim3;
char estado[];


void SendVoltageToDac(double Voltage){

	uint16_t DAC_voltage = round(Voltage*4096/4); // Conversión
	DacBuffer[0] = CONTROL_BYTE;
	DacBuffer[1] = DAC_voltage >> 4; // MSB 11-4 shift right 4 places
	DacBuffer[2] = DAC_voltage << 4; // LSB 3-0 shift left 4 places

		  // Transmits data
	HAL_I2C_Master_Transmit(&hi2c1, MCP4725_ADDR, DacBuffer, DAC_SIZE, HAL_MAX_DELAY);
}

void ClockConfiguration(uint32_t Ts){

	uint32_t ticks_period = (84e6 * (Ts/1000)); // calcul de tics per cada periode

	htim3.Instance = TIM3;  // definim el timer i les caracteristiques
	htim3.Init.Period = ticks_period;
	htim3.Init.Prescaler = prescaler;
	htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim3.Init.CounterMode = TIM_COUNTERMODE_UP;

	HAL_TIM_Base_Start_IT(&htim3); // Inicialitzem el timer

}
