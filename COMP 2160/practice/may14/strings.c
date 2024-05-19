#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// forward declarations
int string_length(char string[]);
/**
 * Compare tow string to one another for equality.
 *
 * args:
 *  string1: the first string
 *  str1_length: the length of string1
 *  string2: the second string
 *  str2_length: length of string2
 * return:
 *  true if equal, false if not
*/
bool string_compare(char string1[], int str1_length, 
                    char string2[], int str2_length);

/**
 * Copy form source to target the specified number of characters
 *
 * args:
 *  source: where I am copying from
 *  character: the number of characters to copy
 * Return:
 * 	the address of where the copy is.
 */
char *string_copy(char source[], int characters);

int main(int argc, char **argv)
{
    char name[] = "Franklin";
    char cat[] = "Walter";

#define NEW_NAME_SIZE 50
    char new_name[NEW_NAME_SIZE] = {0};

    int length = string_length(name);

    bool equal = string_compare(name, length, cat, string_length(cat));


    printf("Name is %s, length: %d\n", name, length);

    if(equal)
    {
        printf("%s and %s are equal.\n", name, cat);
    }
    else
    {
        printf("%s and %s are not equal!\n", name, cat);
    }
    
    printf("Name: %s, new_name: %s\n", name, new_name);
    string_copy(name, new_name, string_length(name));
    printf("Name: %s, new_name: %s\n", name, new_name);

	  return EXIT_SUCCESS;
}

int string_length(char string[])
{
    // NULL-terminated arrays ('\0')
    // COMP1010 and 1020: partially filled arrays and sentinels
    int length = 0;

    while(string[length] != '\0')
    {
        length++;
    }
    return length;
}

bool string_compare(char string1[], int str1_length, 
                    char string2[], int str2_length)
{
    bool equal = false;
    int current = 0;

    if(str1_length == str2_length)
    {
        // only check character if strings have the same length

        equal = true;

        // loop: for or while
        while(equal && current < str1_length)
        {
            if(string1[current] != string2[current])
            {
                equal = false;
            }
            current++;
        }
    }

    return equal;
}

void string_copy(char source[], char target[], int characters)
{
    int i = 0;
    // blindly copy up to 'character' character from source to target
    for(i = 0; i < characters; i++)
    {
        target[i] = source[i];
    }
    // add null byt at end of string
    target[i] = '\0';
}
