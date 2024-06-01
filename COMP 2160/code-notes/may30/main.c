#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// double quotes say "look in this directory"
// for the header file
#include "strings.h"

int main(int argc, char **argv)
{
    string *myString;

    myString = make_string("Franklin", 8);

    printf("The character at 2 is %c\n",
            char_at(myString, 2));

    // call destroy string function
    // to have the library release all
    // resources it has internally acquired:

    destroy_string( myString );
    myString = NULL;

    return EXIT_SUCCESS;
}
