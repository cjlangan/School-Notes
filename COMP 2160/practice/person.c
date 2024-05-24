#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "person.h"

struct PERSON
{
#define MAX_LENGTH 20
    char name[MAX_LENGTH];
    int length;
    int age;
};

person *make_person(char *name, int length, int age)
{
    person *myPerson = NULL;

    myPerson = malloc(sizeof(person));

    if(myPerson != NULL)
    {
        strncpy(myPerson->name, name, length);
        myPerson->length = length;
        myPerson->age = age;
    }
    return myPerson;
}

void destroy_person(person *someone)
{
    assert(someone != NULL);

    free(someone);
}

int twice_age(person *someone)
{
    assert(someone != NULL);

    return 2 * (someone->age);
}
