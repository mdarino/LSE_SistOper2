/*************************************************************************//**

  @file     main.c

  @brief    EJERCICIO 1.3 - RTOS 2 OSEK

  @author   Marcos Darino (MD)

 ******************************************************************************/


/**

 EJERCICIO 1.3    (Spanish)

    Medir   el   tiempo   de   pulsación   de   un   botón   utilizando   
    un   algoritmos   anti­rebote.   Luego  destellar un led durante 
    el tiempo medido. 

 **/




/** \addtogroup rtos FreeRTOS Ejer1.3
 ** @{ */


/*==================[inclusions]=============================================*/
#include "main.h"       /* <= own header */
#include "os.h"               /* <= operating system header */
#include "HW_leds.h"
#include "HW_buttons.h"


#ifndef CPU
#define CPU lpc4337
#endif


#ifndef CPU
#error CPU shall be defined
#endif
#if (lpc4337 == CPU)
#include "chip.h"
#elif (mk60fx512vlq15 == CPU)
#else
#endif


/*==================[macros and definitions]=================================*/

#define TIME_UPDATE_UART  1000  //every 10 msec i will control the button

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/
uint8_t test=0;


int main(void)
{
   /* perform the needed initialization here */
  StartOS(AppMode1);

  
   return 0;
}


void ErrorHook(void)
{
  
   ShutdownOS(0);
}

/** \brief Initial task
 *
 * This task is started automatically in the application mode 1.
 */
TASK(InitTask)
{
   led_Init();


  //INIT UART POR USB
   Chip_UART_Init(LPC_USART2);
   Chip_UART_SetBaud(LPC_USART2, 115200);

   Chip_UART_SetupFIFOS(LPC_USART2, UART_FCR_FIFO_EN | UART_FCR_TRG_LEV0);

   Chip_UART_TXEnable(LPC_USART2);

   Chip_SCU_PinMux(7, 1, MD_PDN, FUNC6);              /* P7_1: UART2_TXD */
   Chip_SCU_PinMux(7, 2, MD_PLN|MD_EZI|MD_ZI, FUNC6); /* P7_2: UART2_RXD */



   /* init CIAA kernel and devices */
   SetRelAlarm(ActivatePeriodicTask, 0, TIME_UPDATE_UART);

   /* terminate task */
   TerminateTask();
}

/** \brief Periodic Task
 *
 * This task is started automatically every time that the alarm
 * ActivatePeriodicTask expires.
 *
 */
TASK(PeriodicTask)
{

   char out[7];
   strcpy(out,"TESTS:\n");
   Chip_UART_SendBlocking((LPC_USART_T *)LPC_USART2,&out,sizeof(out));
   /* terminate task */
   TerminateTask();
}

/** @} doxygen end group definition */


/*==================[end of file]============================================*/

