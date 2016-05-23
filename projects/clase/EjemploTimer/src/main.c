

/*************************************************************************//**

  @file     main.c

  @brief    EJERCICIO 3.1 - RTOS 2 OSEK

  @author   Marcos Darino (MD)

 ******************************************************************************/


/**

 EJERCICIO 3.1    (Spanish)

Este   es   el   uso   más   simple   de   las   colas   del   RTOS:   Los   mensajes   se   pasan   por   copia   dentro   de   la  
cola, dándole persistencia a los mismos una vez que la tarea productora sale de contexto. 
 
Caso de uso​
: Una tarea manejadora de evento bloquea hasta recibir el mismo. 
 
Ejercicio​
:   Una   tarea   mide   el   tiempo   de   opresión   de   un   pulsador.   Cuando   lo   obtiene   lo   envía   par   cola   a  
otra tarea que destella un led durante el tiempo recibido. 

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
#include "delay.h"
#include "os.h"               /* <= operating system header */

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/


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
   delay_init();
   led_Init();

   /* activate periodic task:
    *  - for the first time after 350 ticks (350 ms)
    *  - and then every TIME_UPDATE_BUTTON ticks (10 ms)
    */
   
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
 
  /* terminate task */
   delay_us(20000);
   led_SetToggle(LED_GREEN);
   ChainTask(LedTask);
   
}


/** @} doxygen end group definition */

/*==================[end of file]============================================*/


  

ISR(TIMER1_IRQ)
{
  delay_setEvent(); //time!!!
}


// ISR(TIMER1_IRQ)
// {
//    if (Chip_TIMER_MatchPending(LPC_TIMER1, 0)) {
//       SetEvent(LedTask,evTIMER1);      
//    }
//    Chip_TIMER_ClearMatch(LPC_TIMER1, 0);
// }
