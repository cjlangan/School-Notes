#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h> // the ability to specify the number of bits in a variable

int main(int argc, char **argv)
{
    uint16_t colour = 0; //unsigned integer that takes 16 bitst, _t is type
    uint8_t r, g, b;

    r = 21;
    g = 0;
    b = 25;

    colour = ((b & 0x1f) << 10) | ((g & 0x1f) << 5) | (r & 0x1f);
    printf("The colour is: 0x%x\n", colour);

	  return EXIT_SUCCESS;
}
