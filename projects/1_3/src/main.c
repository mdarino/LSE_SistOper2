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

#define TIME_UPDATE_BUTTON  10  //every 10 msec i will control the button

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

   /* init CIAA kernel and devices */
   SetRelAlarm(ActivatePeriodicTask, 0, TIME_UPDATE_BUTTON);

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
   static int32_t  timeButton=0;
   static uint32_t timePress=0;  //in mseg

   static button_t button1;
   //Init task - only one time
   if(flagInit==0)
   {
      //button1 CIAA
      buttonConstructor(&button1,0,4);
      buttonInitWithoutPullUp(&button1,1,0,FUNC0);
      flagInit=1;
   } 

   
   buttonUpdate(&button1);

   if (buttonGetState(&button1)==PRESS)
   {
      timeButton=buttonGetTime(&button1);
   }
   else
   {
      if(timeButton!=0)
         timePress=timeButton;
      timeButton=0;
   }

   
   //LED TASK -- Turn on the LED if his time is positive
   if (timePress>0)
   {
      timePress--;
      led_SetON(LED_1);
   }
   else
   {
      led_SetOFF(LED_1);
   }

   //--------TEST THE BUTTON ----------//
         // buttonUpdate(&button1);
         //    if (buttonGetState(&button1)==PRESS)
         //    {
         //       led_SetON(LED_1);
         //    }
         //    else
         //    {
         //       led_SetOFF(LED_1);
         //    }



   /* terminate task */
   TerminateTask();
}

/** @} doxygen end group definition */


///EXAMPLES:
///
///  button1 CIAA
  
  // buttonConstructor(&buttonEnter,0,4);
  // buttonInitWithoutPullUp(&buttonEnter,1,0,FUNC0);
  
  // //button2

  // buttonConstructor(&buttonUp,0,8);
  // buttonInitWithoutPullUp(&buttonUp,1,1,FUNC0);
 
  // //button3

  // buttonConstructor(&buttonDown,0,9);
  // buttonInitWithoutPullUp(&buttonDown,1,2,FUNC0);
  
  // //button4

  // buttonConstructor(&buttonBack,1,9);
  // buttonInitWithoutPullUp(&buttonBack,1,6,FUNC0);



/*==================[end of file]============================================*/

