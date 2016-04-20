/*************************************************************************//**

  @file     main.c

  @brief    EJERCICIO 1.4 - RTOS 2 OSEK

  @author   Marcos Darino (MD)

 ******************************************************************************/


/**

 EJERCICIO 1.4    (Spanish)

 Escribir un programa con dos tareas: 
 
  ∙ Una tarea medirá el tiempo de pulsación de un botón, aplicando anti­rebote. 
  ∙ La   otra   destellará   un   led   con   un   período   fijo   de   1   seg,   
  y tomando   como   tiempo   de   activación  
    el último tiempo medido. 
 
 El   tiempo   medido   se   puede   comunicar   entre   
 tareas   a   través   de   una   variable   global,   protegiendo   sus  
 operaciones dentro de una sección crítica. 


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
#include "os.h"               /* <= operating system header */

/*==================[macros and definitions]=================================*/

#define TIME_UPDATE_BUTTON  10  //every 10 msec i will control the button

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/** \brief File descriptor for digital output ports
 *
 * Device path /dev/dio/out/0
 */
//static int32_t fd_out;

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

   /* print message (only on x86) */
   //ciaaPOSIX_printf("Init Task...\n");

   /* open CIAA digital outputs */
   //fd_out = ciaaPOSIX_open("/dev/dio/out/0", ciaaPOSIX_O_RDWR);

   /* activate periodic task:
    *  - for the first time after 350 ticks (350 ms)
    *  - and then every TIME_UPDATE_BUTTON ticks (10 ms)
    */
   
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
  
   static uint32_t timeButton;
   static uint32_t lastTimeButton;
   static uint32_t flag=0;
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
      if (buttonGetLastTime(&button1)>0 && buttonGetLastTime(&button1)!=lastTimeButton)
      {
         //if the time is >0 and diferent (only will be diferent if press again)
         //get the time
         timeButton=buttonGetLastTime(&button1);
         //Save this time
         lastTimeButton=timeButton;
         //turn on the led 3
         led_SetON(LED_3);
         //Activate the LedTask
         
         //timeButton=100;
         // TickType Ticks;

         
         // CancelAlarm(ActivateLedTask);
         
         // SetRelAlarm(ActivateLedTask, 100, (uint16_t)timeButton);
       

            TickType Ticks;
            StatusType ret;
            ret = GetAlarm(ActivateLedTask,&Ticks); 
            
            if (Ticks<0)
            {
              CancelAlarm(ActivateLedTask);
              SetRelAlarm(ActivateLedTask,0, 100); 
            }
            else
            {
              SetRelAlarm(ActivateLedTask,500, 500);
            }



      }
      else
      {
         //check if timebutton is >0
         if (timeButton<=0)
         {
            //if it is <=0 turn off the led, the blick time has passed
            led_SetOFF(LED_3);
         }
         else
         {
            //subtract one block of time
            timeButton-=TIME_UPDATE_BUTTON;   
         }   
      }    

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

   led_SetToggle(LED_1);
   /* terminate task */
   TerminateTask();
}


/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

