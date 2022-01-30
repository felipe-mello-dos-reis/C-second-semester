/********************************************/
/* Aluno: Felipe Mello dos Reis             */
/* CES-11: Algoritmos e Estruturas de Dados */
/********************************************/

#include "list.h"

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

struct list
{
	unsigned int size, max;
	int *p;
};

LIST *list_create(unsigned int max)
{
	LIST *list = (LIST *) malloc(sizeof(LIST));
	list->size = 0;
	list->max = max;
	list->p = (int *)malloc(sizeof(int)*max);
	return list;
}

void list_destroy(LIST *list)
{
	free(list->p);
	free(list);
	return;
}

unsigned int list_max(LIST *list) {
	return list->max;
}

unsigned int list_size(LIST *list) {
	return list->size;
}

void list_print(LIST *list, unsigned int idx) {
	int value = list_value(list, idx);
	if(value != -9999)
	{
		printf("%d\n", value);
	}
	return;
}


void list_insert(LIST *list, int value, unsigned int k) {
	if(k >= list->max || list->size >= list->max)
	{
		printf("ERRO\n");
		return;
	}
	else
	{
		list->size++;
		for(unsigned int i = list->size - 1; i > k; i--)
		{
			list->p[i] = list->p[i-1];
		}
		list->p[k] = value;
		return;
	}
}

void list_delete(LIST *list, unsigned int k) {
	if(k >= list->max)
	{
		printf("ERRO\n");
		return;
	}
	else
	{
		//list->size--;
		for(unsigned int i = k; i < list->max - 1; i++)
		{
			list->p[i] = list->p[i+1];
		}/*
		for(unsigned int i = list->size; i <= list->max; i++)
		{
			list->p[i] = EOF;
		}*/
		return;
	}
}

int list_value(LIST *list, unsigned int idx) {
	if(idx >= list->max)
	{
		printf("ERRO\n");
		return -9999;
	}
	else
	{
		return list->p[idx];
	}
}

void list_change(LIST *list, int value, unsigned int idx) {
	if(idx >= list->max)
	{
		printf("ERRO\n");
		return;
	}
	else
	{
		list->p[idx] = value;
		return;
	}
}
