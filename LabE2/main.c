#include <stdio.h>

#include "bst.h"

int main() {
  int value;
  BST *bst = bst_create();

  //freopen("./Testes/1.in", "r", stdin);


  while(scanf("%d", &value) != EOF && value != 9999){
    bst_insert(bst, value);
  }

  bst_dfs_inorder(bst);
  printf("\n");

  bst_destroy(bst);
}
