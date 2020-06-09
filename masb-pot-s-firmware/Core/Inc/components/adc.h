/*
 * adc.h
 *
 *  Created on: May 27, 2020
 *      Author: cmaim
 */

#ifndef INC_COMPONENTS_ADC_H_
#define INC_COMPONENTS_ADC_H_

#include "stm32f4xx_hal.h"

#define Rtia    10000


// Prototypes
struct Data_S ADC_function(uint8_t count, double samplingPeriod);


#endif /* INC_COMPONENTS_ADC_H_ */
