//-----------------------------------------
// NAME: Connor Langan
// STUDENT NUMBER: 7993941
// COURSE: COMP 2160, SECTION: A01
// INSTRUCTOR: Franklin Bristow
// ASSIGNMENT: 1, QUESTION: 2
//
// REMARKS: Alteration of perfectlybalanced.c such that
//          test cases are supplied via standard input.
//          Tests whether strings are 'balanced' with
//          respect to their parenthesis.
//-----------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

bool isBalanced(char braces[], int length, int idx, int openCount);
int testBalance(char braces[], int length, bool expected);
int printBraces(char braces[], int length);
int printBoolStr(bool value);

// Text Colours
char RED[] = "\033[0;31m";   //RED
char RESET[] = "\033[0m";    // Text Reset
char GREEN[] = "\033[0;32m"; // GREEN

int main(void) 
{ 
#define MAX_LEN 100 // max input string length

    char string[MAX_LEN] = {0};
    int length = 0;
    char input;
    bool expected;
    char SEPARATION_CHAR = ' ';
    char TRUTH_CHAR = 't';
    char FALSE_CHAR = 'f';
    char NEWLINE = '\n';

    // Read in characters and add them to the string while input exists
    // Note: Proper input is of the form:
    // ()()(f)(())\0""$ t
    // Where only a spaced signifies the separation between the input (left)
    // and the expected truth value (t = true, f = false)
    do
    {
        input = getchar();

        // Signifies end of string input
        if(input == SEPARATION_CHAR)
        {
            input = getchar(); // Prospective input for expected bool

            // Check for incorrect termination of a line.
            // Must be (t or f) then \n.  e.g: t\n
            if((input != TRUTH_CHAR && input != FALSE_CHAR) || getchar() != NEWLINE)
            {
                // incorrect means ignore all input until next line
                while(getchar() != NEWLINE) {}
            }
            else
            {
                if(input == TRUTH_CHAR)
                {
                    expected = true;
                }
                else
                {
                    expected = false;
                }
                testBalance(string, length, expected);
            }
            length = 0; // reset for next string of input
        }
        // Ignore input and reset if over max allowed length
        else if(length == MAX_LEN)
        {
            while(getchar() != NEWLINE) {}
            length = 0;
        }
        // newline signifies a new piece of input
        else if(input == NEWLINE)
        {
            length = 0;
        }
        // add any other character to the string
        else
        {
            string[length++] = input;
        }
    }while(input != EOF);

    printf("All test cases complete.");

    return EXIT_SUCCESS;
}
// Prints a string based off its provided length
int printBraces(char braces[], int length)
{
    for(int i = 0; i < length; i++)
    {
        printf("%c", braces[i]);
    }
    return EXIT_SUCCESS;
}
// prints "true" or "false" based on given bool value
int printBoolStr(bool value)
{
    if(value)
    {
        printf("true");
    }
    else
    {
        printf("false");
    }
    return EXIT_SUCCESS;
}
//------------------------------------------------------
// testBalance
//
// PURPOSE: Calls method to test if in input is balanced
//          then prints whether actual matches the expected result
// INPUT PARAMETERS:
//      braces: input string to test
//      length: input string length
//      expected: expected boolean of whether input is balanced or not
//------------------------------------------------------
int testBalance(char braces[], int length, bool expected)
{
    bool balanced = isBalanced(braces, length, 0, 0);

    if(balanced == expected)
    {
        printf("%sPASS%s: ", GREEN, RESET);
        printBraces(braces, length);
        printf(" is ");
        printBoolStr(expected);
        printf(" as expected.\n");
    }
    else
    {
        printf("%sFAIL%s: test case ", RED, RESET);
        printBraces(braces, length);
        printf(" is ");
        printBoolStr(balanced);
        printf(" not as expected.\n");
    }
    return EXIT_SUCCESS;
}
//------------------------------------------------------
// isBalanced
//
// PURPOSE: Tests if every opening parenthesis '(' has
//          a matching closing parenthesis ')'
// INPUT PARAMETERS:
//      braces: input string to test
//      length: input string length
//      idx: current index of the input string
//      openCount: the number of opening parenthesis that
//                 have not been matched with yet.
//------------------------------------------------------
bool isBalanced(char braces[], int length, int idx, int openCount)
{
    bool balanced;
    
    // Cannot process a null string, and a negative count is logically impossible
    assert (braces != NULL);
    assert (openCount >= 0);

    if(idx == length)
    {
        // empty strings are balanced, also means we are done recursing
        balanced = openCount == 0;
    }
    else if(braces[idx] == '(')
    {
        // Don't need to check for a set of parenthesis, move to next
        // idx and increase count
        balanced = isBalanced(braces, length, idx + 1, openCount + 1);
    }
    else if(braces[idx] == ')')
    {
        // Check for opening parenthesis (>0) to 'close' the set off
        if(openCount > 0)
        {
            // decreasing count suggests a set has been closed
            balanced = isBalanced(braces, length, idx + 1, openCount - 1);
        }
        else
        {
            // if no opening parenthesis to match, then not balanced
            balanced = false;
        }
    }
    else
    {
        // ignore anything that's not a parenthesis
        balanced = isBalanced(braces, length, idx + 1, openCount);
    }

    return balanced;
}
