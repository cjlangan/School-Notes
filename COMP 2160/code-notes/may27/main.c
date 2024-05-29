#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Double quotes mean look in this directory fo the header file
#include "strings.h"

int main(int argc, char **argv)
{
    string *myString;

    myString = make_string("Franklin", 8);

    printf("The 2nd character is: %c\n", char_at(myString, 2));

    // could do free(myString), but don't know what's in it.
    // free() is not recursive, 
    // just relaeses string pointer, won't work for linked list
    
    // call destroy_string cuntion to have library relaase all resources
    // taht it has internally acquired.
    destroy_string(myString);

    return EXIT_SUCCESS;
}
