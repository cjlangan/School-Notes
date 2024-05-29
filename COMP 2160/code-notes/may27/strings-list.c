#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#include "strings.h"

// Every node in the list will contain a character
// can do typedef struct NODE node
//  - than can just use node instead of struct NODE.
struct NODE
{
    struct NODE *next;
    char c;
};

// A string is now a linked list of characters.
struct STRING
{
    struct NODE *head;
    int length;
};

// invariant for checking if condtions of function are met while it's running, (state)
void check_string(string *s)
{
    // a valid string has a length that is >= 0 and is < MAX_STRING_LENGTH
    // also, has a null byte at the length of the string
    // also, has length == number of characters counted before the null bytes
    
    assert(s != NULL);
    assert(s->length >= 0);

    // exercise: implement checking if the number of characters before the null byte
    // is equal to length. Use ifndef and NDEBUG
    // should wrap this with here with #ifndef NDEBUG
    // 
    // assert(s->characters[s->length] == '\0');
    
    struct NODE *curr = s->head;
    struct NODE *next = NULL;
    in counter = 0;

    //iteratively scan lsit until the end (NULL), or we find null byte in chracter field
    while(curr != NULL && curr->c != '\0')
    {
        if(curr->next != NULL)
        {
            counter++;
            curr = curr->next;
        }
    }

    assert(counter == s->length);
}

// see strings.h for usage
string *make_string(char *characters, int num_chars)
{
    // assuming that youre not calling make_string(NULL, 0) 
    assert(characters != NULL); 
    // assume that you're not calling make_string("", -1)
    assert(num_chars >= 0);
    // assume that you're calling make_string with a valid C string
    assert(characters[num_chars] == '\0');

    string *myString = NULL;
    
    struct NODE *next = NULL;

    // allocate a number of bytes in the heap that is the same size as
    // the string structure. It's ok for us to return and then use heap
    // allocated objects in other places, unlike stack-allocated objects.
    myString = malloc(sizeof(string));

    // defensive programming: Malloc can return if out of memory
    if(myString != NULL)
    {
        // Only if we can avoid the exceptional case of array out of bouunds exception
        // should we actually create this string instance
        if(num_chars > 0 &&)
        {
            // copying the string rrequires building a list; we need
            // a loop. What kind of loop should we use? a for-loop:
            for(int i = 0; i < num_chars; i++)
            {
                next = myString->head;
                myString->head = malloc(sizeof(struct NODE));
                if(myString->head != NULL)
                {
                    // insert node into the list:
                    myString->head->next = next;
                    myString->head->c = characters[i];
                }
            }
            myString->length = num_chars;
        }
    }
    
    check_string(myString);

    return myString;
}

// see "strings.h" fro usage
void destroy_string(string *s)
{
    assert(s != NULL);
    check_string(s);

    if(s != NULL)
    {
        // release the resources we acquired
        free(s);
    }
}

char char_at(const string *s, int index)
{
    char char_at_index = '\0';
    

    assert(s != NULL);
    check_string(s);

    assert(index >= 0 && index < s->length);

    if(s != NULL && index >= 0 && index < s->length)
    {
        char_at_index = s->characters[index];
    }

    // assume: the character we are returning is in the string or we are
    // returning the null byte if the initial input assumptions were violated
    assert((index >= 0 && index < s->length 
            && strchr(s->characters, char_at_index) != NULL) ||
            (index < 0 || index > s->length));

    return  char_at_index;
}

