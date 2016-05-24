

/*************************************************************************//**

  @file     main.c

  @brief    EJERCICIO PIN ISR - RTOS 2 OSEK

  @author   Marcos Darino (MD)

 ******************************************************************************/



/** \addtogroup OSEK_RTOS PIN_ISR
 ** @{ */
/*==================[inclusions]=============================================*/
//#include "ciaaPOSIX_stdio.h"  /* <= device handler header */
//#include "ciaaPOSIX_string.h" /* <= string header */
//#include "ciaak.h"            /* <= ciaa kernel header */
#include "main.h"         /* <= own header */
#include "HW_leds.h"
#include "HW_buttons.h"
#include "ciaaIO.h"
  #include "queue.h"
#include "ciaaIO_ISR.h"
#include "os.h"               /* <= operating system header */

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

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
   ciaaIO_ISR_Init();
   led_Init();

   queueInit(&cola);

   /* activate periodic task:
    *  - for the first time after 350 ticks (350 ms)
    *  - and then every TIME_UPDATE_BUTTON ticks (10 ms)
    */
   ciaaIO_ISR_SetButton1(0);

   ActivateTask(LedTask);  
   /* terminate task */
   TerminateTask();
}



/** \brief LED Task
 *
 * This task wait the data from the button, when receive it blick the led 3
 */
 
TASK(LedTask)
{
  queueItem_t dataRXTest;
  led_SetOFF(LED_3);

  queueGet(&cola,&dataRXTest,0);

  led_SetON(LED_3);

  SetRelAlarm(AlarmLedTimeEvent, dataRXTest.data, 0);
  //Waiting the time...
  WaitEvent(evTime);
  //Clean the event
  ClearEvent(evTime);

  ChainTask(LedTask);
   
}


ISR(GPIO0_IRQ)
{
      queueItem_t dataTest;
      Chip_PININT_ClearIntStatus(LPC_GPIO_PIN_INT,PININTCH0);   
      dataTest.data=1000;
         //Send the data to queue
      queuePut(&cola, &dataTest,0); //if it is full wait 10mseg and unblock
      //SetEvent(LedTask,evPIN);
     
}


/** @} doxygen end group definition */

/*==================[end of file]============================================*/

