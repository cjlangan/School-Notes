#include <stdio.h>

extern int counter;

void print_counter(void);

int main(void)
{

    printf("In main(), counter is %d\n", counter);
    print_counter();
    counter++;
    printf("In main(), counter is %d\n", counter);
    print_counter();
}
