#include <stdio.h>
#include "btree.h"
#include "queue.h"

#include <assert.h>
#include <stdlib.h>
#include <ctype.h>

struct btree {
    char info;
    BTREE *sright, *sleft;
};



BTREE *btree_read() {
    BTREE* btree;
    char aux;
    assert(scanf("%c", &aux) == 1); //Le o "("
    assert(scanf("%c", &aux) == 1); //Le o "x"
    if(isalpha(aux)){
        btree = (BTREE *)malloc(sizeof(BTREE));
        assert(btree);
        btree->info = aux;
        btree->sleft = btree_read();
        btree->sright = btree_read();
        assert(scanf("%c", &aux) == 1);//Le o ")" 
    }
    else{
        btree = NULL;
    }
 
    return btree;
   
}

void btree_destroy(BTREE *btree) {
    if(btree->sleft != NULL){
        btree_destroy(btree->sleft);
        btree->sleft = NULL;
    }
    if(btree->sright != NULL){
        btree_destroy(btree->sright);
        btree->sright = NULL;
    }
    free(btree);
    btree = NULL;
}

void btree_dfs_pre_order(const BTREE *btree) {
    if(btree != NULL)
    {
        printf("%c", btree->info);
        btree_dfs_pre_order(btree->sleft);
        btree_dfs_pre_order(btree->sright);
    }

}

void btree_dfs_post_order(const BTREE *btree) {
     if(btree != NULL)
    {
        btree_dfs_post_order(btree->sleft);
        btree_dfs_post_order(btree->sright);
        printf("%c", btree->info);
    }

}

void btree_dfs_in_order(const BTREE *btree) {
    if(btree->sleft == NULL && btree->sright == NULL)
        printf("%c", btree->info);
    else{
        if(btree->sleft != NULL)
        btree_dfs_in_order(btree->sleft);
        printf("%c", btree->info);
        if(btree->sright != NULL)
            btree_dfs_in_order(btree->sright);
    }
}

void btree_bfs(const BTREE *btree) {
    BTREE *aux;
    QUEUE *queue = queue_create();
    queue_enqueue(queue, (void *) btree);
    while(!queue_is_empty(queue)){
        aux = (BTREE *) queue_front(queue);
        if(aux->sleft != NULL)
            queue_enqueue(queue, (void *)aux->sleft);
        if(aux->sright != NULL)
            queue_enqueue(queue, (void *)aux->sright);
        printf("%c", aux->info);
        queue_dequeue(queue);
    }
    queue_destroy(queue);
}
