#include "expression.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include<ctype.h>

typedef struct tree TREE;

// caso desejar, pode alterar o conteúdo das structs abaixo
struct tree
{
	union
	{
		int value;
		char operator;
	};
	TREE *left;
	TREE *right;
};

struct expression
{
	TREE *root;
};
/*nao sei o que essa função faz
bool is_literal(const TREE *tree)
{
}

static TREE *literal_create(int value)
{
}
*/
static TREE *tree_read()
{
	char aux;
	TREE *tree;
	//while(scanf("%c", &aux) != EOF && aux != '\n'){
	scanf("%c", &aux);
	if(aux != '\n'){
		tree = (TREE *)malloc(sizeof(TREE));  //aqui nao está com TAD
		if(isdigit(aux)){
			tree->value = aux - '0';
			tree->left = NULL;
			tree->right = NULL;
		}
		else{
			tree->operator = aux;
			tree->left = tree_read();
			tree->right = tree_read();
		}
	}
	return tree;

}

EXPRESSION *expression_read()
{
	// caso desejar, pode alterar o conteúdo abaixo
	EXPRESSION *expression = (EXPRESSION *)malloc(sizeof(EXPRESSION));
	expression->root = tree_read();
	return expression;
}

void tree_destroy(TREE *tree)
{
    if(tree->left != NULL){
        tree_destroy(tree->left);
        tree->left = NULL;
    }
    if(tree->right != NULL){
        tree_destroy(tree->right);
        tree->right = NULL;
    }
	if(tree != NULL)
    	free(tree);
    //tree = NULL;
	
}

void expression_destroy(EXPRESSION *expression)
{
	// caso desejar, pode alterar o conteúdo abaixo
	tree_destroy(expression->root);
	free(expression);
	//expression = NULL;
}

void tree_print(TREE *tree)
{
	if(tree->left == NULL && tree->right == NULL){ //is value
		printf("%d", tree->value);
		return;
	}
	printf("(");
	tree_print(tree->left);
	printf("%c", tree->operator);
	tree_print(tree->right);
	printf(")");
}

void expression_print(EXPRESSION *expression)
{
	// caso desejar, pode alterar o conteúdo abaixo
	tree_print(expression->root);
}

static TREE *tree_reduce(TREE *tree)
{
	if(tree->left == NULL && tree->right == NULL){ //is value
		return tree;
	}
	tree_reduce(tree->left);
	tree_reduce(tree->right);			
	switch (tree->operator)
	{
	case '*':
		tree->value = tree->left->value * tree->right->value;
		break;
	
	case '/':
		tree->value = tree->left->value / tree->right->value;
		break;
	
	case '+':
		tree->value = tree->left->value + tree->right->value;
		break;
	
	case '-':
		tree->value = tree->left->value - tree->right->value;
		break;
	
	default:
		printf("\nDeu ruim"); //RETIRAR ESSA LINHA
		break;
	}

	tree_destroy(tree->left);
	tree->left = NULL;
	tree_destroy(tree->right);
	tree->right = NULL;
	/*
	free(tree->left);
	tree->left = NULL;
	free(tree->right);
	tree->right = NULL;
	*/
	return tree;
}

int expression_evaluate(EXPRESSION *expression)
{
	// caso desejar, pode alterar o conteúdo abaixo
	assert(expression->root != NULL);
	expression->root = tree_reduce(expression->root);
//	assert(is_literal(expression->root));    nao sei o que essa função faz
	return expression->root->value;
}
