#ifndef __QUEUE_H
#define __QUEUE_H

#include <stdbool.h>

typedef struct QUEUE queue;

queue *makeQueue();

bool enqueue(queue *q, int number);

bool dequeue(queue *q, int *number);

bool front(queue *q, int *number);

bool isEmpty(queue *q);

int size(queue *q);

void printQueue(queue *q);

#endif
