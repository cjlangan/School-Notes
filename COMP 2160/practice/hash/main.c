#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "table.h"

#define MAX_LEN 100

int getInputLength(char *line);

int main(int argc, char **argv)
{
    char word[MAX_LEN] = {0};
    int length;
    table *t;
    t = makeTable(128);

    while(fgets(word, MAX_LEN, stdin) != NULL)
    {
        length = getInputLength(word);
        word[length] = '\0';

        insertItem(t, word, length);
    }

    bool boolean = hasItem(t, "Connor", 6);
    printf("Has 'Connor'?\t%d\n", boolean);

	  return EXIT_SUCCESS;
}

int getInputLength(char *line)
{
    int length = 0;

    while(line[length] != '\n')
    {
        length++;
    }
    return length;
}
