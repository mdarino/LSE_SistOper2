
    
#include "ciaaIO_ISR.h"


    void ciaaIO_ISR_Init(void)
    {
      Chip_PININT_Init(LPC_GPIO_PIN_INT);
    }

   //BOTON 1
   // 0 Low - 1 High
   void ciaaIO_ISR_SetButton1(uint8_t LowOrHigh)
   {
      //Set GPIO0[4] (SW0) -> GPIO0_IRQHandler
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




    // //Set GPIO0[4] (SW0) -> GPIO0_IRQHandler
    // Chip_SCU_GPIOIntPinSel(0,0,4);
    // //falling edge IRQ 
    // Chip_PININT_SetPinModeEdge(LPC_GPIO_PIN_INT,PININTCH0);
    // Chip_PININT_EnableIntLow(LPC_GPIO_PIN_INT,PININTCH0);

    // //habilitar la IRQ
    // NVIC_EnableIRQ(PIN_INT0_IRQn);

    // //BOTON 2

    // //Set GPIO1[9] (SW3) ->
    // //Int number - GPIO number - PIN GPIO number
    // Chip_SCU_GPIOIntPinSel(1,1,9);

    // //falling edge IRQ 
    // Chip_PININT_SetPinModeEdge(LPC_GPIO_PIN_INT,PININTCH1);
    // Chip_PININT_EnableIntLow(LPC_GPIO_PIN_INT,PININTCH1);

    // //habilitar la IRQ
    // NVIC_EnableIRQ(PIN_INT1_IRQn);


    // //Chip_PININT_EnableIntHigh
