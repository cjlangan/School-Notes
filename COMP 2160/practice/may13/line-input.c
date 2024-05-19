#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(int argc, char **argv)
{
    
#define NAME_LENGTH 50
    char name[NAME_LENGTH];

    while(fgets(name, NAME_LENGTH, stdin) != NULL)
    {
        printf("Your name is: %s\n", name);
        printf("8th character is: %c\n", name[7]);
    }


	  return EXIT_SUCCESS;
}
