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

void queueInit(queue_t * q, EventMaskType e)
{
	DisableAllInterrupts();
	q->tail = 0;
	q->head = 0;
	q->ev = e;
	q->task = (TaskType)~0;
	EnableAllInterrupts();
}

void queuePut(queue_t * q, queueItem_t d)
{
	while(((q->head+1)%QUEUE_LEN) == q->tail)
	{
		if(q->task != ((TaskType)~0))
		{
			/* interbloqueo */
			ErrorHook();
		}
		GetTaskID(&(q->task));
		WaitEvent(q->ev);
		ClearEvent(q->ev);
		q->task = (TaskType)~0;
	}

	DisableAllInterrupts();

	q->data[q->head] = d;

	q->head = (q->head+1)%QUEUE_LEN;

	EnableAllInterrupts();

	if(q->task != ((TaskType)~0))
	{
		SetEvent(q->task, q->ev);
	}
}

queueItem_t queueGet(queue_t * q)
{
	while(q->head == q->tail)
	{
		if(q->task != ((TaskType)~0))
		{
			/* interbloqueo */
			ErrorHook();
		}
		GetTaskID(&(q->task));
		WaitEvent(q->ev);
		ClearEvent(q->ev);
		q->task = (TaskType)~0;
	}

	DisableAllInterrupts();

	queueItem_t d = q->data[q->tail];
	q->tail = (q->tail+1)%QUEUE_LEN;

	EnableAllInterrupts();

	if(q->task != ((TaskType)~0))
	{
		SetEvent(q->task, q->ev);
	}

	return d;
}

/*==================[end of file]============================================*/
