#include "bst.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

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

TREE *tree_insert(TREE *tree, int value) {
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

void tree_dfs_inorder(const TREE *tree) {
    if(tree->sleft != NULL)
        tree_dfs_inorder(tree->sleft);
    printf("%d ", tree->info);
    if(tree->sright != NULL)
        tree_dfs_inorder(tree->sright);
}

void bst_destroy(BST *bst) {
    tree_destroy(bst->root);
    free(bst);
    bst = NULL;
}


void bst_insert(BST *bst, int value) {
    bst->root = tree_insert(bst->root, value);
}

void bst_dfs_inorder(const BST *bst) {
    tree_dfs_inorder(bst->root);
}
