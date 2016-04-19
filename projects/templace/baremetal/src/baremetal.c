/* Copyright 2014, 2015 Mariano Cerdeiro
 * Copyright 2014, Pablo Ridolfi
 * Copyright 2014, Juan Cecconi
 * Copyright 2014, Gustavo Muro
 * Copyright 2015, Eric Pernia
 * All rights reserved.
 *
 * This file is part of CIAA Firmware.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

/** \brief Bare Metal example source file
 **
 ** This is a mini example of the CIAA Firmware.
 **
 **/

/** \addtogroup CIAA_Firmware CIAA Firmware
 ** @{ */
/** \addtogroup Examples CIAA Firmware Examples
 ** @{ */
/** \addtogroup Baremetal Bare Metal example source file
 ** @{ */

/*
 * Initials    Name
 * ---------------------------
 * ENP          Eric Pernia
 *
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * 20151104   v0.0.1   ENP   First version
 */

/*==================[inclusions]=============================================*/
#include "baremetal.h"       /* <= own header */
#include "os.h"               /* <= operating system header */
#include "DRIVER_GPIO.h"

#include "HW_leds.h"
#include "HW_buttons.h"
#include "HW_display.h"


#include "OS_SCH.h"
#include "OS_tasks.h"



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

#define TEC1_GPIO 0
#define TEC1_PIN  4

#define LEDB_GPIO 5
#define LEDB_PIN  2

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/

static void boardButtonsInit(void) {

   /* Config EDU-CIAA-NXP Button Pins as GPIOs */
   Chip_SCU_PinMux(1,0,MD_PUP|MD_EZI|MD_ZI,FUNC0); /* GPIO0[4], TEC1 */
   Chip_SCU_PinMux(1,1,MD_PUP|MD_EZI|MD_ZI,FUNC0); /* GPIO0[8], TEC2 */
   Chip_SCU_PinMux(1,2,MD_PUP|MD_EZI|MD_ZI,FUNC0); /* GPIO0[9], TEC3 */
   Chip_SCU_PinMux(1,6,MD_PUP|MD_EZI|MD_ZI,FUNC0); /* GPIO1[9], TEC4 */

   /* Config EDU-CIAA-NXP Button Pins as Inputs */
   Chip_GPIO_SetDir(LPC_GPIO_PORT, 0,(1<<4)|(1<<8)|(1<<9),0);
   Chip_GPIO_SetDir(LPC_GPIO_PORT, 1,(1<<9),0);

}

static void boardLedsInit(void) {

	/* Config EDU-CIAA-NXP Led Pins as GPIOs */
   Chip_SCU_PinMux(2,0,MD_PUP,FUNC4);  /* GPIO5[0],  LEDR */
   Chip_SCU_PinMux(2,1,MD_PUP,FUNC4);  /* GPIO5[1],  LEDG */
   //Chip_SCU_PinMux(2,2,MD_PUP,FUNC4);  /* GPIO5[2],  LEDB */
   Chip_SCU_PinMux(2,10,MD_PUP,FUNC0); /* GPIO0[14], LED1 */
   Chip_SCU_PinMux(2,11,MD_PUP,FUNC0); /* GPIO1[11], LED2 */
   Chip_SCU_PinMux(2,12,MD_PUP,FUNC0); /* GPIO1[12], LED3 */

   /* Config EDU-CIAA-NXP Led Pins as Outputs */
   Chip_GPIO_SetDir(LPC_GPIO_PORT, 5,(1<<0)|(1<<1)|(1<<2),1);
   Chip_GPIO_SetDir(LPC_GPIO_PORT, 0,(1<<14),1);
   Chip_GPIO_SetDir(LPC_GPIO_PORT, 1,(1<<11)|(1<<12),1);

   /* Init EDU-CIAA-NXP Led Pins OFF */
   Chip_GPIO_ClearValue(LPC_GPIO_PORT, 5,(1<<0)|(1<<1)|(1<<2));
   Chip_GPIO_ClearValue(LPC_GPIO_PORT, 0,(1<<14));
   Chip_GPIO_ClearValue(LPC_GPIO_PORT, 1,(1<<11)|(1<<12));




   GPIO_setAsOutput(5,2);
   Chip_SCU_PinMux(2,2,MD_PUP,FUNC4);  /* GPIO5[2],  LEDB */
}

