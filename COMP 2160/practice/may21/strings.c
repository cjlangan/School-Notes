#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "strings.h"

struct STRING
{
#define MAX_STRING_LENGTH 100
    char characters[MAX_STRING_LENGTH];
    int length;
};

// Create and instance of a string structure
//
// Args:
//  characters: the character to put into the string
//  num_chars: the number of characters to copy
// Return:
//  an instance of the string structure
// struct STRING make_string(char characters[], int num_chars);

/**
 * Return the character at the specified indes
 *
 * Args:
 *  string: the string to get the characters from
 *  index: the index of the character.  Must be >=0, 
 *                                      must be < string length
 * Return: the character at that index or the NULL byte if invalid index
 */
// char char_at(struct STRING string, int index);

string *make_string(char characters[], int num_chars)
{
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
    
    return myString;
}

char char_at(struct STRING string, int index)
{
    char charAtIndex = '\0';

    if(index >= 0 && index < string.length)
    {
        charAtIndex = string.characters[index];
    }

    return  charAtIndex;
}

