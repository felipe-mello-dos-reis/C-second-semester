#include "queue.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

typedef struct node NODE;

struct node {
    void *element;
    NODE *next;
};

struct queue {
    NODE *begin, *end;
};

QUEUE *queue_create() {
    QUEUE *queue;
    queue = (QUEUE *)malloc(sizeof(QUEUE));
    queue->begin = (NODE *)malloc(sizeof(NODE));
    assert(queue->begin);
    queue->begin->next = NULL;
    queue->end = queue->begin;
    return queue;
}

void queue_destroy(QUEUE *queue) {
    while(queue_is_empty(queue) == 0)
        queue_dequeue(queue);
    free(queue->begin);
    free(queue);
    queue = NULL;
}

void queue_enqueue(QUEUE *queue, void *element) {
    queue->end->next = (NODE *)malloc(sizeof(NODE));
    queue->end->next->element = element;
    queue->end = queue->end->next;
    queue->end->next = NULL;
    
}

void queue_dequeue(QUEUE *queue) {
    assert(queue_is_empty(queue) == 0);
    NODE *aux = queue->begin->next->next;
    free(queue->begin->next);
    queue->begin->next = aux;
    if(queue->begin->next == NULL){
        queue->end = queue->begin;
    }
}

void *queue_front(const QUEUE *queue) {
    return queue->begin->next->element;
}

bool queue_is_empty(const QUEUE *queue) {
    if(queue->begin == queue->end)
        return 1;
    else
        return 0;
}
