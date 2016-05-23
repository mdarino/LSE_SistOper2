/*************************************************************************//**

  @file     delay.c

  @brief    Software Library to make delay with the timer 1 

  @author   Marcos Darino (MD)

 ******************************************************************************/

#include "delay.h"

void delay_init(void){
      ciaaTIMER1Init();
}

void delay_us(uint32_t usec){
   ciaaTIMER1Set(usec);
   WaitEvent(evTIMER1);
   ClearEvent(evTIMER1);   
   ciaaTIMER1Disable();

}

void delay_ms(uint32_t msec){
   ciaaTIMER1Set(msec*1000);
   WaitEvent(evTIMER1);
   ClearEvent(evTIMER1);   
   ciaaTIMER1Disable();
}


void delay_setEvent(void){
   TaskType   task;      /**< waiting task */

   if (ciaaTIMER1Match(0)) {
         GetTaskID(&task);
         SetEvent(LedTask,evTIMER1); 
   }
   ciaaTIMER1ClearMatch(0);

}