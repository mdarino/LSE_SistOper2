
/*************************************************************************//**

  @file     HW_buttons.h

  @brief    Hardware Library to use buttons

  @author   Marcos Darino (MD)

  @version  20151124 v0.0.1   MD Initial release.
 ******************************************************************************/


#ifndef _HW_BUTTONS_H_
#define _HW_BUTTONS_H_

/** \addtogroup HARDWARE_GROUP HARDWARE
 ** @{ */


/** \addtogroup BUTTONS_GROUP BUTTONS
 ** @{ */


/*==================[inclusions]=============================================*/
#include "DRIVER_GPIO.h"

/*==================[cplusplus]==============================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*==================[macros]=================================================*/

/*==================[typedef]================================================*/
typedef struct STR_Button
{
   uint8_t     state;
   uint8_t     lastState;
   uint32_t    time;
   uint32_t    lastTime;
   uint8_t     gpio;
   uint8_t     gpio_bit;
}button_t;


//STATES
#define     PRESS       0  //!< Number if it is press
#define     RELEASE     1  //!< Number if it is release
#define     ANTIREBOUND 2  //!< Number if it is the anti rebound routine
#define     UNDEFINED   3  //!< Number if it is undefined 


//TIMES
#define     TICKS_TO_SET_PRESS 2  ///!<For this case 2x10mseg ->press
#define     TICKS_BUTTON_TIME  10  ///Tick of the library is 10 mseg
#

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/

/**
 * @brief Create the button - Define the GPIO and his bit
 * @param button   Struct of the button
 * @param gpio     GPIO in the uC 
 * @param gpio_bit GPIO BIT in the uC 
 */
void buttonConstructor (button_t *button, uint8_t gpio, uint8_t gpio_bit);
/**
 * @brief Init of the button, Configure the Pin function and set it as input
 * @param button   Struct of the button
 * @param port     PORT in the uC
 * @param port_pin PORT PIN in the uC
 * @param function Function of the PORT PIN
 */
void buttonInitWithoutPullUp (button_t *button, uint8_t  port, uint8_t  port_pin ,uint8_t function);
/**
 * @brief Update the state of the button
 * @param button   Struct of the button
 * @note: It must be run in x ticks time. For example 1mseg
 */
void buttonUpdate (button_t *button);
/**
 * @brief Return how many msec is the button in this state
 * @param  button Struct of the button
 * @return        Number of msec is press
 */
uint32_t buttonGetTime (button_t *button);

/**
 * @brief Return how many msec was the button in the last state
 * @param  button Struct of the button
 * @return        Number of msec is press
 */
uint32_t buttonGetLastTime (button_t *button);

/**
 * @brief Return the state of the button
 * @param  button Struct of the button
 * @return        State of the button
 */
uint8_t buttonGetState (button_t *button);

/**
 * @brief Return the state of the button (but only is press if before was release)
 * @param  button Struct of the button
 * @return        State of the button
 */
uint8_t buttonGetStateWithRl (button_t *button);


/**
 * @brief Return the last state configured
 * @param  button Struct of the button
 * @return        last stated configured
 */

uint8_t buttonGetLastState (button_t *button);
/**
 * @brief  Config 
 * @param  button Struct of the button
 * @param  lastButState  Configure the state (used to remember)
 */
void buttonSetLastState (button_t *button, uint8_t lastButState);


/*==================[cplusplus]==============================================*/

#ifdef __cplusplus
}
#endif

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _HW_BUTTONS_H_ */

