#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "zones.h"

int main(void)
{
    char *hello  = "Hello!!";
    char *kraken = "Kraken";
    char *copy1  = NULL;
    char *copy2  = NULL;
    unsigned char *numbers = NULL; // want each number to be one byte in size

    zone *z = make_zone( 16 ); // allocate a 16 byte zone

    if ( z != NULL )
    {
        copy1 = zalloc( z, strlen( hello ) + 1 ); // 8 bytes

        if ( copy1 != NULL )
        {
            strncpy( copy1, hello, strlen( hello ) );
            printf("The original is %s at %p\n"
                   "The copy is %s at %p\n", hello, hello, copy1, copy1);
        }

        numbers = zalloc( z, 5 * sizeof( unsigned char ) ); // 5 bytes

        if ( numbers != NULL )
        {
            numbers[0] = 42;
            numbers[1] = 42;
            numbers[2] = 42;
            numbers[3] = 42;
            numbers[4] = 42;
        }

        zfree( z, copy1 ); // release the string

        copy2 = zalloc( z, strlen( kraken ) + 1 ); // 7 bytes
        if ( copy2 != NULL )
        {
            strncpy( copy2, kraken, strlen( kraken ) );
            printf("The original is %s at %p\n"
                   "The copy is %s at %p\n", kraken, kraken, copy2, copy2);
        }
    }

    zdump(z);

    destroy_zone(z); // Look, ma! No `free`!

    // if I run this with `valgrind`, I should get no leaks possible even
    // though I "forgot" to zfree two different zalloc.

    return EXIT_SUCCESS;
}
