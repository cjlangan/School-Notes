#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "strings.h"

int total_tests = 0;
int success_tests = 0;

void test_make_string(void)
{
    string *s;

    s = make_string("Hello, world", 12);

    if(s != NULL)
    {
        printf("PASS: Able to make a string.\n");
        success_tests++;
    }
    else
    {
        printf("FAIL: Not able to make a string.\n");
    }

    total_tests++;

    destroy_string(s);
}

void test_char_at_general(void)
{
    char *input = "Franklin";
    string *s = make_string(input, strlen(input));
    
    char expected, returned;

    for(int i = 0; i < strlen(input); i++)
    {
        returned = char_at(s, i);
        expected = input[i];

        if(returned == expected)
        {
            success_tests++;
        }
        else
        {
            printf("FAIL: Did not get expected char (expected [%c], got [%c])", 
                                                        expected, returned);
        }
    }

    total_tests += strlen(input);

    destroy_string(s);
}

void test_char_at_edge_cases(void)
{
    // test the space case first
    char *input = "This is a string";
    string *s = make_string(input, strlen(input));

    if(char_at(s, 4) == ' ')
    {
        success_tests++;
        printf("PASS: Got a space when expecting a space from char_at\n");
    }
    else
    {
        printf("FAIL: Did not get a space when I expected a space\n");
    }

    total_tests++;

    destroy_string(s);
    // END space case =====================================
    
    // empty string is invalid data for char_at
    /*s = make_string("", 0);
    if(char_at(s, 0) == '\0')
    {
        success_tests++;
        printf("PASS: Got the null byte when getting index 0 of empty string");
    }
    else
    {
        printf("FAIL: Did not get null byte at index 0 of empty string");
    }*/

    s = make_string("a", 1);
    if(char_at(s, 0) == 'a')
    {
        success_tests++;
        printf("PASS: Got back 'a' from \"a\"[0]\n");
    }
    else
    {
        printf("FAIL: Did not get correct single character abck from "
                "one character long string.\n");
    }
    
    total_tests++;

    destroy_string(s);
    // =============================================
}

int main(int argc, char **argv)
{
    test_make_string();
    test_char_at_general();
    test_char_at_edge_cases();

    printf("Total tests run: %d\n"
            "Successful tests: %d\n"
            "Failed tests: %d\n", total_tests, success_tests, 
                                total_tests - success_tests);
	  
    return EXIT_SUCCESS;
}
