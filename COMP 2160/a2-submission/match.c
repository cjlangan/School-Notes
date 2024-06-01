/*-----------------------------------------
 * NAME: Connor Langan
 * STUDENT NUMBER: 7993941
 * COURSE: COMP 2160, SECTION: A01
 * INSTRUCTOR: Franklin Bristow
 * ASSIGNMENT: 2, QUESTION: 3
 *
 * REMARKS: Uses the stack.h interface to find the matching bracket given 
 *          input from standard input. Displays pair found to terminal.
 *-----------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#include "stack.h"

// Prints string based off provided length
int printString(char *string, int length);

int main(int argc, char **argv)
{
#define SEPARATION_CHAR ' '
#define OPEN_BRACKET '('
#define CLOSE_BRACKET ')'
#define NEWLINE '\n'
#define POINT_CHAR '^'
#define WRONG_CHAR 'X'
#define SPACER_CHAR ' '
    
    int index;
    int popped;
    int openBracket;  // position of open bracket
    int closeBracket; // position of closed bracket
    int stringLength;

    bool foundMatch;
    bool validInput;

    char currChar;
    char *string = NULL;
    char *separation = NULL;
    stack *myStack = NULL;

    while((currChar = getchar()) != EOF)
    {
        if(currChar != NEWLINE) // skip empty lines
        {
            index = 1;
            string = malloc(sizeof(char));
            
            // Ensure we were able to allocate memory
            if(string != NULL)
            {
                string[0] = currChar; // set first scanned character to start of string

                // Adding input character to heap allocated string
                while((currChar = getchar()) != NEWLINE && currChar != EOF)
                {
                    string = realloc(string, (index + 1) * sizeof(char));

                    // Ensure we were able to allocate memory
                    if(string != NULL)
                    {
                        string[index] = currChar;
                        index++;
                    }
                }
            }
            // Assume: that the string is not NULL
            assert(string != NULL);

            if(string != NULL)
            {
                // Getting the last instance of the separation character
                separation = strrchr(string, SEPARATION_CHAR);

                // Only continue if a separation chracter was found.
                if(separation != NULL)
                {
                    // Determining the integer value at the end of string
                    openBracket = atoi(separation);
                    
                    // Distance between separation character and string start is length of input
                    stringLength = separation - string;

                    index = 0;
                    foundMatch = false;
                    validInput = true;
                    myStack = create_stack();

                    // Find matching closed bracket given the open bracket
                    while(!foundMatch && validInput && index < stringLength)
                    {
                        // While iterating over string, push open bracket postions to the stack
                        if(string[index] == OPEN_BRACKET)
                        {
                            push(myStack, index);
                        }
                        // pop open bracket position to match a found closed bracket
                        else if(string[index] == CLOSE_BRACKET)
                        {
                            if(pop(myStack, &popped))
                            {
                                // Match found if position popped matches position of bracket to match
                                foundMatch = popped == openBracket;
                            }
                            else
                            {
                                // failed pop suggests finding match is impossible
                                validInput = false;
                            }
                        }
                        index++;
                    }
                    destroy_stack(myStack);

                    // Print just the input without the open bracket position
                    printString(string, stringLength);

                    // If find match, point to locations of bracket pair
                    if(foundMatch)
                    {
                        closeBracket = index - 1;

                        for(int i = 0; i < stringLength; i++)
                        {
                            if(i == openBracket || i == closeBracket)
                            {
                                printf("%c", POINT_CHAR);
                            }
                            else
                            {
                                printf("%c", SPACER_CHAR);
                            }
                        }
                    }
                    // Otherwise, print all X's
                    else
                    {
                        for(int i = 0; i < stringLength; i++)
                        {
                            printf("%c", WRONG_CHAR);
                        }
                    }
                    printf("\n");
                }
                else
                {
                    printf("No instance of a separation character found.\n");
                }
            }

            free(string);
        }
    }
        
    printf("All test cases complete.\n");

    return EXIT_SUCCESS;
}

// Prints string based off provided length
int printString(char *string, int length)
{
    // Assume: that given string is not NULL
    assert(string != NULL);

    if(string != NULL)
    {
        for(int i = 0; i < length; i++)
        {
            printf("%c", string[i]);
        }
        printf("\n");
    }

    return EXIT_SUCCESS;
}
