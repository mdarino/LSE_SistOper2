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
 * MD           Full Name
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * 20151109 v0.0.1   MD first version
 */

/*==================[inclusions]=============================================*/
#include "DRIVER_GPIO.h"
#include "HW_leds.h"
/*==================[macros and definitions]=================================*/




/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/
static gpioPin_t leds[6] = {{LED_RED_GPIO,LED_RED_GPIO_BIT},
{LED_GREEN_GPIO,LED_GREEN_GPIO_BIT},
{LED_BLUE_GPIO,LED_BLUE_GPIO_BIT},
{LED_1_GPIO,LED_1_GPIO_BIT},
{LED_2_GPIO,LED_2_GPIO_BIT},
{LED_3_GPIO,LED_3_GPIO_BIT} };
/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/


/*==================[external functions definition]==========================*/

/*Set ON the LED*/
void led_SetON (uint8_t LEDNumber)
{
	GPIO_setON(leds[LEDNumber].gpio,leds[LEDNumber].bit);
}
/*Set OFF the LED*/
void led_SetOFF (uint8_t LEDNumber)
{
	GPIO_SetOFF(leds[LEDNumber].gpio,leds[LEDNumber].bit);
}

/*Configure the port and the GPIO of the LEDs*/
void led_Init (void)
{

	//Configure the fuction of the pin -> as GPIO and without pullups
	GPIO_pinConfiguration(LED_RED_PORT,LED_RED_PORT_PIN,SCU_MODE_INACT ,FUNC4);  /* GPIO5[0], LED0R */
	GPIO_pinConfiguration(LED_GREEN_PORT,LED_GREEN_PORT_PIN,SCU_MODE_INACT ,FUNC4);  /* GPIO5[1], LED0G */
	GPIO_pinConfiguration(LED_BLUE_PORT,LED_BLUE_PORT_PIN,SCU_MODE_INACT ,FUNC4);  /* GPIO5[2], LED0B */
	GPIO_pinConfiguration(LED_1_PORT,LED_1_PORT_PIN,SCU_MODE_INACT ,FUNC0); /* GPIO0[14], LED1 */
	GPIO_pinConfiguration(LED_2_PORT,LED_2_PORT_PIN,SCU_MODE_INACT ,FUNC0); /* GPIO1[11], LED2 */
	GPIO_pinConfiguration(LED_3_PORT,LED_3_PORT_PIN,SCU_MODE_INACT ,FUNC0); /* GPIO1[12], LED3 */
	// Set as outputs all the GPIO
	GPIO_setAsOutput(LED_RED_GPIO,LED_RED_GPIO_BIT);
	GPIO_setAsOutput(LED_GREEN_GPIO,LED_GREEN_GPIO_BIT);
	GPIO_setAsOutput(LED_BLUE_GPIO,LED_BLUE_GPIO_BIT);
	GPIO_setAsOutput(LED_1_GPIO,LED_1_GPIO_BIT);
	GPIO_setAsOutput(LED_2_GPIO,LED_2_GPIO_BIT);
	GPIO_setAsOutput(LED_3_GPIO,LED_3_GPIO_BIT);
}

/*test LEDs - YOU MUST USE DEBUG AND BREAKPOINTS*/
void led_Test (void)
{

	led_SetOFF(LED_RED);
	led_SetOFF(LED_GREEN);
	led_SetOFF(LED_BLUE);
	led_SetOFF(LED_1);
	led_SetOFF(LED_2);
	led_SetOFF(LED_3);

	led_SetON(LED_RED);
	led_SetON(LED_GREEN);
	led_SetON(LED_BLUE);
	led_SetON(LED_1);
	led_SetON(LED_2);
	led_SetON(LED_3);


	led_SetOFF(LED_RED);
	led_SetOFF(LED_GREEN);
	led_SetOFF(LED_BLUE);
	led_SetOFF(LED_1);
	led_SetOFF(LED_2);
	led_SetOFF(LED_3);


}


/** @} doxygen end group definition */
/*==================[end of file]============================================*/

