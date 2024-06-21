#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdbool.h>
#include "queue.h"

int main(int argc, char **argv)
{
    int value = 0;

    queue *q = makeQueue();    

    enqueue(q, 1);
    enqueue(q, 2);
    enqueue(q, 3);
    enqueue(q, 4);
    enqueue(q, 5);
    enqueue(q, 6);
    enqueue(q, 7);

    printQueue(q);

    dequeue(q, &value);
    dequeue(q, &value);
    dequeue(q, &value);

    printQueue(q);

    dequeue(q, &value);
    dequeue(q, &value);
    dequeue(q, &value);
    dequeue(q, &value);

    printQueue(q);

    enqueue(q, 1);
    enqueue(q, 2);
    enqueue(q, 3);
    enqueue(q, 4);
    enqueue(q, 5);

    printQueue(q);

	  return EXIT_SUCCESS;
}
