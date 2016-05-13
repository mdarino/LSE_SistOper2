

/*************************************************************************//**

  @file     main.c

  @brief    EJERCICIO 3.3 - RTOS 2 OSEK

  @author   Marcos Darino (MD)

 ******************************************************************************/


/**

 EJERCICIO 3.3    (Spanish)

Este   es   el   uso   más   simple   de   las   colas   del   RTOS:   Los   mensajes   se   pasan   por   copia   dentro   de   la  
cola, dándole persistencia a los mismos una vez que la tarea productora sale de contexto. 
 
Caso de uso​
: Una tarea manejadora de evento bloquea hasta recibir el mismo. 
 
Ejercicio​
:   Una   tarea   mide   el   tiempo   de   opresión   de   un   pulsador.   Cuando   lo   obtiene   lo   envía   par   cola   a  
otra tarea que destella un led durante el tiempo recibido. 

 **/





/** \addtogroup OSEK_RTOS Ejer3.3
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

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/


static button_t button1;
static queue_t cola;

uint32_t  timeGlobal;

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

   queueInit(&cola, evCola);

   //button1 CIAA
   buttonConstructor(&button1,0,4);
   buttonInitWithoutPullUp(&button1,1,0,FUNC0);

   /* activate periodic task:
    *  - for the first time after 350 ticks (350 ms)
    *  - and then every TIME_UPDATE_BUTTON ticks (10 ms)
    */
   
   //Start the Button task
   SetRelAlarm(ActivateButtonTask, 100,0);
   //Start the LED task
   SetRelAlarm(ActivateLedTask, 150,0);
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
  //queueItem_t
   static uint32_t timeButton;
   queueItem_t punteroEnviado;
   punteroEnviado=&timeGlobal;


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


   //Check the last state
   if (buttonGetLastState(&button1)==PRESS)
   {
      //if the last state is press, check the time
      if (buttonGetLastTime(&button1)>0 && buttonGetLastTime(&button1)!=timeButton)
      {
         //if the time is >0 and diferent (only will be diferent if press again)
         //get the time
         timeButton=buttonGetLastTime(&button1);
         timeGlobal=timeButton;

         //Send the data to queue
         queuePut(&cola, punteroEnviado);
      }
    }  

   SetRelAlarm(ActivateButtonTask, TIME_UPDATE_BUTTON,0);
   /* terminate task */
   TerminateTask();
}



/** \brief LED Task
 *
 * This task wait the data from the button, when receive it blick the led 3
 */
 
TASK(LedTask)
{
  //local variable to receive the timebutton
  static uint32_t timeButtonPress=0;
  queueItem_t punteroRecibido;


  // //set off the led
  led_SetOFF(LED_3);

  // //Wainting the data from the queue
  punteroRecibido = queueGet(&cola);
  timeButtonPress=*punteroRecibido;
  // //Set on the led and wait the time
  led_SetON(LED_3);

  if(timeButtonPress<10)
    timeButtonPress=10;
  //Start the Button task
  SetRelAlarm(ActivateLedTask, timeButtonPress,0);

  /* terminate task */
   TerminateTask();
   
}


/** @} doxygen end group definition */

/*==================[end of file]============================================*/


  

