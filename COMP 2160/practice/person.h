#ifndef __PERSON_H
#define __PERSON_H

typedef struct PERSON person;

person *make_person(char *name, int length, int age);

void destroy_person(person *someone);

int twice_age(person *someone);

#endif
