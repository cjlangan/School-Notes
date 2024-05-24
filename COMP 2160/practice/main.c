#include <stdio.h>
#include <stdlib.h>

#include "person.h"

int main(int argc, char **argv)
{
    person *myPerson;

    myPerson = make_person("Connor", 6, 19);

    printf("Twice their age is: %d\n", twice_age(myPerson));

    destroy_person(myPerson);

    return EXIT_SUCCESS;
}
