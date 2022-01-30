#include "bst.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define TRUE 1;
#define FALSE 0;
typedef struct tree TREE;
struct tree {
	int info;
	TREE *sleft, *sright;
};

struct bst {
    TREE *root;
};

BST *bst_create() {
    BST *bst;
    bst = (BST *)malloc(sizeof(BST));
    assert(bst);
    bst->root = NULL;
    return bst;
}

void tree_destroy(TREE *tree){
    if(tree->sleft != NULL){
        tree_destroy(tree->sleft);
        tree->sleft = NULL;
    }
    if(tree->sright != NULL){
        tree_destroy(tree->sright);
        tree->sright = NULL;
    }
    free(tree);
    tree = NULL;
}
void bst_destroy(BST *bst) {
    tree_destroy(bst->root);
    free(bst);
    bst = NULL;
}
//precisa mesmo desse?
/*
static TREE *tree_create(int value) {
}
*/
static TREE *tree_insert(TREE *tree, int value) {
    if(tree == NULL){
       // printf("PRIMEIRO: %d", value);
        tree = (TREE *)malloc(sizeof(TREE));
        tree->info = value;
        tree->sleft = NULL;
        tree->sright = NULL;
    }
    else if(value < tree->info){
        tree->sleft = tree_insert(tree->sleft, value);
    }
    else if(value > tree->info){
        tree->sright = tree_insert(tree->sright, value);
    }
    return tree;
}

void bst_insert(BST *bst, int value) {
    bst->root = tree_insert(bst->root, value);
}

static int left_most_child(TREE **tree) {
    TREE *aux;
    int value;
    if((*tree)->sleft != NULL)
        value = left_most_child(&(*tree)->sleft);
    else{
        value = (*tree)->info;
        aux = *tree;
        *tree = (*tree)->sright;
        free(aux);
    }
    return value;
}
//quero trocar para void
void tree_remove(TREE **tree, int value) {
    TREE *aux;
    if(*tree != NULL){
        if(value < (*tree)->info)
            tree_remove(&(*tree)->sleft, value); // busca a esquerda
        else if(value > (*tree)->info)
            tree_remove(&(*tree)->sright, value);    // busca a direita
        else if((*tree)->sleft == NULL && (*tree)->sright == NULL){
            //caso 1, folha
            free(*tree);
            *tree = NULL;
        }
        else if((*tree)->sleft == NULL){
            //caso 2, com um unico filho (direito)
            aux = *tree;
            *tree = (*tree)->sright;
            free(aux);
        }
        else if((*tree)->sright == NULL){
            //caso 2, com um unico filho (esquerdo)
            aux = *tree;
            *tree = (*tree)->sleft;
            free(aux);
        }
        else{
            //caso 3, com dois filhos
            (*tree)->info = left_most_child(&(*tree)->sright);
        }
        
    }
}

void bst_remove(BST *bst, int value) {
    if(bst_search(bst, value))
        tree_remove(&bst->root, value);
}

static bool tree_search(const TREE *tree, int value) {
    if(tree == NULL)
        return FALSE;
    if(value == tree->info)
        return TRUE;
    if(value < tree->info)
        return tree_search(tree->sleft, value);
    else
        return tree_search(tree->sright, value);
}

bool bst_search(const BST *bst, int value) {
    return tree_search(bst->root, value);
}

static int tree_height(const TREE *tree) {
    int max, left_height, right_height;
    if(tree == NULL)
        return -1;
    left_height = tree_height(tree->sleft);
    right_height = tree_height(tree->sright);
    max = (left_height > right_height)?left_height:right_height;
    return max + 1;
}

int bst_height(const BST *bst) {
    return tree_height(bst->root);
}

static void tree_print(const TREE *tree) {
    printf("(");
    if(tree == NULL){ //caso no eh folha
        printf(")");
        return;
    }
    printf("%d", tree->info);
    tree_print(tree->sleft);
    tree_print(tree->sright);
    printf(")");
}

void bst_print(const BST *bst) {
    tree_print(bst->root);
}
