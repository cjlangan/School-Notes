#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#include "strings.h"

// every node in the list will contain a character
typedef struct NODE node;
struct NODE 
{
    node *next;
    char c;
};

// A string is now a linked list of characters.
struct STRING 
{
    struct NODE *head;
    int length;
};

static void check_string(const string *s)
{
    assert( s != NULL );
    assert( s->length >= 0 );

    // check that we've got the right number of nodes:
#ifndef NDEBUG
    int count = 0;
    node *curr = s->head;
    while (curr != NULL)
    {
        count++;
        curr = curr->next;
    }
    assert(s->length == count);
#endif
}

void insert_end(char to_add, string *s)
{
    assert(s != NULL);
    check_string(s); // check if valid string, need for assingment 2

    node *new_node = malloc(sizeof(node));
    node *curr;
    node *prev;

    // check if not out of memory
    if(new_node != NULL)
    {
        // populate the node with the passed character
        new_node->c = to_add;
        new_node->next = NULL;

        // If list is empyt, make new node the head of that list
        if(s->head == NULL)
        {
            s->head = new_node;
        }
        else
        {
            // this is not an empty list, so we have to find the end of the list.
            curr = s->head;

            // the event is that we've foun NULL at the end of the list
            while(curr != NULL)
            {
                prev = curr;
                curr = curr->next;
            }

            // post-condition fro search: we've got a node and that node
            // is at the end of the list (it's next is NULL)
            assert(prev != NULL && prev->next == NULL);
            prev->next = new_node;
        }

        // We've added a character, so make sure this is still a vlid string
        s->length++;
    }

    check_string(s); //if change the string, we must check it.

// This diagram was created with asciiflow infinity: https://asciiflow.com/
//                      "cat" should become:                                                            
//                                                                                                      
// ┌──────────────┐   ┌──────────────┐   ┌──────────────┐   ┌──────────────┐   
// │              │   │              │   │              │   │              │  
// │  node *head──┼──►│  node *next──┼──►│  node *next──┼──►│  node *next──┼──►NULL 
// │  int length  │   │  char  c     │   │  char  c     │   │  char  c     │   
// │          3   │   │          'c' │   │          'a' │   │          't' │  
// └──────────────┘   └──────────────┘   └──────────────┘   └──────────────┘ 
//
//                      "" should become:
// ┌──────────────┐   
// │              │   
// │  node *head──┼──►NULL
// │  int length  │   
// │          0   │
// └──────────────┘ 
}

// see "strings.h" for usage
string *make_string(char *characters, int num_chars)
{
    assert( characters != NULL );
    assert( num_chars >= 0 );
    assert( characters[num_chars] == '\0' );

    string *myString = NULL;

    myString = malloc(sizeof(string));

    if (myString != NULL)
    {
        myString->head = NULL;
        myString->length = 0;
        
        // IF there  are any characters in the string (num_chars > 0), 
        // then we can add each fo them to the list
        // If num_chars = 0, then we are skipping past this loop (add
        // nothing to the list)
        for(int i = 0; i < num_chars; i++)
        {
            insert_end(characters[i], myString);
        }
       
        myString->length = num_chars;
    }

    check_string( myString );

    return myString;
}

// see "strings.h" for usage
void destroy_string(string *s)
{
    node *curr, *prev;
    assert( s != NULL );
    check_string( s );

    if ( s != NULL )
    {
        // we need to release the entire list now:
        curr = s->head;
        while (curr != NULL)
        {
            prev = curr;
            curr = curr->next;
            free(prev);
        }
        // release the resources we acquired
        free( s );
        s = NULL;
    }

}

// see "strings.h" for usage.
char char_at(const string *s, int index)
{
    assert( s != NULL );
    assert( index >= 0 && index < s->length );
    check_string( s );
    
    char char_at_index = '\0';
    node *curr;
    int count = 0;

    if (s != NULL && index >= 0 && index < s->length)
    {
        // go to node index:
        curr = s->head;
        while (curr != NULL && count < index)
        {
            curr = curr->next;
            count++;
        }
        if ( curr != NULL )
        {
            assert( count == index );
            char_at_index = curr->c;
        }
    }

    // assumption: the character that we're returning is in the string, or
    // we're returning '\0' if the initial input assumptions were violated
    
    assert( ( index >= 0 && index < s->length && char_at_index != '\0' ) ||
            ( index < 0 || index > s->length ) );
    
    return char_at_index;
}


