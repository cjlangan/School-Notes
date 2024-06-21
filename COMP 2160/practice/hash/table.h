#ifndef __TABLE_H
#define __TABLE_H

#include <stdbool.h>

typedef struct TABLE table;

table *makeTable(int size);

bool insertItem(table *t, char *item, int length);

bool deleteItem(table *t, char *item, int length);

bool hasItem(table *t, char *item, int length);

void emptyTable(table *t);

void destroyTable(table *t);

#endif
