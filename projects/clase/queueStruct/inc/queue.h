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

#ifndef QUEUE_H_
#define QUEUE_H_

#include "os.h"

/* queue definition */
#define QUEUE_LEN	      10

typedef struct
{
	int  numerLed;
	int  timeLed;
}queueItem_t;

typedef struct
{
	queueItem_t data[QUEUE_LEN];
	int count;
	EventMaskType ev;
	TaskType task;
}queue_t;


/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/

/** initialize queue
 * @param q queue to be initialized
 * @param e osek event defined for this queue
 */
void queueInit(queue_t * q, EventMaskType e);

/** put item in queue. this function should block if the queue is full.
 *
 * @param q queue to be used
 * @param d item to queue
 */
void queuePut(queue_t * q, queueItem_t d);

/** get item from queue. this function should block if the queue is empty.
 *
 * @param q queue to be used
 * @return retrieved item
 */
queueItem_t queueGet(queue_t * q);

/*==================[end of file]============================================*/
#endif /* #ifndef _QUEUE_H_ */