static void coreInit(void) {

   /* Read clock settings and update SystemCoreClock variable */
   SystemCoreClockUpdate();
   
   /* Init SysTick interrupt, TICKRATE_HZ ticks per second */
   //tickInit();

}

/* Set up and initialize board hardware */
void boardInit(void) {

   /* Configure Core */
   coreInit();


   /* Initializes GPIO */
  //Chip_GPIO_Init(LPC_GPIO_PORT);

   /* Config EDU-CIAA-NXP Button Pins */
  // boardButtonsInit();

   /* Config EDU-CIAA-NXP Led Pins */
   //boardLedsInit();


   led_Init();
   backlight_Init();



   // INICIO EL PLANIFICADOR
   SCH_Init();

   // INICIALIZACIONES DE TAREAS
  Task1_Init();
  Task2_Init();
  Task3_Init();

   // AÑADO LA TAREA Task 1 AL PLANIFICADOR
   // Add the 'Task1' task (on for ~1000 ms, off for ~1000 ms)
   // - timings are in ticks (1 ms tick interval)
   // (Max interval / delay is 65535 ticks)
  	  SCH_Add_Task(Task1, 0, 1000);

   // AÑADO LA TAREA Task2 AL PLANIFICADOR
  	  SCH_Add_Task(Task2, 1001, 500);
   
   // AÑADO LA TAREA Task3 AL PLANIFICADOR    
      SCH_Add_Task(Task3, 1003, 250);

   // INICIO EL PLANIFICADOR
  SCH_Start();






}



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
   /* perform the needed initialization here */

//   uint8_t gpioPort = 0;
//   uint8_t gpioPin  = 0;
//   uint8_t value    = 0;

    //Buttons



   boardInit();

	struct STR_Button button1;
	buttonConstructor(&button1,0,4);
	buttonInitWithoutPullUp(&button1,1,0,FUNC0);

	struct STR_Button button2;
	buttonConstructor(&button2,0,8);
	buttonInitWithoutPullUp(&button2,1,1,FUNC0);

	struct STR_Button button3;
	buttonConstructor(&button3,0,9);
	buttonInitWithoutPullUp(&button3,1,2,FUNC0);

	struct STR_Button button4;
	buttonConstructor(&button4,1,9);
	buttonInitWithoutPullUp(&button4,1,6,FUNC0);


   led_Test();



   while(1) {
      
	  SCH_Dispatch_Tasks();


	   buttonUpdate(&button1);
	   if (buttonGetState(&button1)==PRESS)
	   {
		   led_SetON(LED_RED);
		   backlight_SetON(BACKLIGHT_RED);
	   }
	   else
	   {
		   led_SetOFF(LED_RED);
		   backlight_SetOFF(BACKLIGHT_RED);
	   }


	   buttonUpdate(&button2);
	   if (buttonGetState(&button2)==PRESS)
	   {
		   led_SetON(LED_BLUE);
		   backlight_SetON(BACKLIGHT_BLUE);
	   }
	   else
	   {
		   led_SetOFF(LED_BLUE);
		   backlight_SetOFF(BACKLIGHT_BLUE);
	   }


	   buttonUpdate(&button3);
	   if (buttonGetState(&button3)==PRESS)
	   {
		   led_SetON(LED_GREEN);
		   backlight_SetON(BACKLIGHT_GREEN);
	   }
	   else
	   {
		   led_SetOFF(LED_GREEN);
		   backlight_SetOFF(BACKLIGHT_GREEN);
	   }
      /* add your code here */
      
	 


      /* Read TEC1 */
//      gpioPort = TEC1_GPIO;
//      gpioPin  = TEC1_PIN; //
//      value    = Chip_GPIO_ReadPortBit( LPC_GPIO_PORT, gpioPort, gpioPin );


//      if (GPIO_getValue(TEC1_GPIO,TEC1_PIN))
//   		 {
//    	  GPIO_setON(5,2);
//   		 }
//      else
//   		 {
//    	  GPIO_cleanOFF(5,2);
//   		 }

      /* Write LED B */

//      gpioPort = LEDB_GPIO;
//      gpioPin  = LEDB_PIN;
//
//      Chip_GPIO_SetPinState( LPC_GPIO_PORT, gpioPort, gpioPin, !value);
      
   }
   return 0;
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

