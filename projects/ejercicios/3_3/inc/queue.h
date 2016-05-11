/*
 * queue.h
 *
 *  Created on: Oct 21, 2014
 *      Author: pablo
 */

#ifndef QUEUE_H_
#define QUEUE_H_

#include "os.h"

/* queue definition */
#define QUEUE_LEN	    1

typedef int * queueItem_t;

typedef struct
{
	queueItem_t data[QUEUE_LEN];
	int count;
	EventMaskType ev;
	TaskType task;
}queue_t;

void queueInit(queue_t * q, EventMaskType e);
void queuePut(queue_t * q, queueItem_t d);
queueItem_t queueGet(queue_t * q);

#endif /* QUEUE_H_ */
