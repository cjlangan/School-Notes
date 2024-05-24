#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int main(int argc, char **argv)
{
    
#define NAME_LENGTH 5
    char name[NAME_LENGTH] = {0};


    // Push a 'stack frame' onto the runtime stack
    printf("Enter your name: ");
    while(fgets(name, NAME_LENGTH, stdin) != NULL)
    {
        // This replaces the newline at the end of the string
        name[strlen(name) - 1] = '\0';

        printf("Your name is: %s!!!!!!!!!!\n", name);
        printf("8th character is: %c\n", name[7]);
        printf("Enter your name: ");
    }


	  return EXIT_SUCCESS;
}
