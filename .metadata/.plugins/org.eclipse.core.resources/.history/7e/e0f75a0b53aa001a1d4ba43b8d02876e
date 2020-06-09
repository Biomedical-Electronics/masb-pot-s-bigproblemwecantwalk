/**
  ******************************************************************************
  * @file		cyclic_voltammetry.c
  * @brief		Gestión de la voltammetría cíclica.
  * @author		Albert Álvarez Carulla
  * @copyright	Copyright 2020 Albert Álvarez Carulla. All rights reserved.
  ******************************************************************************
  */

#include "components/cyclic_voltammetry.h"
#include "components/masb_comm_s.h"

extern uint8_t count;
extern char *estado; // la fem extern perque s'accedirà des de l'interrupt
extern double vcell;


void Cyclic_voltammetryManagement(struct CV_Configuration_S cvConfiguration){

	double VCELL = cvConfiguration.eBegin; //eBegin, the beginning voltage is assigned to VCELL
	SendVoltageToDac(VCELL); // We use the function to apply voltage to the cell with VCELL
	double vObjetivo = cvConfiguration.eVertex1; //

	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, 1);// We close the realy in order to cnnect the circuit

	uint8_t cycles = cvConfiguration.cycles; // total number of cycles the cyclic voltammetry goes through
	double scanRate = cvConfiguration.scanRate; //variation of the electrochemical cell in time
	double eStep = cvConfiguration.eStep; // increase/decrease of voltage between two consecutive point
	double samplingPeriod = scanRate/eStep; //the sampling period corresponds to the time between samples

	ClockConfiguration(samplingPeriod); // the timer is configured with the samplingPeriod

	uint8_t count = 1; // the count variable used in conditionals and other functions, we make it to be 1.
	estado = "CV"; // the status of the measure is CV, with all that corresponds to it.
	int sign = 1; // variable that helps us change the sign of eStep for proper application

	while (count <= cycles){ // while the count has not gotten to the final cycle which is cycles
		estado = "CV"; // the status of the measures is CV

		if (vcell == vObjetivo){ //if the real vcell (read with the ADC) is equal to vObjetivo


				if (vObjetivo == cvConfiguration.eVertex1){ // if eVertex1 is equal to vObjetivo

					vObjetivo = cvConfiguration.eVertex2; // we change the value of vObjetivo to eVertex2
					sign = -1; // and the sign for the eStep variable is changed
				}

				else if (vObjetivo == cvConfiguration.eVertex2){ // if eVertex2 is equal to vOBjetivo

					vObjetivo = cvConfiguration.eBegin; //we change the value of vObjetivo to eBegin
					sign = 1; // and the sign for the eStep variable is changed
				}

				else if (count == cycles){ // if the count equals the total number of cycles

					estado = "IDLE"; // the status is change to IDLE so it stops the measure
				}

				else{ // if count is not the last cycles, cycles

					vObjetivo = cvConfiguration.eVertex1; // we change the vObjetivo value to eVertex1
					sign = 1; // and the sign for the eStep variable is changed
				}


		}
		else{

			if (VCELL + (eStep*sign) > vObjetivo){ //if VCELL plus the increase/decrease of eStep is larger than vObjetivo
				SendVoltageToDac(vObjetivo); //then we fix the voltage of the cell with this vObjetivo
			}
			else{
				VCELL = VCELL +(eStep*sign); //if its not bigger, we add to VCELL the eStep, so the voltage changes and we cna measure other points
				SendVoltageToDac(VCELL); // we assign this new VCELL to the voltage applied to the cell

			}
		}
	}

	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, 0); // the relay is opened so the measurement stops

}




