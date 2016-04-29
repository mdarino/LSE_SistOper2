/*
 * queue.c
 *
 *  Created on: Oct 21, 2014
 *      Author: pablo
 */

#include "queue.h"

void queueInit(queue_t * q, EventMaskType e)
{
	DisableAllInterrupts();
	q->count = 0;
	q->ev = e;
	q->task = (TaskType)~0;
	EnableAllInterrupts();
}

void queuePut(queue_t * q, queueItem_t d)
{
	while(q->count == QUEUE_LEN)
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

	q->data[q->count] = d;

	q->count++;

	EnableAllInterrupts();

	if((q->count == 1)&&(q->task != ((TaskType)~0)))
	{
		SetEvent(q->task, q->ev);
	}
}

queueItem_t queueGet(queue_t * q)
{
	while(q->count == 0)
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

	queueItem_t d = q->data[0];
	int i;

	for(i=0; i < q->count; i++)
	{
		q->data[i] = q->data[i+1];
	}

	q->count--;

	EnableAllInterrupts();

	if((q->count == QUEUE_LEN-1)&&(q->task != ((TaskType)~0)))
	{
		SetEvent(q->task, q->ev);
	}

	return d;
}
