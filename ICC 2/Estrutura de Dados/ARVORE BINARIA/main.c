#include <stdio.h>
#include <stdlib.h>

typedef struct NO* ArvBin;

struct NO{
    int info;
    struct NO *esq;
    struct NO *dir;
};

ArvBin* inicializa_arvore(){
	ArvBin* raiz = (ArvBin*)malloc(sizeof(ArvBin));
	if (raiz != NULL)
		*raiz = NULL;
	return raiz;
}

void libera_NO(struct NO* no){
	if(no == NULL)
		return;
	libera_NO(no->esq);
	libera_NO(no->dir);
	free(no);
	no = NULL;
}

void libera_ArvBin(ArvBin* raiz){
	if (raiz == NULL)
		return;
	libera_NO(*raiz);
	free(raiz);
}

int insere_ArvBin(ArvBin* raiz, int valor){
    if(raiz == NULL)
        return 0;
	struct NO* novo = (struct NO*) malloc(sizeof(struct NO));
	if(novo == NULL)
		return 0;
	novo->dir=NULL;
	novo->esq=NULL;
	novo->info=valor;
	if(*raiz == NULL)
		*raiz = novo;
	else {
		struct NO* atual = *raiz;
		struct NO* ant = NULL;
		while(atual != NULL){
			ant = atual;
			if(valor == atual->info){
				free(novo);
				return 0;
			}
			if(valor > atual->info)
				atual = atual->dir;
			else
				atual = atual->esq; 
		}
		if(valor > ant->info)
			ant->dir = novo;
		else 
			ant->esq = novo;
	}
	return 1;
}	

int estaVazia_ArvBin(ArvBin *raiz){
	if(raiz == NULL)
		return 1;
	if(*raiz == NULL)
		return 1;
	return 0;
}

int totalNO_ArvBin(ArvBin *raiz){
    if (raiz == NULL)
        return 0;
    if (*raiz == NULL)
        return 0;
    int alt_esq = totalNO_ArvBin(&((*raiz)->esq));
    int alt_dir = totalNO_ArvBin(&((*raiz)->dir));
    return(alt_esq + alt_dir + 1);
}


int altura_ArvBin(ArvBin* raiz){
	if(raiz == NULL)
		return 0;
	if (*raiz == NULL)
		return 0;
	int alt_esq = altura_ArvBin(&((*raiz)->esq));
	int alt_dir = altura_ArvBin(&((*raiz)->dir)); 
	if (alt_esq > alt_dir)
		return (alt_esq +1);
	else 
		return(alt_dir +1);
}

struct NO* remove_atual(struct NO* atual){
	struct NO *no1, *no2;
	if(atual->esq == NULL){
		no2 = atual->dir;
		free(atual);
		return no2;
	}
	no1 = atual;
	no2 = atual->esq;
	while(no2->dir != NULL){
		no1 = no2;
		no2 = no2->dir;
	}
	if(no1 != atual){
		no1->dir = no2->esq;
		no2->esq = atual->esq;
	}
	no2->dir = atual->dir;
	free(atual);
	return no2;
}


int remove_ArvBin(ArvBin* raiz, int valor){
	if(raiz == NULL)
		return 0;
	struct NO* ant = NULL;
	struct NO* atual = *raiz;
	while(atual != NULL){
		if (valor == atual->info){
			if(atual == *raiz)
				*raiz = remove_atual(atual);
			else {
				if(ant->dir == atual)
					ant->dir = remove_atual(atual);
				else 
					ant->esq = remove_atual(atual);
			}
			return 1;
		}
		ant = atual;
		if(valor >atual->info)
			atual = atual->dir;
		else 
			atual = atual->esq;
	}
}	

void emOrdem_ArvBin(ArvBin* raiz){
	if (raiz == NULL)
		return;
	if(*raiz != NULL){
		emOrdem_ArvBin(&((*raiz)->esq));
		printf("%d\n", (*raiz)->info);
		emOrdem_ArvBin(&((*raiz)->dir));
	}
}

int main(){
	int x,y;
	ArvBin* raiz =  inicializa_arvore();
	insere_ArvBin(raiz, 5);
	remove_ArvBin(raiz, 5);
	emOrdem_ArvBin(raiz);
	printf("\n");
	insere_ArvBin(raiz, 5);
	insere_ArvBin(raiz, 6);
	insere_ArvBin(raiz, 4);
	insere_ArvBin(raiz, 3);
	insere_ArvBin(raiz, 7);
	x = altura_ArvBin(raiz);
	y = totalNO_ArvBin(raiz);
	printf("A altura eh %d, e o numero de nos eh %d \n", x, y);
	emOrdem_ArvBin(raiz);
	printf("\n");
	remove_ArvBin(raiz, 6);
	x = altura_ArvBin(raiz);
	y = totalNO_ArvBin(raiz);
	printf("A altura eh %d, e o numero de nos eh %d \n", x, y);	
	emOrdem_ArvBin(raiz);
	printf("\n");
	remove_ArvBin(raiz, 5);
	x = altura_ArvBin(raiz);
	y = totalNO_ArvBin(raiz);	
	printf("A altura eh %d, e o numero de nos eh %d \n", x, y);
	emOrdem_ArvBin(raiz);
	libera_ArvBin(raiz);
}
