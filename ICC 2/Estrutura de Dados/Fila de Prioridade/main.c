#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 50

struct paciente {
	int prio;
	char nome[20];
};

typedef struct FilaP{
	int qtd;
	struct paciente dados[MAX];
} FilaPrio ;


FilaPrio* cria_FilaPrio(){
	FilaPrio* fp = (FilaPrio*)malloc(sizeof(FilaPrio));
	if(fp != NULL)
        fp->qtd = 0;
    return fp;
}

void libera_FilaPrio(FilaPrio* fp){
	free(fp);
}
	
int consulta_FilaPrio(FilaPrio* fp, char* nome){
	if(fp == NULL || fp->qtd == 0)
		return 0;
	strcpy(nome, fp->dados[fp->qtd-1].nome);
	return 1;
}
	
int insere_FilaPrio(FilaPrio* fp, char *nome, int prioridade){
	if(fp == NULL)
		return 0;
	if(fp->qtd == MAX)//fila cheia
        	return 0;
	int i = fp->qtd-1;
	while(i>=0 && fp->dados[i].prio >= prioridade){
		fp->dados[i+1] = fp->dados[i];
		i--;
	}
	strcpy(fp->dados[i+1].nome,nome);
	fp->dados[i+1].prio = prioridade;
	fp->qtd ++;
	return 1;
}

int remove_FilaPrio(FilaPrio* fp){
	if(fp == NULL)
		return 0;
	if(fp->qtd == 0)
		return 0;
	fp->qtd--;
	return 1;
}

int tamanho_FilaPrio(FilaPrio* fp){
	if(fp == NULL)
		return 0;
	else 
		return fp->qtd;
}

int estaCheia_FilaPrio(FilaPrio* fp){
    if(fp == NULL)
        return -1;
    return (fp->qtd == MAX);
}

int estaVazia_FilaPrio(FilaPrio* fp){
    if(fp == NULL)
        return -1;
    return (fp->qtd == 0);
}

void imprime_FilaPrio(FilaPrio* fp){
    if(fp == NULL)
        return;
    int i;
    for(i=fp->qtd-1; i >=0 ; i--){
        printf("Prio: %d \tNome: %s\n",fp->dados[i].prio,fp->dados[i].nome);
    }
}

int main(){
	FilaPrio* fp = cria_FilaPrio();
	insere_FilaPrio(fp, "Joao",1);
	insere_FilaPrio(fp, "Marcos",2);
	insere_FilaPrio(fp, "Pedro",5);	
	insere_FilaPrio(fp, "Jefferson",3);
	insere_FilaPrio(fp, "Luisa",4);
	imprime_FilaPrio(fp);
	printf("\n\n");
	insere_FilaPrio(fp, "Renan",6);
	imprime_FilaPrio(fp);
	printf("\n\n");
	remove_FilaPrio(fp);
	imprime_FilaPrio(fp);

}
