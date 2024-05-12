//-----------------------------------------
// NAME: Connor Langan
// STUDENT NUMBER: 7993941
// COURSE: COMP 2160, SECTION: A01
// INSTRUCTOR: Franklin Bristow
// ASSIGNMENT: 1, QUESTION: 1
//
// REMARKS: A C program converted from PerfectlyBalanced.java.
//          Tests if brackets are balanced in given strings.
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
    // perfectly balanced string
    char perfect[] =
    "\n"
    "( )( )( )( )\n"
    "(o)(r)(b)(p)\n"
    "( )( )( )( )(g)\n"
    "(          ) /\n"
    "|         /\n";

    // Non-balanced string
    char shock[] =
    "\n"
    "^       ^\n"
    "( )     ( )\n"
    "     -\n"
    "     ( ))\n\n";

    // an empty string is balanced.
    testBalance("", 0, true);
    // a pair of parentheses is balanced.
    testBalance("()", 2, true);
    // a single closing parenthesis is unbalanced.
    testBalance(")", 1, false);
    // a single opening parenthesis is unbalanced.
    testBalance("(", 1, false);
    // multiple pairs of parentheses are balanced.
    testBalance("()()", 4, true);
    // inverted parentheses are unbalanced.
    testBalance(")(", 2, false);
    
    testBalance(perfect, 70, true);
    
    testBalance(shock, 41,  false);
    testBalance("(balanced)", 10, true);
    testBalance("unbalanced)", 11, false);
    testBalance("(((()))", 7, false);
    testBalance("(((((((", 7, false);
    testBalance("(()()(()))", 10, true);
    // check that our "fail" message appears correctly.
    // this is the only test case that should fail.
    testBalance("intentionally fail (", 20, true);
    // we shouldn't care about "NULL bytes"
    testBalance("(\0)", 3, true);

    printf("All test cases complete.\n");

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
//          then prints whether this matches the expected result
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
