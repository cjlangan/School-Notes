#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX_STRING_LENGTH 10

/**
 * Get a substring of the input string, from the specified start all the way to
 * the end of the string. Output is placed in `out`.
 *
 * Args:
 *  in:    The input buffer, this is where we're copying from. Must not be NULL. 
 *         Must be a valid C string (ends with '\0').
 *  start: The index in the input buffer where we're going to start copying
 *         from. Must be >= 0. Must be less than the length of `in`.
 *  out:   The output buffer, where we're copying to. Must not be NULL. Will
 *         contain a string that is (strlen(in) - start) in length.
 */
void substr(char *in, int start, char *out);

int main(void)
{
    char *string = "This is a really long string, like super long. I still don't understand what domain expansion means.";
    char dest[MAX_STRING_LENGTH] = {0};

    printf("string is %s\n", string);
    substr(string, 2, dest);
    printf("string is %s and dest is %s\n", string, dest);
    return EXIT_SUCCESS;
}

void substr(char *in, int start, char *out)
{
    assert( in != NULL );
    assert( in[strlen(in)] == '\0' );
    assert( start >= 0 && start < strlen(in) );
    assert( out != NULL );

    int i;

    for (i = start; i < strlen(in); i++)
    {
        // i - start because we're writing to the beginning of 
        // out (i.e., out[0]), but starting at in[start].
        out[i - start] = in[i];
    }

    // add the null byte to the string
    out[i - start] = '\0';

    assert( strlen(out) == strlen(in) - start );
}
