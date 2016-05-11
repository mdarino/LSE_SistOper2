/*******************************************************************************
              Copyright 2015 Arimex Importadora SA, All Rights Reserved
 *******************************************************************************
 ***************************************************************************/

#ifndef _DRIVER_GPIO_H_
#define _DRIVER_GPIO_H_
/** @brief Brief for this header file.
 **
 ** Control the GPIO ports and PIN configurations. 
 ** It uses the LPCOPEN's librarys
 **
 **/

/** \addtogroup DRIVER GPIO 
 ** @{ */

/*
 * Initials    Name
 * ---------------------------
 * MD          MARCOS DARINO
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * 20151109 v0.0.1   MD:Initial release.
 */

/*==================[inclusions]=============================================*/
#include "chip.h"

/*==================[cplusplus]==============================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*==================[macros]=================================================*/

/*==================[typedef]================================================*/
typedef struct
{
    int gpio;
    int bit;
} gpioPin_t;
/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/


/**
 * @brief Set GPIO direction for a single GPIO pin to an input
 * @param port  : GPIO Port number where @a pin is located
 * @param pin   : GPIO pin to set direction on as input
 * @return  Nothing
 */
void GPIO_setAsInput(uint8_t port, uint8_t pin);

/**
 * @brief Set GPIO direction for a single GPIO pin to an output
 * @param port  : GPIO Port number where @a pin is located
 * @param pin   : GPIO pin to set direction on as output
 * @return  Nothing
 */
void GPIO_setAsOutput(uint8_t port, uint8_t pin);

/**
 * @brief Set a GPIO pin state via the GPIO byte register
 * @param port  : GPIO Port number where @a pin is located
 * @param pin   : GPIO pin to set
 * @return  Nothing
 */
void GPIO_setON(uint32_t port, uint32_t pin);

/**
 * @brief Set a GPIO port/bit to the low state
 * @param port   : port number
 * @param pin  : pin in the port to set low
 * @return  None
 * @note  Any bit set as a '0' will not have it's state changed. This only
 * applies to ports configured as an output.
 */
void GPIO_SetOFF(uint32_t port, uint32_t pin);



/**
 * @brief Toggle a GPIO port/bit
 * @param port   : port number
 * @param pin  : pin in the port to set low
 * @return  None
 * @note  Toggle the state of the pin. This only
 * applies to ports configured as an output.
 */
void GPIO_Toggle(uint32_t port, uint32_t pin);


/**
 * @brief Set a GPIO port/bit to the low state
 * @param port   : port number
 * @param pin  : pin in the port to set low
 * @param value  : FALSE 0  - TRUE other 
 * @return  None
 * @note  Any bit set as a '0' will not have it's state changed. This only
 * applies to ports configured as an output.
 */
void GPIO_setValue(uint32_t port, uint32_t pin, uint32_t value);

/**
 * @brief Sets I/O Control pin mux (see scu_18xx_43xx.h)
 * @param port    : Port number, should be: 0..15
 * @param pin     : Pin number, should be: 0..31
 * @param modefunc  : OR'ed values or type SCU_MODE_*
 * @return  Nothing
 * @note  Do not use for clock pins (SFSCLK0 .. SFSCLK4). Use
 * Chip_SCU_ClockPinMux() function for SFSCLKx clock pins.
 */
INLINE void GPIO_pinConfiguration(uint8_t port, uint8_t pin, uint16_t mode, uint8_t func);


/**
 * @brief Read a GPIO state
 * @param port  : GPIO port to read
 * @param pin   : GPIO pin to read
 * @return  true of the GPIO is high, false if low
 */
bool GPIO_getValue(uint8_t port, uint8_t pin);




/*==================[cplusplus]==============================================*/

#ifdef __cplusplus
}
#endif

/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _DRIVER_GPIO_H_ */

