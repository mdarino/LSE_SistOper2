

/*************************************************************************//**

  @file     main.c

  @brief    EJERCICIO 2.1 - RTOS 2 OSEK

  @author   Marcos Darino (MD)

 ******************************************************************************/


/**

 EJERCICIO 2.1    (Spanish)

Caso   de   uso​
:   Una   tarea   consumidora   está   bloqueada   esperando   
recibir   un   semáforo,   mientras   que  
una tarea generadora lo liberara cuando genere o descubra un dato. 
 
Ejercicio​
:   Implementar   una   tarea   que   mida   un   pulsador,   
y   libere   un   semáforo   cuando   confirme   el   fin  
de   la   pulsación.   Implementar   otra   tarea   que   
destelle   un   leds   cuando   recibe   el   semáforo.   
Esta   última  esperará al semáforo indefinidamente. 

 **/




/** \addtogroup OSEK_RTOS Ejer1.4
 ** @{ */
/*==================[inclusions]=============================================*/
//#include "ciaaPOSIX_stdio.h"  /* <= device handler header */
//#include "ciaaPOSIX_string.h" /* <= string header */
//#include "ciaak.h"            /* <= ciaa kernel header */
#include "main.h"         /* <= own header */
#include "HW_leds.h"
#include "HW_buttons.h"
#include "ciaaIO.h"
#include "os.h"               /* <= operating system header */

/*==================[macros and definitions]=================================*/

#define TIME_UPDATE_BUTTON  10  //every 10 msec i will control the button

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/


static button_t button1;

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
   /* Starts the operating system in the Application Mode 1 */
   /* This example has only one Application Mode */
   StartOS(AppMode1);

   /* StartOs shall never returns, but to avoid compiler warnings or errors
    * 0 is returned */
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
   
   //button1 CIAA
   buttonConstructor(&button1,0,4);
   buttonInitWithoutPullUp(&button1,1,0,FUNC0);

   /* activate periodic task:
    *  - for the first time after 350 ticks (350 ms)
    *  - and then every TIME_UPDATE_BUTTON ticks (10 ms)
    */
   
   //Start the Button task
   SetRelAlarm(ActivateButtonTask, 350, TIME_UPDATE_BUTTON);
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
  

   //Update the button struct
   buttonUpdate(&button1);

   
   //Only to check if the button is press
   //If it is press turn on the led 2
   if (buttonGetState(&button1)==PRESS)
   {
     led_SetON(LED_2);
   }
   else
   {
     led_SetOFF(LED_2);
   }


   //Check the last state -- and ask the time in the new state
   // if the time is less or equal to zero -> the button change his state
   //the next time, the time in the new state is bigger than zero

   if (buttonGetLastState(&button1)==PRESS && buttonGetTime(&button1)<=0)
   {
      //if the button was pressed and release
      //send the event to unblock the blink task
      SetEvent(LedTask,evBoton);
   }


  /* terminate task */
   TerminateTask();
}


/** \brief button Task
 *
 * This task is started only when receive an event of the button realese
 */
 
TASK(LedTask)
{

   //turn off the led and wait
   led_SetOFF(LED_1);  
   //waiting
   WaitEvent(evBoton);
   //clean the event
   ClearEvent(evBoton);
   //turn on the led to make a blink
   led_SetON(LED_1);
   //set a delay with other event - the time is fixed to one second
   // if you want the button time, we can use a global variable
   SetRelAlarm(AlarmTimeButton, 1000, 0);
   //waiting the time...
   WaitEvent(evTimeButton);
   //clean the event
   ClearEvent(evTimeButton);
   //Start again the task
   ChainTask(LedTask);
}


/** @} doxygen end group definition */

/*==================[end of file]============================================*/


  

