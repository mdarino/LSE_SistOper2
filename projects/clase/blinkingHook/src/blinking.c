/*==================[inclusions]=============================================*/
#include "os.h"               /* <= operating system header */
#include "ciaaPOSIX_stdio.h"  /* <= device handler header */
#include "ciaaPOSIX_string.h" /* <= string header */
#include "ciaak.h"            /* <= ciaa kernel header */
#include "blinking.h"         /* <= own header */

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

static int32_t fd_out;
static int32_t fd_in;

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/

int main(void)
{
   StartOS(AppMode1);
   return 0;
}

void ErrorHook(void)
{
   ciaaPOSIX_printf("ErrorHook was called\n");
   ciaaPOSIX_printf("Service: %d, P1: %d, P2: %d, P3: %d, RET: %d\n", OSErrorGetServiceId(), OSErrorGetParam1(), OSErrorGetParam2(), OSErrorGetParam3(), OSErrorGetRet());
   ShutdownOS(0);
}

TASK(InitTask)
{
   ciaak_start();

   fd_out = ciaaPOSIX_open("/dev/dio/out/0", ciaaPOSIX_O_RDWR);

   fd_in = ciaaPOSIX_open("/dev/dio/in/0", ciaaPOSIX_O_RDWR);

   SetRelAlarm(ActivatePeriodicTask, 0, 500);

   TerminateTask();
}

TASK(PeriodicTask)
{
   uint8_t inputs;
   uint8_t outputs;

   ciaaPOSIX_read(fd_in, &inputs, 1);

   ciaaPOSIX_read(fd_out, &outputs, 1);

   if((inputs & 0x02)==0x02) {
	   outputs ^= 0x20;
   } else {
	   outputs &= ~0x20;
   }
   ciaaPOSIX_write(fd_out, &outputs, 1);

   TerminateTask();
}

ALARMCALLBACK(tickHook)
{

}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

