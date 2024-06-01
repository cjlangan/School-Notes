#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void counter(void);

int main(int argc, char **argv)
{
	counter();
	counter();
	counter();
	counter();

	return EXIT_SUCCESS;
}

void counter(void)
{
	// initialisation only happens once in first call
	// then retains value
	static int counter = 0;

	counter++;

	printf("Coun inside function %d\n", counter);
}
