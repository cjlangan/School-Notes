#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// forward declarations
/**
 * Copy form source to target the specified number of characters
 *
 * args:
 *  source: where I am copying from
 *  character: the number of characters to copy
 * Return:
 * 	the address of where the copy is, address to first character.
 */
char *string_copy(char source[], int characters);

int main(int argc, char **argv)
{
    char name[] = "Franklinnnnnnnnnnnnnnnnnnnnnnnnnnnnnn";
    char cat[] = "walter";

    char *new_name = string_copy(name, strlen(name));
    
    printf("Original name: %s, new name: %s\n", name, new_name);
    printf("Original name: %p, new name: %p\n", name, new_name);

    char *cat_name = string_copy(cat, 6);

	  printf("Original name: %s, new name: %s, cat name: %s\n", name, new_name, cat_name);
    printf("Original name: %p, new name: %p, cat name: %p\n", name, new_name, cat_name);

  return EXIT_SUCCESS;
}

char *string_copy(char source[], int characters)
{
#define TARGET_LENGTH 50
    char target[TARGET_LENGTH] = {0};

    int i = 0;
    
    // fixed one problem
    // If want seg fault, delete the conditional
    if(characters < TARGET_LENGTH)
    {
        // blindly copy up to 'character' character from source to target
        for(i = 0; i < characters; i++)
        {
            target[i] = source[i];
        }
        // add null byt at end of string
        target[i] = '\0';
    }

    return target;
}
