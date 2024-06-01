/*-----------------------------------------
 * NAME: Connor Langan
 * STUDENT NUMBER: 7993941
 * COURSE: COMP 2160, SECTION: A01
 * INSTRUCTOR: Franklin Bristow
 * ASSIGNMENT: 2, QUESTION: 1
 *
 * REMARKS: An implementation of the stack.h interface as a linked list.
 *          Utilizes DBC to support the programmer's using it.
 *-----------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "stack.h"

// Every node will contain an integer
typedef struct NODE node;
struct NODE
{
    node *next;
    int value;
};

// A stack is a chain of nodes
struct STACK
{
    node *head;
};

/* check_stack() 
 *      Invariant to determine if a stack is in a valid state.
 *
 * Args:
 *      s: the stack to be checked. Must not be NULL. No node within may
 *          point to any previous node. No nodes signifies head must be NULL, 
 *          and at least one node signifies that head must not be NULL.
 *          The last node must point to NULL.
 */
void check_stack(stack *s)
{
#ifndef NDEBUG
    // Assume: that the given stack is not NULL
    assert(s != NULL);

    int num_nodes = 0;
    node *curr = s->head;
    node *prev = NULL;

    // Assume: that no node points to any previous node
    while(curr != NULL)
    {
        num_nodes++;
        prev = s->head;

        while(prev != curr)
        {
            assert(curr->next != prev);
            prev = prev->next;
        }

        curr = curr->next;
    }

    // Assume: that the last node points to NULL
    assert(curr == NULL);

    // Assume: that if the number of nodes is = 0, then head is NULL
    //              if the number of nodes is > 0, then head is not NULL
    if(num_nodes == 0)
    {
        assert(s->head == NULL);
    }
    else
    {
        assert(s->head != NULL);
    }
#endif
}

// See stack.h for usage
stack *create_stack(void)
{
    // Create space for the stack
    stack *s = NULL;
    s = malloc(sizeof(stack));

    // Ensure we were able to allocate memory for the stack
    if(s != NULL)
    {
        s->head = NULL;
    }

    // Assume: the stack returned is not NULL and is empty
    assert(s != NULL);

    check_stack(s);

    return s;
}

// See stack.h for usage
bool push(stack *s, int value)
{
    // The stack to push the value onto must not be NULL and must be valid.
    assert(s != NULL);
    check_stack(s);

    // Track the size to compare for later
#ifndef NDEBUG
    int original_size = size(s);
#endif
    
    bool added = false;
    node *new_node = malloc(sizeof(node));
 
    // ensure the stack exists and that memory was available for the new node
    if(s != NULL && new_node != NULL)     
    {
        // Insert new node to top of the stack
        new_node->value = value;
        new_node->next = s->head;
        s->head = new_node;

        added = true;

        // Assume: that the head node has the proper value
        assert(s->head->value == value);
    }

    // Assume: that the size of the stack has increased by one and the stack is valid
    assert(size(s) == original_size + 1);    
    check_stack(s);

    return added;
}

// See stack.h for usage
bool peek(stack *s, int *value)
{
    // Assume: that the given stack is not NULL and is valid
    assert(s != NULL);
    check_stack(s);
    // Assume: that the given integer address is not NULL
    assert(value != NULL);

    // Track the original size and contents of the stack
#ifndef NDEBUG
    int original_size = size(s);
    int *original_stack = malloc(original_size * sizeof(int));
    assert(original_stack != NULL);
    node *curr = s->head;

    for(int i = 0; i < original_size; i++)
    {
        original_stack[i] = curr->value;
        curr = curr->next;
    }
#endif
    
    bool hasData = false;

    // Ensure the stack has data and that the given integer address is not NULL
    if(s != NULL && s->head != NULL && value != NULL)
    {
        *value = s->head->value;
        hasData = true;
    }
    
    // Assume: that the size of the stack hasn't changed.
    assert(size(s) == original_size);
    
    // Assume: that the contents of the stack have stayed the same.
#ifndef NDEBUG
    curr = s->head;
    
    for(int i = 0; i < original_size; i++)
    {
        assert(curr->value == original_stack[i]);
        curr = curr->next;
    }
    free(original_stack);
#endif

    check_stack(s);

    return hasData;
}

// See stack.h for usage
bool pop(stack *s, int *value)
{
    // Assume: that the given stack is not NULL and is valid
    assert(s != NULL);
    check_stack(s);
    // Assume: that the given integer address is not NULL
    assert(value != NULL);

    // track the size so we can compare to it later
#ifndef NDEBUG
    int original_size = size(s);
#endif
    
    bool wasPopped = false;
    node *oldhead;

    // Ensure the stack has data and that the given integer address is not NULL
    if(s != NULL && s->head != NULL && value != NULL)
    {
        *value = s->head->value; // set value to head value of stack
        
        // track the old head node to free and set the 
        // head node to be the next node on the stack
        oldhead = s->head;
        s->head = s->head->next;
        free(oldhead);

        wasPopped = true;
    }

    // Assume: if data was popped, then size is one less
    //         if data wasn't popped, then size is the same
#ifndef NDEBUG
    if(wasPopped)
    {
        assert(size(s) == original_size - 1);
    }
    else
    {
        assert(size(s) == original_size);
    }
#endif

    check_stack(s);

    return wasPopped;
}

// See stack.h for usage
int size(stack *s)
{
    // Assume: that the given stack is not NULL and the stack is valid
    assert(s != NULL);
    check_stack(s);

    int size = 0;
    node *curr;

    // if stack exists
    if(s != NULL)
    {
        curr = s->head;

        // Increment size until end of stack is reached.
        while(curr != NULL)
        {
            size++;
            curr = curr->next;
        }
    }
   
    // Assume: that the returned size is >= 0 and that the stack is valid
    assert(size >= 0);
    check_stack(s);

    return size;
}

// See stack.h for usage
bool empty(stack *s)
{
    // Assume: that the given stack is not NULL and is valid
    assert(s != NULL);
    check_stack(s);
    
    // Track the original size and contents of the stack
#ifndef NDEBUG
    int original_size = size(s);
    int *original_stack = malloc(original_size * sizeof(int));

    assert(original_stack != NULL); // Ensure we could allocate memory
    
    node *curr = s->head;

    for(int i = 0; i < original_size; i++)
    {
        original_stack[i] = curr->value;
        curr = curr->next;
    }
#endif

    bool isEmpty = true;

    // check if the stack exists and is not empty
    if(s != NULL && s->head != NULL)
    {
        isEmpty = false;
    }
    
    // Assume: that the size of the stack hasn't changed.
    assert(size(s) == original_size);
    
    // Assume: that the contents of the stack have stayed the same.
#ifndef NDEBUG
    curr = s->head;
    
    for(int i = 0; i < original_size; i++)
    {
        assert(curr->value == original_stack[i]);
        curr = curr->next;
    }
    free(original_stack);
#endif

    check_stack(s);

    return isEmpty;
}

// See stack.h for usage
bool destroy_stack(stack *s)
{
    // Assume: that the given stack is not NULL and is valid
    assert(s != NULL);
    check_stack(s);
    
    node *curr;
    node *prev;   
    bool isDestroyed = false;

    // if stack exists, release the memory for each node 
    if(s != NULL)
    {
        // Release the entire stack now
        curr = s->head;

        while(curr != NULL)
        {
            prev = curr;
            curr = curr->next;
            free(prev);
        }
        
        free(s);
        s = NULL;
        isDestroyed = true;
    }
    
    return isDestroyed;
}
