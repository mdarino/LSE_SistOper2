/*************************************************************************//**

  @file     HW_buttons.c

  @brief    Hardware Library to use buttons

  @author   Marcos Darino (MD)


 ******************************************************************************/


/** \addtogroup HARDWARE_GROUP HARDWARE
 ** @{ */


/** \addtogroup BUTTONS_GROUP BUTTONS
 ** @{ */


/*==================[inclusions]=============================================*/

#include "HW_buttons.h"


/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/


/*Button constructor: define the GPIO and the bit*/
void buttonConstructor (button_t *button, uint8_t gpio, uint8_t gpio_bit)
{
	button->state=UNDEFINED;
	button->time=0;
	button->lastTime=0;
	button->gpio=gpio;
	button->gpio_bit=gpio_bit;
	button->lastState=UNDEFINED;
}

/*Button init: configure the pin and set as output*/
void buttonInitWithoutPullUp (button_t *button, uint8_t  port, uint8_t  port_pin ,uint8_t function)
{
	GPIO_pinConfiguration(port,port_pin, MD_PUP|MD_EZI|MD_ZI,function);
	GPIO_setAsInput(button->gpio,button->gpio_bit);
}

/*buttons Update: update the state of the buttons*/
void buttonUpdate (button_t *button)
{
	// if (!(GPIO_getValue(button->gpio,button->gpio_bit)))
	// {
	// 	button->time++;
	// 	if (button->time>1000000)  //4294967295
	// 		button->time=1000000;
	// 	if (button->time>TICKS_TO_SET_PRESS)
	// 		button->state=PRESS;
		
	// }
	// else
	// {
	// 	button->state=RELEASE;
	// 	button->time=0;
	// }





	switch (button->state)
	{	
		case PRESS:
			
			if (!(GPIO_getValue(button->gpio,button->gpio_bit)))
			{
				button->time++;

			}
			else
			{
				button->lastTime=button->time;
				button->lastState=PRESS;
				button->state=RELEASE;
				button->time=0;
			}


		break;
		case ANTIREBOUND:
			if (!(GPIO_getValue(button->gpio,button->gpio_bit)))
			{
				button->time++;
				if (button->time>TICKS_TO_SET_PRESS)
				{
					button->state=PRESS;
					button->time=0;
				}	
					
			}
			else
			{
				button->state=RELEASE;
				button->time=0;
			}			

		break;
		case RELEASE:
			
			if (!(GPIO_getValue(button->gpio,button->gpio_bit)))
			{
				button->lastTime=button->time;
				button->lastState=RELEASE;
				button->state=ANTIREBOUND;
				button->time=0;
			}
			else
			{
				button->time++;	
			}		
		break;				

		default :
		break;
	}

	
	
}



/*buttons get time: return how many mseg it is pressed the button */
uint32_t buttonGetTime (button_t *button)
{
	// uint32_t time_in_msec;
	// if(button->time > TICKS_TO_SET_PRESS)
	// {
	// 	time_in_msec=(button->time-TICKS_TO_SET_PRESS)*TICKS_BUTTON_TIME;
	// }
	// else
	// {
	// 	time_in_msec=0;
	// }
	
	// return (time_in_msec);
	// 
	return (button->time);
}	

/*buttons get state: return if the button is press or release */
uint8_t buttonGetState (button_t *button)
{
	return (button->state);
}	

/*buttons get state: return if the button is press or release */
/*only is press if after was release*/
uint8_t buttonGetStateWithRl (button_t *button)
{
	uint8_t bState=RELEASE;
	

	if (button->state==PRESS)
	{
		if (button->lastState==RELEASE)
		{
			bState=PRESS;
		}
		button->lastState=PRESS;
	}
	else
	{
		button->lastState=RELEASE;
	}

	return (bState);
}	

/*buttons lastState: return the last state of the button */
uint8_t buttonGetLastState (button_t *button)
{
	return (button->lastState);
}
/*buttons lastState: set the last state of the button (to remember) */
void buttonSetLastState (button_t *button, uint8_t lastButState)
{
	button->lastState=lastButState;
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

