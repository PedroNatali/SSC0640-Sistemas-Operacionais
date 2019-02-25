#include <stdio.h>
#include <stdlib.h>
#define MAX 50
#define INVALIDO -1

typedef int TIPOCHAVE;

typedef enum{
	false, true
}bool;

typedef struct{
	TIPOCHAVE chave;
} REGISTRO;

typedef struct{
	REGISTRO reg;
	int prox;
} ELEMENTO;

typedef struct{
	ELEMENTO A[MAX];
	int inicio;
	int dispo;
} LISTA;


void inicializarLista(LISTA* lista){
	int i;
	for(i=0; i<MAX-1; i++)
		lista->A[i].prox = i + 1;
	lista->A[MAX-1].prox = INVALIDO;
	lista->inicio = INVALIDO;
	lista->dispo = 0;
}

int tamanho(LISTA* lista){
	int i = lista->inicio;
	int tam = 0;
	while (i != INVALIDO){
		tam ++;
		i = lista->A[i].prox;
	}
	return tam;
}

void imprimeLista(LISTA* lista){
	int i = lista->inicio;
	printf("Lista : \" ");
	while (i != INVALIDO){
		printf("%i ", lista->A[i].reg.chave);
		i = lista->A[i].prox;
	}
	printf("\"\n");
}

int buscaSequencialOrd(LISTA* lista, TIPOCHAVE ch){
	int i = lista->inicio;
	while(i != INVALIDO && lista->A[i].reg.chave < ch)
		i = lista->A[i].prox;
	if (i != INVALIDO && lista->A[i].reg.chave == ch)
		return i;
	else 
		return INVALIDO;
}

int obterNo(LISTA* lista){
	int resultado = lista->dispo;
	if(lista->dispo != INVALIDO)
		lista->dispo = lista->A[lista->dispo].prox;
	return resultado;
}

bool inserirElemListaOrd(LISTA* lista, REGISTRO reg){
	if(lista->dispo == INVALIDO)
		return false;
	int ant = INVALIDO;
	int i = lista->inicio;
	TIPOCHAVE ch = reg.chave;
	while((i != INVALIDO) && (lista->A[i].reg.chave<ch)){
		ant = i;
		i = lista->A[i].prox;
	}
	if(i != INVALIDO && lista->A[i].reg.chave == ch)
		return false;
	i= obterNo(lista);
	lista->A[i].reg = reg;
	if (ant == INVALIDO){
		lista->A[i].prox = lista->inicio;
		lista->inicio = i;
	} else {
		lista->A[i].prox = lista->A[ant].prox;
		lista->A[ant].prox = i;
	}
	return true;
}

void devolverNO(LISTA* lista, int j){
	lista->A[j].prox = lista->dispo;
	lista->dispo = j;
}

bool excluirElemLista(LISTA* lista, TIPOCHAVE ch){
	int ant = INVALIDO;
	int i = lista->inicio;
	while ((i != INVALIDO) && (lista->A[i].reg.chave<ch)){
		ant = i;
		i = lista->A[i].prox;

	}
	if (i == INVALIDO || lista-> A[i].reg.chave != ch)
		return false;
	if (ant == INVALIDO)
		lista->inicio = lista->A[i].prox;
	else 
		lista->A[ant].prox = lista->A[i].prox;
	devolverNO(lista, i);
	return true;
}

void reinicializarLista(LISTA* lista){
	inicializarLista(lista);
}

int main(){
	void inicializarLista(lista);
	void imprimeLista(lista);
	bool inserirElemListaOrd(lista);
	void imprimeLista(lista);
	bool excluirElemLista(lista);
	void imprimeLista(lista);
}
