#include "queue.h"
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

typedef struct NODE node;
struct NODE
{
    int value;
    node *link;
};

struct QUEUE
{
    node *front;
    node *back;
    int size;
};

queue *makeQueue()
{
    queue *q = malloc(sizeof(queue));

    assert(q != NULL);

    if(q != NULL)
    {
        q->size = 0;
        q->front = NULL;
        q->back = NULL;
    }
    return q;
}

bool enqueue(queue *q, int number)
{
    assert(q != NULL);
    
    bool wasAdded = false;

    if(q != NULL)
    {
        node *newNode = malloc(sizeof(node));

        assert(newNode != NULL);
        
        if(newNode != NULL)
        {
            newNode->value = number;
            newNode->link = NULL;

            if(q->back != NULL)
            {
                q->back->link = newNode;
            }

            q->back = newNode;

            if(q->front == NULL)
            {
                q->front = newNode;
            }

            q->size++;
            wasAdded = true;
        }
    }
    return wasAdded;
}

bool dequeue(queue *q, int *number)
{
    assert(q != NULL);
    assert(number != NULL);

    bool wasRemoved = false;

    if(q != NULL && q->front != NULL && number != NULL)
    {
        *number = q->front->value;
        node *temp = q->front;
        q->front = q->front->link;
        free(temp);
        q->size--;
        wasRemoved = true;
    }
    return wasRemoved;
}

bool front(queue *q, int *number)
{
    assert(q != NULL);
    assert(number != NULL);

    bool wasValue = false;

    if(q != NULL && q->front != NULL && number != NULL)
    {
        *number = q->front->value;
        wasValue = true;
    }

    return wasValue;
}

bool isEmpty(queue *q)
{
    assert(q != NULL);

    bool empty = true;

    if(q != NULL)
    {
        empty = q->front == NULL;
    }
    return empty;
}

int size(queue *q)
{
    assert(q != NULL);

    int size = 0;

    if(q != NULL)
    {
        size = q->size;
    }
    return size;
}

void printQueue(queue *q)
{
    if(q != NULL)
    {
        node *curr = q->front;

        while(curr != NULL)
        {
            printf("%d ", curr->value);
            curr = curr->link;
        }
        printf("\n");
    }
}


