#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include <string.h>

lista_t* criar_lista(){
	lista_t* lista = (lista_t*)malloc(sizeof(lista_t));
	lista->inicio = NULL;
	lista->fim= NULL;
	return lista;
}
	

	
void inserir(lista_t* lista, char nome[50], int idade){
	if(lista->inicio == NULL){
		dados_t* dados = (dados_t*)malloc(sizeof(dados_t));
		strcpy(dados->nome, nome);
		dados->idade = idade;
		dados->prox = NULL;
		lista->inicio = dados;
		lista->fim = dados;
	} else {
		dados_t* dados = (dados_t*)malloc(sizeof(dados_t));
		strcpy(dados->nome, nome);
		dados->idade = idade;
		dados->prox = NULL;
		lista->fim->prox = dados;
		lista->fim = dados;
	}
}	

void print_lista(lista_t* lista){
	dados_t* dados_aux = lista->inicio;
	while(dados_aux != NULL){ 
		printf("Nome:  %s -",dados_aux->nome);
		printf("Idade: %d\n", dados_aux->idade);
		dados_aux = dados_aux->prox;
	}
}	

void apagar_item(lista_t* lista){
        dados_t* dados_aux = lista->inicio;
	if(dados_aux->prox == NULL){
		free(dados_aux);
		lista->inicio = NULL;
	} else {
        while(dados_aux->prox->prox != NULL)
		dados_aux = dados_aux->prox;
	free(dados_aux->prox);
	dados_aux->prox = NULL;
	}
}



void excluir(dados_t* dados);
 
int main(){
	char nome[50] = "Guilherme ADA";
	int idade = 21;

	lista_t* lista = criar_lista();
	inserir(lista, nome, idade);
	inserir(lista, "Castanhari", 5);
	print_lista(lista);
	apagar_item(lista);
	print_lista(lista);

}
