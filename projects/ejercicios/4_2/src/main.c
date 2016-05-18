

/*************************************************************************//**

  @file     main.c

  @brief    EJERCICIO 4.1 - RTOS 2 OSEK

  @author   Marcos Darino (MD)

 ******************************************************************************/


/**

 EJERCICIO 4.1  (Spanish)

Caso de uso: Sincronizar la generación de un evento con su consumidor, cuando la generación del
evento es más rápida que su manejo (se acumulan eventos).
Ejercicio: Repetir el ejercicio (semáforo binario), pero agregue la posibilidad de que se contabilicen
hasta 3 pulsaciones del botón, que a su vez generarán 3 destellos del led.

 **/




/** \addtogroup OSEK_RTOS Ejer4.1
 ** @{ */
/*==================[inclusions]=============================================*/
//#include "ciaaPOSIX_stdio.h"  /* <= device handler header */
//#include "ciaaPOSIX_string.h" /* <= string header */
//#include "ciaak.h"            /* <= ciaa kernel header */
#include "main.h"         /* <= own header */
#include "HW_leds.h"
#include "HW_buttons.h"
#include "queue.h"
#include "ciaaIO.h"
#include "os.h"               /* <= operating system header */

/*==================[macros and definitions]=================================*/

#define TIME_UPDATE_BUTTON  10  //every 10 msec i will control the button


#define NUM_PRESS_LED 3  //how many press we will wait (WARNING: the queue have to storage the same quantity +1)

/*==================[internal data declaration]==============================*/

static uint32_t tiempoBlinkLED_ms;

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/


static button_t button1;
static queue_t cola;

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/
/** \brief Main function
 *
 * This is the main entry point of the software.
 *
 * \returns 0
 *
 * \remarks This function never returns. Return value is only to avoid compiler
 *          warnings or errors.
 */
int main(void)
{
   StartOS(AppMode1);
   return 0;
}

/** \brief Error Hook function
 *
 * This fucntion is called from the os if an os interface (API) returns an
 * error. Is for debugging proposes. If called this function triggers a
 * ShutdownOs which ends in a while(1).
 *
 * The values:
 *    OSErrorGetServiceId
 *    OSErrorGetParam1
 *    OSErrorGetParam2
 *    OSErrorGetParam3
 *    OSErrorGetRet
 *
 * will provide you the interface, the input parameters and the returned value.
 * For more details see the OSEK specification:
 * http://portal.osek-vdx.org/files/pdf/specs/os223.pdf
 *
 */
void ErrorHook(void)
{
   led_SetON(LED_1);
   led_SetON(LED_2);
   led_SetON(LED_3);
   ShutdownOS(0);
}

/** \brief Initial task
 *
 * This task is started automatically in the application mode 1.
 */
TASK(InitTask)
{
   /* init CIAA kernel and devices */
   
   
   //ciaak_start();
   ciaaIOInit();
   led_Init();

   queueInit(&cola);

   //button1 CIAA
   buttonConstructor(&button1,0,4);
   buttonInitWithoutPullUp(&button1,1,0,FUNC0);

   /* activate periodic task:
    *  - for the first time after 350 ticks (350 ms)
    *  - and then every TIME_UPDATE_BUTTON ticks (10 ms)
    */
   
   //Start the Button task
   SetRelAlarm(ActivateButtonTask, 100, 0);
   //Start the LED task
   SetRelAlarm(ActivateLedTaskBlink, 150,0);
   //Start the LED task
   SetRelAlarm(ActivateLedTaskButton, 200,0);
   /* terminate task */
   TerminateTask();
}

/** \brief button Task
 *
 * This task is started automatically every time that the alarm
 * ActivateButtonTask expires.
 *
 */
TASK(ButtonTask)
{
  
   static uint32_t timeButton;
   buttonUpdate(&button1);
   //static uint8_t countPress=0;

   queueItem_t dataTest;

   //dataTest.data=100;
   
   //Only to check if the button is press
   //If it is press turn on the led 2
   if (buttonGetState(&button1)==PRESS)
   {
     led_SetON(LED_RED);
   }
   else
   {
     led_SetOFF(LED_RED);
   }


   //Check the last state
   if (buttonGetLastState(&button1)==PRESS)
   {
      //if the last state is press, check the time
      if (buttonGetLastTime(&button1)>0 && buttonGetLastTime(&button1)!=timeButton)
      {
         //if the time is >0 and diferent (only will be diferent if press again)
         //get the time
         timeButton=buttonGetLastTime(&button1);
         dataTest.data=timeButton;
         //Send the data to queue
         queuePut(&cola, &dataTest,10); //if it is full wait 10mseg and unblock
      }
    }  

   SetRelAlarm(ActivateButtonTask, TIME_UPDATE_BUTTON,0);
   /* terminate task */
   TerminateTask();
}



/** \brief LED Task
 *
 * This task blink the led
 */
 
TASK(LedTaskBlink)
{
  
  tiempoBlinkLED_ms = 500; 
  GetResource(LedGreen);
  led_SetON(LED_3);
  led_SetON(LED_1); //debug
  while(tiempoBlinkLED_ms);
  ReleaseResource(LedGreen);

  SetRelAlarm(ActivateLedTaskBlink, 500,0);
  led_SetOFF(LED_3);
  led_SetOFF(LED_1); //debug
  TerminateTask();
}



/** \brief LED Task
 *
 * This task wait the data from the button, when receive it blick the led 3
 */
 

TASK(LedTaskButton)
{
 
  queueItem_t dataRXTest;
  //waiting the data
  queueGet(&cola,&dataRXTest,0);
  //Set the min time
  if(dataRXTest.data<10)
    dataRXTest.data=10;
    
  GetResource(LedGreen);

  tiempoBlinkLED_ms = 20;
  while(tiempoBlinkLED_ms);

  tiempoBlinkLED_ms = dataRXTest.data; 
  led_SetON(LED_2); //debug
  led_SetON(LED_3);
  while(tiempoBlinkLED_ms);
  
  led_SetOFF(LED_3);
  led_SetOFF(LED_2); //debug
  
  tiempoBlinkLED_ms = 20;
  while(tiempoBlinkLED_ms);

  ReleaseResource(LedGreen);

  
  ChainTask(LedTaskButton);
   
}



/* TickHook de 1ms */
ALARMCALLBACK(TickHook)
{
  if(tiempoBlinkLED_ms)
    tiempoBlinkLED_ms--;
}


/** @} doxygen end group definition */

/*==================[end of file]============================================*/


  

