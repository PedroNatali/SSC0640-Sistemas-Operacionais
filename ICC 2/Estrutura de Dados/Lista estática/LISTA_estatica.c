#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#define MAX 100
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

typedef struct aluno{
	int matricula;
	char nome[30];	
} ALUNO ;

typedef struct lista {
	int qtd;
	ALUNO dados[MAX];
} LISTA ;

LISTA* cria_lista(){
	LISTA* lista = (LISTA*)malloc(sizeof(LISTA));
	if(lista != NULL)
		lista->qtd = 0;
	return lista;
}	

int adiciona_aluno(LISTA* lista, int matricula, char nome[30]){
	if(lista == NULL)
		return 0;
	if(lista->qtd == MAX)
        return 0;
	lista->dados[lista->qtd].matricula = matricula;
	strcpy(lista->dados[lista->qtd].nome, nome);
	lista->qtd++;
	return 1;
}

void printa_lista(LISTA* lista){
	if(lista == NULL)
		return;
	int i;
	for(i=0; i< lista->qtd; i++){
		printf("%d %s", lista->dados[i].matricula, lista->dados[i].nome);
		printf("\n");
	}
	printf("\n");
}

int remove_ultimoaluno(LISTA* lista){
	if(lista == NULL)
		return 0;
	if(lista->qtd == 0)
        return 0;
    lista->qtd--;
    return 1;
} 

void libera_lista(LISTA* lista){
    free(lista);
}

int main(){
	
	LISTA* lista = cria_lista();
	adiciona_aluno(lista, 1, "Marcos");
	printa_lista(lista);
	adiciona_aluno(lista, 2, "Joao");
	printa_lista(lista);
	remove_ultimoaluno(lista);
	printa_lista(lista);
}
