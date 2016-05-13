/* Copyright 2015, Nicolás Dassieu Blanchet.
 * Copyright 2015, Pablo Ridolfi.
 * All rights reserved.
 *
 * This file is part of a project.
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

/** @brief OSEK-OS simple queue implementation.
 **
 **/

/*==================[inclusions]=============================================*/

#include "queue.h"

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/

/**
 * @brief Init the struct of the queue
 */
void queueInit(queue_t * q)
{
	DisableAllInterrupts();
	q->tail = 0;
	q->head = 0;
	q->evSpace = EVENT_SPACE;
	q->evTimeOutGet = EVENT_TIMEOUT_GET;
	q->evTimeOutPut = EVENT_TIMEOUT_PUT;
	q->alarmTimeoutGet = ALARM_TIMEOUT_GET;
	q->alarmTimeoutPut = ALARM_TIMEOUT_PUT;
	q->task = (TaskType)~0;
	EnableAllInterrupts();
}

/**
 * @brief Send a new data to the queue
 */
returnType_t queuePut(queue_t *q, queueItem_t *d, TickType t)
{
	
   //----------------------------------
	//----Local variables
	//----------------------------------

	EventMaskType events;  //save the events...to check
	int flagState=0;  //1 timeout, 0 unblock in time
	int returnState=QUEUE_OK; //Return variable
   TickType Ticks;	//sabe the current tick of the alarm (not used)

   //----------------------------------
	//----Check if the queue is full...
	//----------------------------------
	while(((q->head+1)%QUEUE_LEN) == q->tail)
	{
		//Check the task to aboid the block 
		if(q->task != ((TaskType)~0))
		{
			/* interbloqueo */
			ErrorHook();
		}

		//If the time != 0 => activate the alarm 
		if (t != 0)
		{
			SetRelAlarm(q->alarmTimeoutPut, t, 0);
		}
		
		//Set the task...to know how is block
		GetTaskID(&(q->task));
		//Waiting space or timeout in que queue
   	WaitEvent(q->evTimeOutPut | q->evSpace);
   	//Get the event
   	GetEvent(q->task, &events);

	   if (events & q->evSpace) {
		   //If we have space...
		   ClearEvent(q->evSpace);
		   flagState=0; //unblock in time
		   //Check if the alarm is on. If it is on, we turn off
		   if (E_OK == GetAlarm(q->alarmTimeoutPut,&Ticks))
        	{
          	CancelAlarm(q->alarmTimeoutPut);
         }
	   }
	   else if (events & q->evTimeOutPut) {
		   //If timeout...
		   ClearEvent(q->evTimeOutPut);
		   flagState=1;  //Timeout
	   }
		
		//Clean the task waiting
		q->task = (TaskType)~0;
	}

   //----------------------------------
	//----Data.....
	//----------------------------------
	
	if (flagState==0)
	{	
		//If unblock in time.... 
	   DisableAllInterrupts();
		//Copy the new data in the queue
		q->data[q->head] = *d;
		//Update the head of the queue
		q->head = (q->head+1)%QUEUE_LEN;
		EnableAllInterrupts();
		//return OK - new data is in the queue
		returnState= QUEUE_OK;
	}
	else
	{
		//return TimeOut - we were unlocked by alarm
		returnState= QUEUE_TIMEOUT;
	}


	//if some task is blocking -> set the event 
	if(q->task != ((TaskType)~0))
	{
		SetEvent(q->task, q->evSpace);
	}

	return returnState;
}



/**
 * @brief Receive a new data to the queue
 */

returnType_t queueGet(queue_t * q, queueItem_t *d, TickType t)
{
   
   //----------------------------------
   //----Local variables
   //----------------------------------

   EventMaskType events;  //save the events...to check
   int flagState=0;  //1 timeout, 0 unblock in time
   int returnState=QUEUE_OK; //Return variable
   TickType Ticks;   //sabe the current tick of the alarm (not used)
   StatusType ret;

   //----------------------------------
   //----Check if the queue is ...
   //----------------------------------
   if(q->head == q->tail)
   {
      //Check the task to aboid the block 
      if(q->task != ((TaskType)~0))
      {
         /* interbloqueo */
         ErrorHook();
      } 
      
      //If the time != 0 => activate the alarm 
      if (t != 0)
      {
         SetRelAlarm(q->alarmTimeoutGet, t, 0);
      }    

      //Set the task...to know how is block
      GetTaskID(&(q->task));
      //Waiting space or timeout in que queue
      WaitEvent(q->evTimeOutGet | q->evSpace);
      //Get the event
      GetEvent(q->task, &events);

      if (events & q->evSpace) {
         //If we have space...
         ClearEvent(q->evSpace);
         flagState=0; //unblock in time
         //Check if the alarm is on. If it is on, we turn off
         if (t != 0)
         {
            CancelAlarm(q->alarmTimeoutGet);
         }

      }
      else if (events & q->evTimeOutGet) {
         //If timeout...
         ClearEvent(q->evTimeOutGet);
         flagState=1;  //Timeout
      }
      
      //Clean the task waiting
      q->task = (TaskType)~0;
   }

   
   //----------------------------------
   //----Data.....
   //----------------------------------
   
   if (flagState==0)
   {  
      //If unblock in time.... 
      DisableAllInterrupts();
      //Copy the new data in the queue
      *d = q->data[q->tail];
      //Update the head of the queue
      q->tail = (q->tail+1)%QUEUE_LEN;
      EnableAllInterrupts();
      //return OK - new data is in the queue
      returnState= QUEUE_OK;
   }
   else
   {
      //return TimeOut - we were unlocked by alarm
      returnState= QUEUE_TIMEOUT;
   }

   //if some task is blocking -> set the event 
   if(q->task != ((TaskType)~0))
   {
      SetEvent(q->task, q->evSpace);
   }

   return returnState;

}

/*==================[end of file]============================================*/
