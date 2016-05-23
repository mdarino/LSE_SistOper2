/*************************************************************************//**

  @file     delay.h

  @brief    Software Library to make delay with the timer 1 

  @author   Marcos Darino (MD)

 ******************************************************************************/


#ifndef DELAY_H_
#define DELAY_H_

#include "ciaaTIMER.h"
#include "os.h"


void delay_init(void);
void delay_us(uint32_t usec);
void delay_ms(uint32_t usec);
void delay_setEvent(void);

#endif /* DELAY_H_ */
