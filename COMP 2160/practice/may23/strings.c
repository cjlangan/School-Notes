#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#include "strings.h"

struct STRING
{
#define MAX_STRING_LENGTH 100
    char characters[MAX_STRING_LENGTH];
    int length;
};

// invariant for checking if condtions of function are met while it's running, (state)
void check_string(string *s)
{
    // a valid string has a length that is >= 0 and is < MAX_STRING_LENGTH
    // also, has a null byte at the length of the string
    // also, has length == number of characters counted before the null bytes
    
    assert(s != NULL);
    assert(s->length >= 0 && s->length < MAX_STRING_LENGTH);
    assert(s->characters[s->length] == '\0');

    // exercise: implement checking if the number of characters before the null byte
    // is equal to length. Use ifndef and NDEBUG
    // should wrap this with here with #ifndef NDEBUG

#ifndef NDEBUG // this is good
    int size = 0;
    while(s->characters[size] != '\0')
    {
        size++;
    }
    assert(size == s->length);
#endif
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
    assert(num_chars < MAX_STRING_LENGTH);

    string *myString = NULL;

    // allocate a number of bytes in the heap that is the same size as
    // the string structure. It's ok for us to return and then use heap
    // allocated objects in other places, unlike stack-allocated objects.
    myString = malloc(sizeof(string));

    // defensive programming: Malloc can return if out of memory
    if(myString != NULL)
    {
        // Only if we can avoid the exceptional case of array out of bouunds exception
        // should we actually create this string instance
        if(num_chars > 0 && num_chars < MAX_STRING_LENGTH)
        {
            // copy only up to 'num_chars' characters into the string
            strncpy(myString->characters, characters, num_chars);
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

    // release the resources we acquired
    free(s);
}

char char_at(struct STRING string, int index)
{
    char char_at_index = '\0';
    
    // this is only going to be here if assertions or design-by-contract
    // are turned on at compile time
#ifndef NDEBUG
    char copy_of_string[MAX_STRING_LENGTH] = {0};
    int original_length = string.length;
    strncpy(copy_of_string, string.characters, original_length);
#endif

    if(index >= 0 && index < string.length)
    {
        char_at_index = string.characters[index];
    }

    // assume: the character we are returning is in the string or we are
    // returning the null byte if the initial input assumptions were violated
    assert((index >= 0 && index < string.length 
            && strchr(string.characters, char_at_index) != NULL) ||
            (index < 0 || index > string.length));

    // assumption: the string itself has not been modified by this code.
#ifndef NDEBUG //only need for non assert, dont need here
    assert(original_length == string.length);
    assert(strncmp(copy_of_string, string.characters, original_length) == 0);
#endif

    return  char_at_index;
}

