/*==================[inclusions]=============================================*/
#include "boton_timeout.h"         /* <= own header */
#include "ciaaIO.h"
#include "os.h"               /* <= operating system header */

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/

int main(void)
{
   ciaaIOInit();
   StartOS(AppMode1);
   return 0;
}

void ErrorHook(void)
{
   ShutdownOS(0);
}

TASK(BotonTask)
{
   static int flag = 0;
   if ((flag == 0) && (ciaaReadInput(0) == 0)) {
	   flag = 1;
	   SetEvent(LEDTask, evBoton);
   }
   else if ((flag == 1) && (ciaaReadInput(0) == 1)){
	   flag = 0;
   }
   ChainTask(BotonTask);
}

TASK(LEDTask)
{
   EventMaskType eventos;
   SetRelAlarm(AlarmTimeout, 1000, 0);
   WaitEvent(evBoton | evTimeout);
   GetEvent(LEDTask, &eventos);
   if (eventos & evBoton) {
	   ClearEvent(evBoton);
	   CancelAlarm(AlarmTimeout);
	   ciaaWriteOutput(4, 0);
	   ciaaWriteOutput(5, 1);
   }
   else if (eventos & evTimeout) {
	   ClearEvent(evTimeout);
	   ciaaWriteOutput(4, 1);
	   ciaaWriteOutput(5, 0);
   }
   ChainTask(LEDTask);
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

