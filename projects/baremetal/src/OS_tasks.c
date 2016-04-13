/*******************************************************************************
              Copyright 2015 Arimex Importadora SA, All Rights Reserved
 *******************************************************************************
 ***************************************************************************/


/** @brief Brief for this file.
 **
 **/

/** \addtogroup groupName Group Name
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 * MD           MARCOS DARINO
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * 20151109 v0.0.1   MD first version
 */

/*==================[inclusions]=============================================*/
#include "HW_leds.h"
#include "OS_tasks.h"
 
/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

volatile int32_t Led_State1;
volatile int32_t Led_State2;
volatile int32_t Led_State3;

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/

void Task1_Init(void){

}

void Task1(void){

	if (Led_State1 == 1){
	      led_SetOFF(LED_1); // Apago el pin
	      Led_State1 = 0;
	   }
	   else{
	      led_SetON(LED_1);// Prendo el pin
	      Led_State1 = 1;
	   }

}

void Task2_Init(void){

}

void Task2(void){

	if (Led_State2 == 1){
	      led_SetOFF(LED_2); // Apago el pin
	      Led_State2 = 0;
	   }
	   else{
	      led_SetON(LED_2);// Prendo el pin
	      Led_State2 = 1;
	   }


}


void Task3_Init(void){

}


void Task3(void){

	if (Led_State3 == 1){
	      led_SetOFF(LED_3); // Apago el pin
	      Led_State3 = 0;
	   }
	   else{
	      led_SetON(LED_3);// Prendo el pin
	      Led_State3 = 1;
	   }



}


/** @} doxygen end group definition */
/*==================[end of file]============================================*/

