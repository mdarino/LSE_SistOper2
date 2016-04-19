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
#include "string.h"
#include <stdlib.h>

//#include "../../../modules/ciaa/inc/ciaaUART.h"
//#include "../../../modules/ciaa/inc/ciaaIO.h"

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

#define TIME_UPDATE_UART  10  //every 10 msec i will control the button

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/



/* reverse:  reverse string s in place */
void reverse(char s[])
{
    int c, i, j;

    for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

/* itoa:  convert n to characters in s */
void itoa(int n, char s[])
{
    int i, sign;

    if ((sign = n) <0)  /* record sign */
        n = -n;          /* make n positive */
    i = 0;
    do {       /* generate digits in reverse order */
        s[i++] = n % 10 + '0';   /* get next digit */
    } while ((n /= 10) > 0);     /* delete it */
    if (sign<0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}



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
  
    //ciaaIOInit();
    //ciaaUARTInit();

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
   static uint8_t  flagInit=0;
   static button_t button1;
   static int16_t timeButton;
   static int16_t newTimeButton;
   static int16_t uartTime=0;
   char str[15]; //the max number is 65536
 
   //Init task - only one time
   if(flagInit==0)
   {
      //button1 CIAA
      buttonConstructor(&button1,0,4);
      buttonInitWithoutPullUp(&button1,1,0,FUNC0);
      flagInit=1;
   } 
   
   buttonUpdate(&button1);
   led_SetToggle(LED_1);

   newTimeButton=buttonGetTime(&button1);
   
   if(buttonGetState(&button1)==PRESS)
   {
      led_SetON(LED_2);
   }
   else
   {
      led_SetOFF(LED_2);
   }

   uartTime++;
   if (uartTime>100)
   {
       uartTime=0;
       timeButton=newTimeButton;
       
       newTimeButton=buttonGetLastTime(&button1);  //reutilizo la variable

       strcpy(str,"\nTIME PRESS=       ");
       Chip_UART_SendBlocking((LPC_USART_T *)LPC_USART2,&str,sizeof(str));
       strcpy(str,"                    ");
       itoa(timeButton,str);
       Chip_UART_SendBlocking((LPC_USART_T *)LPC_USART2,&str,sizeof(str));

       strcpy(str,"\nLAST TIME=        ");
       Chip_UART_SendBlocking((LPC_USART_T *)LPC_USART2,&str,sizeof(str));
       strcpy(str,"                    ");
       itoa(newTimeButton,str);
       Chip_UART_SendBlocking((LPC_USART_T *)LPC_USART2,&str,sizeof(str));


   }

   /* terminate task */
   TerminateTask();
}

/** @} doxygen end group definition */


/*==================[end of file]============================================*/

