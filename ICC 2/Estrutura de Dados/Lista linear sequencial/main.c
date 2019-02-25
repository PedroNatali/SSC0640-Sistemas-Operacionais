#include <stdio.h>
#include <stdlib.h>	
#define MAX 50

typedef int TIPOCHAVE;

typedef struct{
	TIPOCHAVE chave;
} REGISTRO ;

typedef enum{
false, true
} bool;

typedef struct {
	REGISTRO A[MAX+1];
	int nroElem;	
} LISTA ; 

void inicializarLista(LISTA* lista){
	lista->nroElem = 1;
}

int tamanho(LISTA* lista){
	return lista->nroElem;
}

void exibirLista(LISTA* lista){
	int i;
	printf("Lista: \" ");
	for(i=0; i<lista->nroElem; i++)
		printf("%i  ", lista->A[i].chave);
	printf("\"\n");
}

int buscaBinaria(LISTA* lista, TIPOCHAVE ch){
	int esq, dir, meio;
	esq = 0;
	dir = lista->nroElem-1;
	while(esq <=dir) {
		meio = ((esq + dir) / 2);
		if(lista->A[meio].chave == ch)
			return meio;
		else {
			if(lista->A[meio].chave < ch)
				esq = meio +1;
			else
				dir = meio -1;
		}
	}
	return -1;
}

bool inserirElemListaOrd(LISTA* lista, REGISTRO reg){
	if(lista->nroElem >= MAX)
		return false;
	int pos = lista->nroElem;
	while(pos > 0 && lista->A[pos-1].chave > reg.chave){
		lista->A[pos] = lista->A[pos-1];
		pos --;
	}
	lista->A[pos] = reg;
	lista->nroElem++;
}

bool excluirElemLista(TIPOCHAVE ch, LISTA* lista){
	int pos, j;
	pos = buscaBinaria(lista, ch);
	if(pos == -1)
		return false;
	for(j = pos; j < lista->nroElem-1; j++)
		lista->A[j] = lista->A[j+1];
	lista->nroElem--;
	return true;
}

void renicializarLista(LISTA* lista){
	lista->nroElem =0;
}

int main() {
void inicializarLista(lista);
void exibirLista(lista);
int tamanho(lista);
bool inserirElemListaOrd(lista);
void exibirLista(lista);
int tamanho(lista);
int buscaBinaria(lista);
bool excluirElemLista(lista);
void exibirLista(lista);
int tamanho(lista);
void renicializarLista(lista);
void exibirLista(lista);
int tamanho(lista);
	return 0;
}
