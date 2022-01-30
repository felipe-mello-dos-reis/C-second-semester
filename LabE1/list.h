/* Não modifique este arquivo. */

#ifndef LIST_H
#define LIST_H


typedef int *LIST;

LIST list_create(int idx);

void list_destroy(LIST list);

void list_insert(LIST list, int element, int idx);

int list_value(LIST list, int idx);

#endif // LIST_H
