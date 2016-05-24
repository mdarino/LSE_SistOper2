/*************************************************************************//**

  @file     ciaaIO_ISR.c

  @brief    IO ISR library

  @author   Marcos Darino (MD)

 ******************************************************************************/




    
#include "ciaaIO_ISR.h"


    void ciaaIO_ISR_Init(void)
    {
      Chip_PININT_Init(LPC_GPIO_PIN_INT);
    }

   //BOTON 1
   // 0 Low - 1 High
   void ciaaIO_ISR_SetButton1(uint8_t LowOrHigh)
   {
      //Set GPIO0[4] 
      Chip_SCU_GPIOIntPinSel(0,0,4);
      Chip_PININT_SetPinModeEdge(LPC_GPIO_PIN_INT,PININTCH0); 
      if (LowOrHigh)
      {
         Chip_PININT_EnableIntHigh(LPC_GPIO_PIN_INT,PININTCH0);
      }
      else
      {
         Chip_PININT_EnableIntLow(LPC_GPIO_PIN_INT,PININTCH0);  
      }
      
      //habilitar la IRQ
      NVIC_EnableIRQ(PIN_INT0_IRQn);

   }


   //BOTON 2
   // 0 Low - 1 High
   void ciaaIO_ISR_SetButton2(uint8_t LowOrHigh)
   {
      //Set GPIO0[8] 
      Chip_SCU_GPIOIntPinSel(1,0,8);
      Chip_PININT_SetPinModeEdge(LPC_GPIO_PIN_INT,PININTCH1); 
      if (LowOrHigh)
      {
         Chip_PININT_EnableIntHigh(LPC_GPIO_PIN_INT,PININTCH1);
      }
      else
      {
         Chip_PININT_EnableIntLow(LPC_GPIO_PIN_INT,PININTCH1);  
      }
      
      //habilitar la IRQ
      NVIC_EnableIRQ(PIN_INT1_IRQn);

   }



   //BOTON 3
   // 0 Low - 1 High
   void ciaaIO_ISR_SetButton3(uint8_t LowOrHigh)
   {
      //Set GPIO0[9] 
      Chip_SCU_GPIOIntPinSel(2,0,9);
      Chip_PININT_SetPinModeEdge(LPC_GPIO_PIN_INT,PININTCH2); 
      if (LowOrHigh)
      {
         Chip_PININT_EnableIntHigh(LPC_GPIO_PIN_INT,PININTCH2);
      }
      else
      {
         Chip_PININT_EnableIntLow(LPC_GPIO_PIN_INT,PININTCH2);  
      }
      
      //habilitar la IRQ
      NVIC_EnableIRQ(PIN_INT2_IRQn);

   }


   //BOTON 4
   // 0 Low - 1 High
   void ciaaIO_ISR_SetButton4(uint8_t LowOrHigh)
   {
      //Set GPIO1[9] 
      Chip_SCU_GPIOIntPinSel(3,1,9);
      Chip_PININT_SetPinModeEdge(LPC_GPIO_PIN_INT,PININTCH3); 
      if (LowOrHigh)
      {
         Chip_PININT_EnableIntHigh(LPC_GPIO_PIN_INT,PININTCH3);
      }
      else
      {
         Chip_PININT_EnableIntLow(LPC_GPIO_PIN_INT,PININTCH3);  
      }
      
      //habilitar la IRQ
      NVIC_EnableIRQ(PIN_INT3_IRQn);

   }   