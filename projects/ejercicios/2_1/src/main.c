

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
   //ciaaPOSIX_printf("ErrorHook was called\n");
   //ciaaPOSIX_printf("Service: %d, P1: %d, P2: %d, P3: %d, RET: %d\n", OSErrorGetServiceId(), OSErrorGetParam1(), OSErrorGetParam2(), OSErrorGetParam3(), OSErrorGetRet());
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
   //Set defaul time
   SetRelAlarm(ActivateLedTask,100, 0); 
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
      //if the button was pressed and release
      //send the event
      
      SetEvent(LedTask,evBoton);

   }
   



   /* terminate task */
   TerminateTask();
}


/** \brief button Task
 *
 * This task is started automatically every time that the alarm
 * ActivateLedTask expires.
 *
 */
TASK(LedTask)
{
   TickType Ticks;
   StatusType ret;

   led_SetOFF(LED_1);  //waiting
   //SetEvent(LedTask,evBoton);
   WaitEvent(evBoton);
   ClearEvent(evBoton);

   //CancelAlarm(ActivateLedTask);
   //SetRelAlarm(ActivateLedTask, 250, 0); //led blick one time (250mseg ON)
        
         //Check the state of the alarm
        // ret = GetAlarm(ActivateLedTask,&Ticks); 
        // if (E_OK == ret)
        // {
        //     //if it is ok, update the time
        //     //to do this, first stop and then update
        //     CancelAlarm(ActivateLedTask);
        //     SetRelAlarm(ActivateLedTask,0, 250); 
        // }  
        // 

        //  //Check the state of the alarm


   led_SetON(LED_1);
   /* Chain task */
        // ret = GetAlarm(ActivateLedTask,&Ticks); 
        // if (E_OK == ret)
        // {
        //     //if it is ok, update the time
        //     //to do this, first stop and then update
        //     CancelAlarm(ActivateLedTask);
        //     SetRelAlarm(ActivateLedTask,1000, 0); 
        // }
        // else if (E_OS_NOFUNC == ret)
        // {
        //   //set defaul time
        //   SetRelAlarm(ActivateLedTask,1000, 0); 
        // }


   SetRelAlarm(ActivateLedTask,1000, 0);     
   TerminateTask();
   //ChainTask(LedTask);
}


/** @} doxygen end group definition */

/*==================[end of file]============================================*/

