/*************************************************************************//**

  @file     main.c

  @brief    EJERCICIO 1.4 - RTOS 2 OSEK

  @author   Marcos Darino (MD)

 ******************************************************************************/


/** \addtogroup OSEK_RTOS Ejer1.4
 ** @{ */

/*==================[inclusions]=============================================*/
#include "main.h"         /* <= own header */
#include "ciaaIO.h"
#include "os.h"               /* <= operating system header */


/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/
/** \brief Main function
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
 */
void ErrorHook(void)
{
  ciaaWriteOutput(3,1);  //Led RED ON
  ciaaWriteOutput(4,1);  //Led RED ON
  ciaaWriteOutput(5,1);  //Led RED ON
  ShutdownOS(0);
}

/** \brief Initial task
 *
 * This task is started automatically in the application mode 1.
 */
TASK(InitTask)
{
       
   ciaaIOInit();
   //Start the Button task
   SetRelAlarm(ActivateButtonTask, 0, 10000);
   //Set defaul time
   SetRelAlarm(ActivateLedTask,10, 500); 
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
  
    TickType Ticks;
    StatusType ret;

    ret = GetAlarm(ActivateLedTask,&Ticks); 
    if (E_OK == ret)
        {
            //if it is ok, update the time
            //to do this, first stop and then update
            CancelAlarm(ActivateLedTask);
            SetRelAlarm(ActivateLedTask,0, 100); 
        }
        else if (E_OS_NOFUNC == ret)
        {
          //set defaul time
          SetRelAlarm(ActivateLedTask,0, 500); 
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

   ciaaToggleOutput(0);
   /* terminate task */
   TerminateTask();
}


/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

