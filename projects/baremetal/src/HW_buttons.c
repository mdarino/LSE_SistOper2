/*******************************************************************************
              Copyright 2015 Arimex Importadora SA, All Rights Reserved
 *******************************************************************************
 ***************************************************************************/


/** @brief Brief for this file.
 **
 **/

/** \addtogroup Hardware Buttons
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 * MD           Marcos Darino
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * 20151109 v0.0.1   MD first version
 */

/*==================[inclusions]=============================================*/

#include "HW_buttons.h"


/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/

void buttonConstructor (struct STR_Button *button, uint8_t gpio, uint8_t gpio_bit)
{
	button->state=UNDEFINED;
	button->time=0;
	button->gpio=gpio;
	button->gpio_bit=gpio_bit;
	button->lastState=UNDEFINED;
}

void buttonInitWithoutPullUp (struct STR_Button *button, uint8_t  port, uint8_t  port_pin ,uint8_t function)
{
	GPIO_pinConfiguration(port,port_pin, MD_PUP|MD_EZI|MD_ZI,function);
	GPIO_setAsInput(button->gpio,button->gpio_bit);
}

void buttonUpdate (struct STR_Button *button)
{
	if (!(GPIO_getValue(button->gpio,button->gpio_bit)))
	{
		button->time++;
		if (button->time>65000)
			button->time=65000;
		if (button->time>20)
			button->state=PRESS;
	}
	else
	{
		button->state=RELEASE;
		button->time=0;
	}
	
}


uint16_t buttonGetTime (struct STR_Button *button)
{
	return (button->time);
}	

uint8_t buttonGetState (struct STR_Button *button)
{
	return (button->state);
}	

uint8_t buttonGetLastState (struct STR_Button *button)
{
	return (button->lastState);
}
void buttonSetLastState (struct STR_Button *button, uint8_t lastButState)
{
	button->lastState=lastButState;
}


/** @} doxygen end group definition */
/*==================[end of file]============================================*/

