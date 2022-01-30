/* Não modifique este arquivo. */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

LIST list_create(int idx)
{
    LIST list;
    list = (int *)malloc(sizeof(int)*idx);
    assert(list != NULL);
    return list;
}

void list_destroy(LIST list)
{
    free(list);
}

void list_insert(LIST list, int element, int idx)
{
    list[idx] = element;
}

int list_value(LIST list, int idx)
{
    return list[idx];
}
