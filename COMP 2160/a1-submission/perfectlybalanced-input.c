//-----------------------------------------
// NAME: Connor Langan
// STUDENT NUMBER: 7993941
// COURSE: COMP 2160, SECTION: A01
// INSTRUCTOR: Franklin Bristow
// ASSIGNMENT: 1, QUESTION: 2
//
// REMARKS: A modification of perfectlybalanced.c such that test cases
//          can be supplied through standard input. Still determines
//          if such cases' parenthesis are 'balanced'.
//-----------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

// isBalanced
//
// PURPOSE: Tests if every opening parenthesis '(' has
//          a matching closing parenthesis ')'
// INPUT PARAMETERS:
//      braces: input string to test
//      length: input string length
//      openCount: the number of opening parenthesis that
//                 have not been matched with yet.
// RETURN:
//      bool that indicates if string is balanced
bool isBalanced(char braces[], int length, int openCount);

// testBalance
//
// PURPOSE: Calls method to test if input is balanced
//          then prints whether this matches the expected result
// INPUT PARAMETERS:
//      braces: input string to test
//      length: input string length
//      expected: expected boolean of whether input is balanced or not
int testBalance(char braces[], int length, bool expected);

// prints string based off provided length
int printBraces(char braces[], int length);

// prints "true" or "false" based on given bool value
int printBoolStr(bool value);

// getInputLength
//
// PURPOSE: determines input string length, so reads up until
//          a space or a newline.
// INPUT PARAMETERS:
//      line: original line of text from input
// RETURN:
//      returns the length of the input string to be tested on
int getInputLength(char line[]);

#define SEPARATION_CHAR ' '
#define LINE_END '\n'
#define TRUTH_CHAR 't'
#define FALSE_CHAR 'f'

int main(void) 
{ 
#define MAX_LEN 100
    char string[MAX_LEN] = {0}; // full line string
    bool expected; // expected balance of input
    int length;

    // Read input until end of file
    while(fgets(string, MAX_LEN, stdin) != NULL)
    {
        expected = false;
        length = getInputLength(string);

        // character after input string should be ' '
        if(string[length] == SEPARATION_CHAR)
        {   
            // character after the bool character signifier should be '\n'
            if(string[length + 2] == LINE_END)
            {
                // bool character must be 't' or 'f'
                if(string[length + 1] == FALSE_CHAR || string[length + 1] == TRUTH_CHAR)
                {
                    // determine bool value from bool character
                    if(string[length + 1] == TRUTH_CHAR)
                    {
                        expected = true;
                    }
                    else
                    {
                        expected = false;
                    }
                    testBalance(string, length, expected); // send test case
                }
            }
        }
    }
    printf("All test cases complete.\n");

    return EXIT_SUCCESS;
}
// Refer to forward declaration description at top for getInputLength
int getInputLength(char line[])
{
    int length = 0;
    
    // Read until the line ends or the separation character is met to determine the length
    while(line[length] != SEPARATION_CHAR && line[length] != LINE_END)
    {
        length++;
    }
    return length;
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
// Prints "true" or "false" based off given bool value
int printBoolStr(bool isTrue)
{
    isTrue  ?  printf("true")  :  printf("false");

    return EXIT_SUCCESS;
}
// Refer to forward declaration description at top for testBalance
int testBalance(char braces[], int length, bool expected)
{
// Text Colours
#define RED "\033[0;31m"   //RED
#define RESET "\033[0m"    // Text Reset
#define GREEN "\033[0;32m" // GREEN

    bool balanced = isBalanced(braces, length, 0);

    if(balanced == expected)
    {
        printf("%sPASS%s: ", GREEN, RESET);
        printBraces(braces, length);
        printf(" is ");
        printBoolStr(balanced);
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
// Refer to forward declaration description at top for isBalanced
bool isBalanced(char braces[], int length, int openCount)
{
    bool balanced;
    
    // Cannot process a null string, and a negative count is logically impossible
    assert (braces != NULL);
    assert (openCount >= 0);

    if(length == 0)
    {
        // empty strings are balanced, also means we are done recursing
        balanced = openCount == 0;
    }
    else if(braces[0] == '(')
    {
        // Don't need to check for a set of parenthesis. Send the address
        // of the second character, essentially the substring without the first character
        // , so we must also decrease the length by one.
        balanced = isBalanced(&braces[1], length - 1, openCount + 1);
    }
    else if(braces[0] == ')')
    {
        // Check for opening parenthesis (>0) to 'close' the set off
        if(openCount > 0)
        {
            // decreasing count suggests a set has been closed
            balanced = isBalanced(&braces[1], length - 1, openCount - 1);
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
        balanced = isBalanced(&braces[1], length - 1, openCount);
    }
    return balanced;
}
