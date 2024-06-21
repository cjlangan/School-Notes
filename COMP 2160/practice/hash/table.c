#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include "table.h"

// I should have added the key as a part of the node structure. Then
// used this in all the methods.
// For the exam, it is vital that I internalise the structure of these
// ADT implementations, such has the key-value pair here, and the queue's 
// front pointing to the "end" of the linked list (easier to remove).
// Remember, this is a Programming Practices course, so recall all memory
// management, stack, heap, retrieving input (fgets, scanf), cohesion, coupling, DBC, 
// defensive programming, compilation steps (preprocessor, code generator, 
// assembler, linker), manipulating bits (recall operators), function pointers 
// (your code is in the address space, populated by our OS), 

typedef struct NODE node;
struct NODE
{
    char *word;
    node *link;
};

struct TABLE
{
    int size;
    node **data;
};

static int hash(table *t, char *item, int length)
{
    assert(t != NULL);
    assert(item != NULL);
    assert(length >= 0);

    // should be some DBC here, but, alas, I am lazy.

    int result = (int)(item[length - 1]) % t->size;

    for(int i = length - 2; i >= 0; i--)
    {
#define PRIME 13
        result = (PRIME * result + (int)(item[i])) % t->size;
    }
    return result;
}

table *makeTable(int size)
{
    assert(size > 0);

    table *t = malloc(sizeof(table));

    assert(t != NULL);

    if(t != NULL)
    {
        t->size = size;
        t->data = malloc(sizeof(node*) * size);
        assert(t->data != NULL);
        if(t->data == NULL)
        {
            free(t);
            t = NULL;
        }
    }
    return t;
}

bool insertItem(table *t, char *item, int length)
{
    assert(t != NULL);
    assert(item != NULL);
    assert(length >= 0);

    bool wasAdded = false;
    node *curr;
    node *prev = NULL;
    int key;

    if(t != NULL && item != NULL && length >= 0)
    {
        key = hash(t, item, length);
        printf("Key in insertitem: %d\n", key);
        curr = t->data[key];
        while(curr != NULL)
        {
            prev = curr;
            curr = curr->link;
        }
        node *newNode = malloc(sizeof(node));

        assert(newNode != NULL);

        if(newNode != NULL)
        {
            newNode->word = malloc(sizeof(char) * length + 1);

            assert(newNode->word != NULL);

            if(newNode->word != NULL)
            {
                strncpy(newNode->word, item, length);
                newNode->link = NULL;

                if(prev != NULL)
                {
                    prev->link = newNode;
                }
                else
                {
                    t->data[key] = newNode;
                }
                wasAdded = true;
            }
            else
            {
                free(newNode);
            }
        }
    }
    return wasAdded;
}

bool hasItem(table *t, char *item, int length)
{
    assert(t != NULL);
    assert(item != NULL);
    assert(length >= 0);


    bool hasItem = false;
    int key;
    node *curr;

    if(t != NULL && item != NULL && length >= 0)
    {
        key = hash(t, item, length);
        printf("Key in hasItem: %d\n", key);
        curr = t->data[key];
        while(!hasItem && curr != NULL)
        {
            if(strncmp(curr->word, item, length) == 0)
            {
                hasItem = true;
            }
            curr = curr->link;
        }
    }
    return hasItem;
}

bool deleteItem(table *t, char *item, int length)
{
    return true;
}
