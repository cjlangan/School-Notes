#include <stdio.h>
#include <stdlib.h>

int main(void) 
{
    int n = 17;
    int steps = 0;

    int x = 2*n;
    int sum = 0;
    steps += 2;

    while(x > 0)
    {
        int y = 0;
        steps += 2;

        while(y < x)
        {
            sum += 3*y;
            y += 1;
            steps += 3;
        }
        x -= 2;
        steps += 2;
    }
    steps++;

    printf("Steps taken: %d\n", steps);
    printf("Value of sum: %d\n", sum);
}
