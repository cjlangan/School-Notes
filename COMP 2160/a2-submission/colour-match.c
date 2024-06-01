/*-----------------------------------------
 * NAME: Connor Langan
 * STUDENT NUMBER: 7993941
 * COURSE: COMP 2160, SECTION: A01
 * INSTRUCTOR: Franklin Bristow
 * ASSIGNMENT: 2, QUESTION: BONUS
 *
 * REMARKS: Uses the stack.h interface to pair up all brackets given from
 *          standard input and colour code the matches to the terminal.
 *-----------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#include "stack.h"

#define NUM_COLOURS 16
#define RED "\033[0;31m"
#define YELLOW "\033[0;33m"
#define GREEN "\033[0;32m"
#define BLUE "\033[0;34m"
#define MAGENTA "\033[0;35m"
#define CYAN "\033[0;36m"
#define BLACK "\033[0;30m"
#define WHITE "\033[0;37m"
#define RED_BACK "\033[0;41m"
#define YELLOW_BACK "\033[0;43m"
#define GREEN_BACK "\033[0;42m"
#define BLUE_BACK "\033[0;44m"
#define MAGENTA_BACK "\033[0;45m"
#define CYAN_BACK "\033[0;46m"
#define BLACK_BACK "\033[0;40m"
#define WHITE_BACK "\033[0;47m"
#define NORMAL "\033[0m"

int main(int argc, char **argv)
{
#define SEPARATION_CHAR ' '
#define OPEN_BRACKET '('
#define CLOSE_BRACKET ')'
#define NEWLINE '\n'
   
    int index;
    int popped;
    int stringLength;
    int colourIdx;

    char currChar;
    char *string = NULL;
    char *colourArray[] = {RED, YELLOW, GREEN, BLUE, MAGENTA, CYAN, BLACK, WHITE,
                            RED_BACK, YELLOW_BACK, GREEN_BACK, BLUE_BACK, MAGENTA_BACK,
                            CYAN_BACK, BLACK_BACK, WHITE_BACK};
    char **colours = NULL;
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
                    // Distance between separation character and string start is length of input
                    stringLength = separation - string;

                    colours = malloc(sizeof(RED) * stringLength);

                    // Initialise all "colours" to be regular
                    for(int i = 0; i < stringLength; i++)
                    {
                        colours[i] = NORMAL;
                    }

                    colourIdx = 0;
                    myStack = create_stack();

                    // Pair matching bracket indicies to alike colours
                    for(int i = 0; i < stringLength; i++)
                    {
                        // While iterating over string, push open bracket postions to the stack
                        if(string[i] == OPEN_BRACKET)
                        {
                            push(myStack, i);
                        }
                        // pop open bracket position to match a found closed bracket
                        else if(string[i] == CLOSE_BRACKET)
                        {
                            // If able to pop, then a pair was found
                            if(pop(myStack, &popped))
                            {
                                // Set index pair to be the same colour
                                colours[popped] = colourArray[colourIdx];
                                colours[i] = colourArray[colourIdx];
                                colourIdx++;

                                if(colourIdx == NUM_COLOURS)
                                {
                                    colourIdx = 0;
                                }
                            }
                        }
                    }
                    destroy_stack(myStack);
                    
                    // Print each character based on given colour from colours
                    for(int i = 0; i < stringLength; i++)
                    {
                        printf("%s%c", colours[i], string[i]);
                    }
                    printf("\n");
                    
                    free(colours);
                }
                else
                {
                    printf("%sNo instance of a separation character found.\n", NORMAL);
                }
            }

            free(string);
        }
    }
        
    printf("%sAll test cases complete.\n", NORMAL);

    return EXIT_SUCCESS;
}
