/*
 * loop.c
 *
 *  Created on: 7 jun. 2020
 *      Author: Carles
 */


#include "components/loop.h"


struct CV_Configuration_S cvConfiguration; // guarda el valor de cv i ca
struct CA_Configuration_S caConfiguration;
struct Data_S data;

extern char *estado; // la fem extern perque s'accedirà des de l'interrupt
extern uint8_t count;
extern double samplingPeriod;
extern double Ts;
extern TIM_HandleTypeDef htim3;

void setup(void) {

    MASB_COMM_S_waitForMessage(); // Waiting the first message.
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 1); // PMU setup
}

void loop(void) {

    if (MASB_COMM_S_dataReceived()) { // si se recibe un paquete...

        switch(MASB_COMM_S_command()) {
        case START_CV_MEAS: // rebem info de CV i fem start de cyclic voltametry
        	cvConfiguration = MASB_COMM_S_getCvConfiguration();
        	Cyclic_voltammetryManagement(cvConfiguration);
        	break;

        case START_CA_MEAS: // rebem info de CA i fem start de chrono amperimmetry
        	caConfiguration = MASB_COMM_S_getCaConfiguration();
        	ChronoamperometryManagement(caConfiguration);
        	break;

        case STOP_MEAS:
        	break;

        default:
            break;

        }


        MASB_COMM_S_waitForMessage(); // esperamos a recibir un paquete nuevo
    }

}


void interrupt_management(void){

	if (estado == "Cv"){
		struct Data_S data = ADC_function(count, samplingPeriod); // obtenemos medicion
		MASB_COMM_S_sendData(data); // mandamos medicion al host
	}
	else if (estado == "Ca"){
		struct Data_S data = ADC_function(count, Ts); // obtenemos medicion
		MASB_COMM_S_sendData(data); // mandamos medicion al host
	}
	else if (estado == "IDLE"){
		HAL_TIM_Base_Stop_IT(&htim3);
	}

	count++;
}
