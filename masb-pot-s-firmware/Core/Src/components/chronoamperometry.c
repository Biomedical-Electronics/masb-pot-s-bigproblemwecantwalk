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

extern TIM_HandleTypeDef htim3;
extern char estado;

char ChronoamperometryManagement(struct CA_Configuration_S caConfiguration){


	double eDC = caConfiguration.eDC;
	SendVoltageToDac(eDC); //Fixem el voltatge a la cell

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, 1); // Tanquem el relé

	uint32_t Ts = caConfiguration.samplingPeriodMs;
	uint32_t Mt = caConfiguration.measurementTime;

	uint8_t TotalMeasurements = round(Mt/(Ts/1000));

	ClockConfiguration(Ts,Mt); // Configuració del timer
	HAL_TIM_Base_Start_IT(&htim3); // Inicialitzem el timer

	int count = 1;
	while (count<=TotalMeasurements){
		if (count == TotalMeasurements){
			&estado = "IDLE";
		}
		&estado= "CA";

		return estado;
	}

	HAL_TIM_Base_Stop_IT(&htim3);

}
