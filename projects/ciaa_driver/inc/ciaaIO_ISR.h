


#include "chip.h"

#ifndef CIAAIOISR_H_
#define CIAAIOISR_H_

   void ciaaIO_ISR_Init(void);
   void ciaaIO_ISR_SetButton1(uint8_t LowOrHigh);
   void ciaaIO_ISR_SetButton2(uint8_t LowOrHigh);
   void ciaaIO_ISR_SetButton3(uint8_t LowOrHigh);
   void ciaaIO_ISR_SetButton4(uint8_t LowOrHigh);

#endif /* CIAATIMER_H_ */