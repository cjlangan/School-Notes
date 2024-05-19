#include <stdio.h>
#include <stdlib.h>
//#include <stdbool.h>

void munch_string(char array[]);

int main(int argc, char **argv)
{
#define MAX_LENGTH 10

    char array[MAX_LENGTH];

    munch_string(array);

	  return EXIT_SUCCESS;
}


void munch_string(char array[])
{
    printf("Yum strings\n");
}
