/*************************************************************************//**

  @file     main.c

  @brief    EJERCICIO 1.2 - RTOS 2 OSEK

  @author   Marcos Darino (MD)

 ******************************************************************************/


/**

 EJERCICIO 1.2    (Spanish)
  Implementar   una   tarea   que   genere   una   onda   cuadrada   
  (y   que   encienda   un   LED)   con  periodo de 1 seg y 
  ciclos de actividad incrementándose 100 ms, 200 ms, 300 ms.... 
 **/

/** \addtogroup OSEK_RTOS Ejer1.2
 ** @{ */
 


/*==================[inclusions]=============================================*/
#include "main.h"       /* <= own header */
#include "os.h"               /* <= operating system header */
#include "HW_leds.h"

#ifndef CPU
#define CPU lpc4337
#endif


#ifndef CPU
#error CPU shall be defined
#endif
#if (lpc4337 == CPU)
#include "chip.h"
#elif (mk60fx512vlq15 == CPU)
#else
#endif


/*==================[macros and definitions]=================================*/


/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/
uint8_t test=0;


int main(void)
{
   /* perform the needed initialization here */
  StartOS(AppMode1);

  
   return 0;
}


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
   led_Init();

   /* init CIAA kernel and devices */
   SetRelAlarm(ActivatePeriodicTask, 0, 100);

   /* terminate task */
   TerminateTask();
}

/** \brief Periodic Task
 *
 * This task is started automatically every time that the alarm
 * ActivatePeriodicTask expires.
 *
 */
TASK(PeriodicTask)
{
  static uint8_t inc=0;  //Save the the current state  (column)
  static uint8_t sta=0;  //Save the max state on (row)

  //Every 100mseg we evaluate the state, TABLE:
  //  ROW     ON     OFF     UNIT
  //  1      100     900     mseg
  //  2      200     800     mseg
  //  3      300     700     mseg
  //  4      400     600     mseg
  //  5      500     500     mseg
  //  6      600     400     mseg
  //  7      700     300     mseg
  //  8      800     200     mseg
  //  9      900     100     mseg
  //  10     1000    0       mseg

  /*
  Check if inc is less than sta, for example 
  in the first time inc=0 and sta=0, turn on 
  the led, increce inc, then inc=1 and sta=0, 
  turn off the led for the following 9 times
  when inc=10 - we clean it and increase sta
  to 1. The second time we turn the led two times 
  (200mseg) and go forward...
  */
 
  if (inc<=sta)   
  {
    led_SetON(LED_1);  //Set on the led
  }
  else
  {
    led_SetOFF(LED_1);  //Set off the led
    led_SetToggle(LED_2);  //Only to debug
  }
  
  inc++;  //Increase current state (column)
  led_SetToggle(LED_3); //Only to debug

  //If inc>10, we complete the first row of the table
  //Clean inc and increment sta
  if (inc>10)
  {
    sta++;
    inc=0;
  }
  
  //Set the max of the row
  if (sta>10)
  {
    sta=0;
  }
   
   /* terminate task */
   TerminateTask();

}

/** @} doxygen end group definition */

/*==================[end of file]============================================*/

