#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

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
struct STRING make_string(char characters[], int num_chars);

/**
 * Return the character at the specified indes
 *
 * Args:
 *  string: the string to get the characters from
 *  index: the index of the character.  Must be >=0, 
 *                                      must be < string length
 * Return: the character at that index or the NULL byte if invalid index
 */
char char_at(struct STRING string, int index);

char char_at(struct STRING string, int index)
{
    char charAtIndex = '\0';

    if(index >= 0 && index < string.length)
    {
        charAtIndex = string.characters[index];
    }

    return  charAtIndex;
}

int main(int argc, char **argv)
{
    // the type
    // vvvvvvvvv
    struct STRING string;

    //call 'constructor'
    string = make_string("Franklin", 8);

    printf("String characters: %s, String length: %d\n", string.characters, string.length);

    printf("The character at 2 is %c\n", char_at(string, 2));

	  return EXIT_SUCCESS;
}

struct STRING make_string(char characters[], int num_chars)
{
    // just like an array, I can set the contents to all be zero
    struct STRING string = {0};

    // Only if we can avoid the exceptional case of array out of bouunds exception
    // should we actually create this string instance
    if(num_chars > 0 && num_chars < MAX_STRING_LENGTH)
    {
        // copy only up to 'num_chars' characters into the string
        strncpy(string.characters, characters, num_chars);
        string.length = num_chars;
    }
    
    return string;
}
