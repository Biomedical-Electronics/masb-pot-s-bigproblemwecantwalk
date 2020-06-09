/**
  ******************************************************************************
  * @file		chronoamperometry.c
  * @brief		Gestión de la cronoamperometría.
  * @author		Albert Álvarez Carulla
  * @copyright	Copyright 2020 Albert Álvarez Carulla. All rights reserved.
  ******************************************************************************
  */

#include "components/chronoamperometry.h"
#include "components/masb_comm_s.h"
#include "components/dac.h"

extern char *estado; // la fem extern perque s'accedirà des de l'interrupt
extern uint8_t count;


void ChronoamperometryManagement(struct CA_Configuration_S caConfiguration){


	double eDC = caConfiguration.eDC;
	SendVoltageToDac(eDC); //Fixem el voltatge a la cell

	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, 1); // Tanquem el relé

	uint32_t Ts = caConfiguration.samplingPeriodMs;
	uint32_t Mt = caConfiguration.measurementTime;

	uint8_t TotalMeasurements = round(Mt/(Ts/1000)); // Calculem el nombre necessari de measurements

	ClockConfiguration(Ts); // Configuració del timer

	estado= "CA";
	count = 1;

	while (count<=TotalMeasurements){ // While loop que dura tot el measurement.

		if (count == TotalMeasurements){
			estado = "IDLE";
		}

		estado= "CA";

	}

	// Per tancar el clock hauria destar al propi  interrupt: HAL_TIM_Base_Stop_IT(&htim3);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, 0); // Obrim el relé

}
