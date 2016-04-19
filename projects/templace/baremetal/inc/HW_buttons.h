/*******************************************************************************
              Copyright 2015 Arimex Importadora SA, All Rights Reserved
 *******************************************************************************
 ***************************************************************************/

#ifndef _TEMPLATE_H_
#define _TEMPLATE_H_
/** @brief Brief for this header file.
 **
 ** Full description for this header file.
 **
 **/

/** \addtogroup Hardware Buttons
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

/*==================[typedef]================================================*/
struct	STR_Button
{
	uint8_t		state;
	uint8_t		lastState;
	uint16_t	time;
	uint8_t		gpio;
	uint8_t		gpio_bit;
};


//STATES
#define		PRESS		0
#define		RELEASE		1
#define		UNDEFINED	2


/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/


void buttonConstructor (struct STR_Button *button, uint8_t gpio, uint8_t gpio_bit);
void buttonInitWithoutPullUp (struct STR_Button *button, uint8_t  port, uint8_t  port_pin ,uint8_t function);
void buttonUpdate (struct STR_Button *button);
uint16_t buttonGetTime (struct STR_Button *button);
uint8_t buttonGetState (struct STR_Button *button);
uint8_t buttonGetLastState (struct STR_Button *button);
void buttonSetLastState (struct STR_Button *button, uint8_t lastButState);


/*==================[cplusplus]==============================================*/

#ifdef __cplusplus
}
#endif

/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _TEMPLATE_H_ */

