#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#include "strings.h"
#include "strings.h"

struct STRING 
{
#define MAX_STRING_LENGTH 100
    char characters[MAX_STRING_LENGTH];
    int length;
};

void check_string(const string *s)
{
    // a valid string has a length >= 0 and is less than MAX_STRING_LENGTH
    // a valid string has a null byte '\0' at the length of the string.
    // a valid string has length == number of characters counted before the null byte.

    assert( s != NULL );
    assert( s->length >= 0 && s->length < MAX_STRING_LENGTH );
    assert( s->characters[s->length] == '\0' );

    // exercise for the reader: implement checking if the number characters before
    // the null byte is equal to length.
    // if you do this, you should wrap this here with #ifndef NDEBUG
}


// see "strings.h" for usage
string *make_string(char *characters, int num_chars)
{
    // assuming that you're not calling make_string(NULL, 0);
    assert( characters != NULL );
    // assume that you're not calling make_string("", -1);
    assert( num_chars >= 0 );
    // assume that you're calling make_string with a valid C string
    assert( characters[num_chars] == '\0' );
    assert( num_chars < MAX_STRING_LENGTH );

    string *myString = NULL;

    // allocate a number of bytes in the heap
    // that is the same size as the string
    // structure.
    // It's OK for us to return and then use
    // heap-allocated objects in other
    // places, unlike stack-allocated objects.
    myString = malloc(sizeof(string));

    // more defensive programming:
    // malloc can return NULL when out of memory.
    if (myString != NULL)
    {
        // only if we can avoid the exceptional case
        // of array index out of bounds exception should
        // we actually create this string instance.
        if (num_chars > 0 && num_chars < MAX_STRING_LENGTH)
        {
            // copy only `num_chars` characters into
            // the string.
            strncpy(myString->characters, characters, num_chars);
            myString->length = num_chars;
        }
    }

    check_string( myString );

    return myString;
}

// see "strings.h" for usage
void destroy_string(string *s)
{
    assert( s != NULL );
    check_string( s );

    if ( s != NULL )
    {
        // release the resources we acquired
        free( s );
    }

}

// see "strings.h" for usage.
char char_at(const string *s, int index)
{
    char char_at_index = '\0';

    assert( s != NULL );
    check_string(s);

    assert( index >= 0 && index < s->length );

    if (s != NULL && index >= 0 && index < s->length)
    {
        char_at_index = s->characters[index];
    }

    // assumption: the character that we're returning is in the string, or
    // we're returning '\0' if the initial input assumptions were violated
    
    assert( ( index >= 0 && index < s->length && strchr( s->characters, char_at_index ) != NULL ) ||
            ( index < 0 || index > s->length ) );
    
    return char_at_index;
}


