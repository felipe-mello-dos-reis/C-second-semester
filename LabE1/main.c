#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "stack_extra.h"
#include "list.h"

typedef struct JOGADOR JOGADOR;
struct JOGADOR
{
	int posicao, num_imoveis;
	STACK *dado;
	STACK *imoveis_jogador;
};


void jogada (JOGADOR *, int *, int *);

int main()
{

	int contador, elemento;
	int *tab;
	JOGADOR *jogador_1;
	JOGADOR *jogador_2;

	jogador_1 = (JOGADOR *)malloc(sizeof(JOGADOR));
	assert(jogador_1 != NULL);
	jogador_2 = (JOGADOR *)malloc(sizeof(JOGADOR));
	assert(jogador_2 != NULL);


//	REGISTRO DO TABULEIRO;

	tab = list_create(16);
	for(int i = 1; i <= 15; i++)
	{
		assert(scanf("%d", &elemento) == 1);
		list_insert(tab, elemento, i);
	}


//	REGISTRO DOS DADOS DO JOGADOR 1

	contador = 0;
	STACK *dado_aux_1;
	dado_aux_1 = stack_create();
    while (contador <= 15)
    {
    	assert(scanf("%d", &elemento) == 1);
    	stack_push(dado_aux_1, elemento);
		contador+=elemento;
	}
	jogador_1->dado = stack_create();
	jogador_1->dado = stack_reverse(dado_aux_1);


//	REGISTRO DOS DADOS DO JOGADOR 2

	contador = 0;
	STACK *dado_aux_2;
	dado_aux_2 = stack_create();
    while (contador <= 15)
    {
    	assert(scanf("%d", &elemento)==1);
    	stack_push(dado_aux_2, elemento);
		contador+=elemento;
	}
	jogador_2->dado = stack_create();
	jogador_2->dado = stack_reverse(dado_aux_2);


//	REGISTRO DA LISTA DE PROPRIEDADES
	int *imoveis;
	imoveis = list_create(21);
	for(int i = 1; i <= 20; i++)
		list_insert(imoveis, 1, i);	//1 indica imovel DISPONIVEL, 0 indica imovel INDISPONIVEL
	jogador_1->imoveis_jogador = stack_create();
	jogador_2->imoveis_jogador = stack_create();


//	JOGO

	jogador_1->posicao = 0;
	jogador_2->posicao = 0;
	jogador_1->num_imoveis = 0;
	jogador_2->num_imoveis = 0;
	while(jogador_1->posicao <= 15 || jogador_2->posicao <= 15)
	{
		if(jogador_1->posicao <= 15)
			jogada(jogador_1, tab, imoveis);
		if(jogador_2->posicao <= 15)
			jogada(jogador_2, tab, imoveis);
	}


//	ENCERRAMENTO

	if(stack_isEmpty(jogador_1->imoveis_jogador) == 1)
	{
	//	printf("teste\n");
		printf("0\n");
	}
	else
	{
		stack_printBottomUp(jogador_1->imoveis_jogador);
	}
	if(stack_isEmpty(jogador_2->imoveis_jogador) == 1)
	{
		printf("0\n");
	}
	else
	{
		stack_printBottomUp(jogador_2->imoveis_jogador);
	}
	

//	RESULTADO FINAL

	if(jogador_1->num_imoveis > jogador_2->num_imoveis)
	{
		printf("1");
	}
	if(jogador_1->num_imoveis < jogador_2->num_imoveis)
	{
		printf("2");
	}
	if(jogador_1->num_imoveis == jogador_2->num_imoveis)
	{
		printf("3");
	}


//	LIBREAÇÃO DE MEMORIA

	list_destroy(tab);
	stack_destroy(dado_aux_1);
	stack_destroy(jogador_1->dado);
	stack_destroy(dado_aux_2);
	stack_destroy(jogador_2->dado);
	list_destroy(imoveis);
	stack_destroy(jogador_1->imoveis_jogador);
	stack_destroy(jogador_2->imoveis_jogador);
	free(jogador_1);
	free(jogador_2);
	return 0;
}

void jogada (JOGADOR *jogador, int *tab, int *imoveis)
{
	jogador->posicao += stack_top(jogador->dado);
	stack_pop(jogador->dado);
	if(jogador->posicao > 15)
		return;
	switch(list_value(tab, jogador->posicao))
	{
	case 0:
		//nada acontece
		break;
	case -1:
		//jogador deverá vender o ultimo imóvel adquirido
		if(stack_isEmpty(jogador->imoveis_jogador) == 1)
			break;
		else
		{
			list_insert(imoveis, 1, stack_top(jogador->imoveis_jogador));
			stack_pop(jogador->imoveis_jogador);
			jogador->num_imoveis--;
			break;
		}
	default:
		//jogador deverá comprar o imóvel de numero x, caso disponivel
		if(list_value(imoveis,list_value(tab, jogador->posicao)) == 0)
			break;
		else
		{
			list_insert(imoveis, 0, list_value(tab, jogador->posicao));
			stack_push(jogador->imoveis_jogador, tab[jogador->posicao]);
			jogador->num_imoveis++;
			break;
		}
	}
}
