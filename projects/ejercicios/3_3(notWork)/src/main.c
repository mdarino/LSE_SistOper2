

/*************************************************************************//**

  @file     main.c

  @brief    EJERCICIO 3.3 - RTOS 2 OSEK

  @author   Marcos Darino (MD)

 ******************************************************************************/




/**

 EJERCICIO 3.3  (Spanish)

Caso de uso: Los mensajes a enviar por cola son demasiado grandes para pasar por copia (por
ejemplo, un buffer a ser transmitido por puerto serie). Se pasa entonces por cola la dirección de los
datos a procesar, pero en este caso debe asegurar el programador que los mismos se mantienen
válidos hasta que el destinatario los recibe. Para esto se usa memoria global, y según el caso debe
señalizarse la validez del mensaje (p. ej., mediante flags o variables de estado).

Ejercicio: Repetir la tarea del ejemplo anterior, pero en vez de pasar el data por cola, pasar la
dirección del mismo. Recuerde usar variables globales para mantener válido el dato cuando la tarea
sale de contexto.
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

static uint32_t timeButtonGlobal;

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
   SetRelAlarm(ActivateButtonTask, 100, TIME_UPDATE_BUTTON);
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
  
   static uint32_t timeButton;
   buttonUpdate(&button1);
   static int *timePointer;
   static timePointer=&timeButtonGlobal;
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
         timeButtonGlobal=buttonGetLastTime(&button1);
         
         //Send the data to queue
         queuePut(&cola, &timePointer);
      }
    }  

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
  int *timeButtonPress;
  uint32_t test;
  // //set off the led
  led_SetOFF(LED_3);

  // //Wainting the data from the queue
  timeButtonPress = queueGet(&cola);
  test=*timeButtonPress;
  // //Set on the led and wait the time
  led_SetON(LED_3);

  if(timeButtonPress<10)
    timeButtonPress=10;
  //Start the Button task
  SetRelAlarm(ActivateLedTask, *timeButtonPress,0);

  /* terminate task */
   TerminateTask();
   
}


/** @} doxygen end group definition */

/*==================[end of file]============================================*/


  

