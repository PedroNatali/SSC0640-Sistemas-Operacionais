#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "fila.h"

fila_f* inicializa_fila(){
	fila_f* fila  = (fila_f*)malloc(sizeof(fila_f));
	fila->inicio = NULL;
	fila->fim = NULL;
	return fila;
}

void adiciona_elemento(fila_f* fila, int num){
	if(fila->inicio == NULL){
		dados_f* dados = (dados_f*)malloc(sizeof(dados_f));
		dados->idade = num;	
		dados->prox = NULL;
		fila->inicio = dados;
		fila->fim = dados;
	} else {
		dados_f* dados = (dados_f*)malloc(sizeof(dados_f));
		dados->idade = num;
		dados->prox = NULL;
		fila->fim->prox = dados;
		fila->fim = dados;
	}
}

void remove_elementos(fila_f* fila){
        dados_f* dados_aux = fila->inicio;
	if(dados_aux->prox == NULL){
		free(dados_aux);
		fila->inicio = NULL;
	} else {
        while(dados_aux->prox->prox != NULL)
		dados_aux = dados_aux->prox;
	free(dados_aux->prox);
	dados_aux->prox = NULL;
	}
}


void printa_fila(fila_f* fila){
	dados_f* dados_aux = fila->inicio;
	while(dados_aux != NULL){
		printf("%d", dados_aux->idade);
		dados_aux = dados_aux->prox;
	}
	printf("\n");
}

int main (){
	int OP, num, qtd;
	fila_f* fila = inicializa_fila();
	adiciona_elemento(fila, 1);
	printa_fila(fila);
	adiciona_elemento(fila, 2);
	printa_fila(fila);
	remove_elementos(fila);
	printa_fila(fila);
}	
//	while(1){
//		int OP, num, qtd;
//		fila_f* fila = inicializa_fila();
//
//		printf("Ola, essa eh sua lista, o que deseja fazer ? //\n");
//		printf("1- Adicionar um elemento\n");
//		printf("2- Remover um elemento \n");
//		printf("3- Imprimir a fila\n");
//		printf("\n");
//		scanf("%d", &OP);
//		switch(OP){
//			case 1:
//				printf("\n");
//				scanf("%d", &num);
//				adiciona_elemento(fila, num);
//				break;
//			case 2:
//				printf("\n");
//				remove_elementos(fila);
//				break;
//			case 3:
//				printf("\n");
//				printa_fila(fila);
//				break;
//			default:
//				printf("\n");
//				printf("INVALIDO\n");
//				break;
//		}
//		printf("\n");
//	}
//}

//
