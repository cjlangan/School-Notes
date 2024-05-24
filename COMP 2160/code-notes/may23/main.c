#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Double quotes mean look in this directory fo the header file
#include "strings.h"

int main(int argc, char **argv)
{
    string *myString;

    myString = make_string("Franklin", 8);

    printf("The 4th character is: %c\n", char_at(myString, 4));

    destroy_string(myString);

    return EXIT_SUCCESS;
}
