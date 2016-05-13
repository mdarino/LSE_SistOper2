/* Copyright 2015, Pablo Ridolfi.
 * All rights reserved.
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

#ifndef _QUEUE_H_
#define _QUEUE_H_

/** \brief Queue implementation for OSEK-OS applications.
 **
 **/

/*==================[inclusions]=============================================*/

#include "os.h"

/*==================[macros]=================================================*/

/** queue length */
#define QUEUE_LEN	      3

//Events  - MUST BE THE SAME in the .OIL
#define EVENT_SPACE        evQueueSpace
#define EVENT_TIMEOUT_GET  evQueueTimeOutGet
#define EVENT_TIMEOUT_PUT  evQueueTimeOutPut
//ALARM  - MUST BE THE SAME in the .OIL
#define ALARM_TIMEOUT_GET  AlarmQueueTimeoutGet
#define ALARM_TIMEOUT_PUT  AlarmQueueTimeoutPut

//RETURN VALUES - 
#define QUEUE_ERROR     2
#define QUEUE_TIMEOUT   1
#define QUEUE_OK        0

//queue block forever - if you send it, i will be block forever
#define QUEUE_BLOCK_FOREVER     0

/*==================[typedef]================================================*/

/** data type to be stored in the queue */
typedef struct 
{
  int data; 
}queueItem_t;

/** return types */
typedef int returnType_t;

/** queue definition */
typedef struct
{
	queueItem_t data[QUEUE_LEN];     /**< queue buffer */
	int            head;					/**< last item queued */
	int            tail;					/**< first item queued */
	EventMaskType  evSpace;          /**< event associated to this queue */
   EventMaskType  evTimeOutGet;     /**< event associated to when you try to get info */
   EventMaskType  evTimeOutPut;     /**< event associated to when you try to put info */
	TaskType       task;					/**< waiting task */
   AlarmType      alarmTimeoutGet;  /**< Set the max time to wait when you try to get info */
   AlarmType      alarmTimeoutPut;  /**< Set the max time to wait when you try to put info */
}queue_t;

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/

/** initialize queue
 * @param q queue to be initialized
 */
void queueInit(queue_t * q);

/** put item in queue. this function should block if the queue is full.
 *
 * @param q queue to be used
 * @param d item to queue
 */


/**
 * @brief Put item in queue
 * @param q   Struct of the queue
 * @param d   data pointer
 * @param t   How many tick we will wait if the  queue is full (0 for infinite)
 * @return    "QUEUE_TIMEOUT" if can not put the data in the queue in time- 
 *            "QUEUE_OK" if can put the data in the queue
 */

returnType_t queuePut(queue_t * q, queueItem_t * d, TickType t);

/**
 * @brief Get item in queue
 * @param q   Struct of the queue
 * @param d   data pointer
 * @param t   How many tick we will wait if the  queue is full (0 for infinite)
 * @return    "QUEUE_TIMEOUT" if can not put the data in the queue in time- 
 *            "QUEUE_OK" if can put the data in the queue
 */
returnType_t queueGet(queue_t * q, queueItem_t *d, TickType t);




/*==================[end of file]============================================*/
#endif /* #ifndef _QUEUE_H_ */
