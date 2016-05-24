/*******************************************************************************
              Copyright 2015 Arimex Importadora SA, All Rights Reserved
 *******************************************************************************
 ***************************************************************************/

#ifndef _HW_LEDS_H_
#define _HW_LEDS_H_
/** @brief Brief for this header file.
 **
 ** Full description for this header file.
 **
 **/

/** \addtogroup Hardware LEDs
 ** @{ */

/*
 * Initials    Name
 * ---------------------------
 * MD          MARCOS DARINO
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * 20151109 v0.0.1 FN Initial release.
 */

/*==================[inclusions]=============================================*/
#include "DRIVER_GPIO.h"
/*==================[cplusplus]==============================================*/

#ifdef __cplusplus
extern "C" {
#endif


/*==================[macros]=================================================*/

//
//	LED NUMBER DEFINES
//

#define LED_1		3	//!< Number of the LED 1  
#define LED_2		4	//!< Number of the LED 2
#define LED_3		5	//!< Number of the LED 3
#define LED_BLUE	2	//!< Number of the LED blue
#define LED_GREEN	1	//!< Number of the LED green
#define LED_RED 	0	//!< Number of the LED red


//
//	GPIO DEFINES
//
#define LED_1_GPIO		0	//!< GPIO of the LED
#define LED_2_GPIO		1	//!< GPIO of the LED
#define LED_3_GPIO		1	//!< GPIO of the LED
#define LED_BLUE_GPIO	5	//!< GPIO of the LED
#define LED_GREEN_GPIO	5	//!< GPIO of the LED
#define LED_RED_GPIO 	5	//!< GPIO of the LED

#define LED_1_GPIO_BIT		14	//!< BIT of the LED in the GPIO
#define LED_2_GPIO_BIT		11	//!< BIT of the LED in the GPIO
#define LED_3_GPIO_BIT		12	//!< BIT of the LED in the GPIO
#define LED_BLUE_GPIO_BIT	2	//!< BIT of the LED in the GPIO
#define LED_GREEN_GPIO_BIT	1	//!< BIT of the LED in the GPIO
#define LED_RED_GPIO_BIT 	0	//!< BIT of the LED in the GPIO

//
//	PORT/PIN DEFINES
//

#define LED_1_PORT		2	//!< Port of the LED - Use to configure the pin
#define LED_2_PORT		2	//!< Port of the LED - Use to configure the pin
#define LED_3_PORT		2	//!< Port of the LED - Use to configure the pin
#define LED_BLUE_PORT	2	//!< Port of the LED - Use to configure the pin
#define LED_GREEN_PORT	2	//!< Port of the LED - Use to configure the pin
#define LED_RED_PORT 	2	//!< Port of the LED - Use to configure the pin

#define LED_1_PORT_PIN		10		//!< Pin of the LED in the Port
#define LED_2_PORT_PIN		11		//!< Pin of the LED in the Port
#define LED_3_PORT_PIN		12		//!< Pin of the LED in the Port
#define LED_BLUE_PORT_PIN	2		//!< Pin of the LED in the Port
#define LED_GREEN_PORT_PIN	1		//!< Pin of the LED in the Port
#define LED_RED_PORT_PIN 	0		//!< Pin of!< the LED in the Port


/*==================[typedef]================================================*/

/*==================[external data declaration]==============================*/


/*==================[external functions declaration]=========================*/

/**
 * @brief Turn on the LED
 * @param LEDNumber : Number of the LED to turn ON
  */
void led_SetON (uint8_t LEDNumber);

/**
 * @brief Turn of the LED
 * @param LEDNumber Number of the LED to turn OFF
 */
void led_SetOFF (uint8_t LEDNumber);

/**
 * @brief Toggle the LED
 * @param LEDNumber Number of the LED to turn OFF
 */
void led_SetToggle (uint8_t LEDNumber);



/**
 * @brief 	Configure the Ports and set as output the GPIO
 * @note	If you add new LED you should add it in this function
 */
void led_Init (void);

/**
 * @brief 	Turn off all the LEDs and then turn on all
 * @note	To test the LED you should use the DEBUG mode and breakpoints
 */
void led_Test (void);


/*==================[cplusplus]==============================================*/

#ifdef __cplusplus
}
#endif

/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _HW_LEDS_H_ */

