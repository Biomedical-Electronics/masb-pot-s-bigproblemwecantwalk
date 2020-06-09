/*
 * adc.c
 *
 *  Created on: May 27, 2020
 *      Author: cmaim
 */
#include <components/adc.h>
#include <components/masb_comm_s.h>
#include <stdio.h>

uint32_t Vadc = 0;
ADC_HandleTypeDef hadc1;
extern double vcell=0;

// what we want out of this function, with inputs count and sampling period, is to have an structure Data_S pointdata
// whose variables are characteristic for each point in chronoamperometry and cyclic voltammetry.
struct Data_S ADC_function(uint8_t count, double samplingPeriod){

		HAL_ADC_Start(&hadc1); // the conversion starts

		HAL_ADC_PollForConversion(&hadc1, 200); // we wait 200 ms to make sure the conversion is done
		Vadc = (HAL_ADC_GetValue(&hadc1)*4/4096); // we store the value resulting from the conversion and multiplied by factor (4/4096)
												  // (since the resolution of the ADC is 12 bits) in the variable Vadc.

		double vcell = ((1.65-Vadc)*2); //following the formulas on the paper we are able to get the voltage and current of the cell.

		double icell = ((Vadc - 1.65)*2)/Rtia;

		struct Data_S pointdata; //here we create the structure pointdata of type Data_S so we

		pointdata.point = count; // since count represents the number of measures that have been done, we assign it to point (same meaning)
		pointdata.timeMs = count*samplingPeriod; // according to the definition of timeMs, this multiplication corresponds to the time
												 // that has passed since the start of measurements
		pointdata.voltage = vcell; // voltage of the cell
		pointdata.current = icell; // current of the cell

		return pointdata; // as said, the function return a structure with the 4 needed parameters (for each point)
						  // needed for the graphical representation of the tests.
}


