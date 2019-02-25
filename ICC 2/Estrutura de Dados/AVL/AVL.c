#include<stdio.h>
#include<stdlib.h>

typedef struct NO* ArvAVL;

struct NO {
	int alt;
	int info;
	struct NO *esq;
	struct NO *dir;
};

ArvAVL* inicializa_arvore(){
	ArvAVL* raiz = (ArvAVL*)malloc(sizeof(ArvAVL));
	if (raiz != NULL)
		*raiz = NULL;
	return raiz;
}


int Maior (int x, int y){
	if(x>y)
		return x;
	else 
		return y;
}

int altura_NO(struct NO* no){
	if (no == NULL)
		return -1;
	else 
		return no->alt;
}

int Diff_Altura(struct NO* no){
	return labs(altura_NO(no->esq) - altura_NO(no->dir));
}

void RotacaoLL(ArvAVL *raiz){
	struct NO* no;
	no = (*raiz)-> esq;
	(*raiz)->esq = no->dir;
	no->dir = *raiz;
	(*raiz)->alt = Maior(altura_NO((*raiz)->esq), altura_NO((*raiz)->dir))+1;
	no->alt = Maior(altura_NO(no->esq), (*raiz)->alt) +1;
	*raiz = no;
}

void RotacaoRR(ArvAVL *raiz){
	struct NO* no;
	no = (*raiz)->dir;
	(*raiz)->dir = no->esq;
	no->esq = *raiz;
	(*raiz)->alt = Maior(altura_NO((*raiz)->esq), altura_NO((*raiz)->dir))+1;
	no->alt = Maior(altura_NO(no->dir), (*raiz)->alt) +1;
	*raiz = no;
}

void RotacaoRL(ArvAVL *raiz){
	RotacaoLL(&(*raiz)->dir);
	RotacaoRR(raiz);
}

void RotacaoLR(ArvAVL *raiz){
	RotacaoRR(&(*raiz)->esq);
	RotacaoLL(raiz);
}

int insere_ArvAVL(ArvAVL *raiz, int valor){
	int res;
	if(*raiz == NULL){
		struct NO* no = (struct NO*)malloc(sizeof(struct NO));
		if(no == NULL)
			return 0;
		no->alt = 0;
		no->dir = NULL;
		no->esq = NULL;
		no->info = valor;
		*raiz = no;
		return 1;
	}
	struct NO* atual = *raiz;
	if(valor < atual->info){
		if((res=insere_ArvAVL(&(atual->esq), valor))==1){
			if(Diff_Altura(atual)>=2){
				if(valor < (*raiz)->esq->info){
					RotacaoLL(raiz);
				} else {
					RotacaoLR(raiz);
				}
			}
		}
	} else {
		if(valor > atual->info){
			if((res=insere_ArvAVL(&(atual->dir), valor))==1){
				if(Diff_Altura(atual) >=2){
					if((*raiz)->dir->info < valor){
						RotacaoRR(raiz);
					}else{
						RotacaoRL(raiz);
					}
				}
			}
		}else{
				printf("Valor duplicado!!\n");
				return 0;
		}
	}		
		atual->alt  = Maior(altura_NO(atual->esq), altura_NO(atual->dir))+1;
	
	return res;
}
	
struct NO* procura_menor(struct NO* atual){
	struct NO* no1 = atual;
	struct NO* no2 = atual->esq;
	while(no2 != NULL){
		no1 = no2;
		no2 = no2->esq;
	}
	return no1;
}
	
int remove_ArvAVL(ArvAVL* raiz, int valor){
	if(*raiz == NULL){
		printf("Valor invalido!");
		return 0;
	}
	int res;
	if(valor < (*raiz)->info){
		if((res=remove_ArvAVL(&(*raiz)->esq, valor))==1){
			if(Diff_Altura(*raiz)>=2){
				if(altura_NO((*raiz)->dir->esq)
				<= altura_NO((*raiz)->dir->dir))
					RotacaoRR(raiz);
				else 
					RotacaoRL(raiz);
			}
		}
	}
	if( (*raiz)->info < valor){
		if((res=remove_ArvAVL(&(*raiz)->dir, valor))==1){
			if(Diff_Altura(*raiz)>=2){
				if(altura_NO((*raiz)->esq->dir)
				<= altura_NO((*raiz)->esq->esq))
					RotacaoLL(raiz);
				else 
					RotacaoLR(raiz);
			}
		}
	}
	if( (*raiz)->info == valor){
		if(((*raiz)->esq == NULL || (*raiz)->dir == NULL)){
			struct NO* antNo = (*raiz);
			if((*raiz)->esq != NULL)
				*raiz = (*raiz)->esq;
			else 
				*raiz = (*raiz)->dir;
			free(antNo);
		}else {
			struct NO* temp = procura_menor((*raiz)->dir);
			(*raiz)->info = temp->info;
			remove_ArvAVL(&(*raiz)->dir, (*raiz)->info);
			if(Diff_Altura(*raiz)>=2){
				if(altura_NO((*raiz)->esq->dir)
				<= altura_NO((*raiz)->esq->esq))
					RotacaoLL(raiz);
				else 
					RotacaoLR(raiz);
			}
		}
		if(*raiz != NULL)
			(*raiz)->alt = Maior(altura_NO((*raiz)->esq),altura_NO((*raiz)->dir)) +1;
		return 1;
	}
	
	(*raiz)->alt = Maior(altura_NO((*raiz)->esq), altura_NO((*raiz)->dir))+1;
	return	res;
}

int totalNO_ArvAVL(ArvAVL *raiz){
    if (raiz == NULL)
        return 0;
    if (*raiz == NULL)
        return 0;
    int alt_esq = totalNO_ArvAVL(&((*raiz)->esq));
    int alt_dir = totalNO_ArvAVL(&((*raiz)->dir));
    return(alt_esq + alt_dir + 1);
}


int altura_ArvAVL(ArvAVL* raiz){
	if(raiz == NULL)
		return 0;
	if (*raiz == NULL)
		return 0;
	int alt_esq = altura_ArvAVL(&((*raiz)->esq));
	int alt_dir = altura_ArvAVL(&((*raiz)->dir)); 
	if (alt_esq > alt_dir)
		return (alt_esq +1);
	else 
		return(alt_dir +1);
}


void emOrdem_ArvAVL(ArvAVL* raiz){
	if (raiz == NULL)
		return;
	if(*raiz != NULL){
		emOrdem_ArvAVL(&((*raiz)->esq));
		printf("%d\n", (*raiz)->info);
		emOrdem_ArvAVL(&((*raiz)->dir));
	}
}

		
int main(){
	int x,y;
	ArvAVL* raiz =  inicializa_arvore();
	insere_ArvAVL(raiz, 5);
	remove_ArvAVL(raiz, 5);
	x = altura_ArvAVL(raiz);
	y = totalNO_ArvAVL(raiz);
	printf("A altura eh %d, e o numero de nos eh %d \n", x, y);
	emOrdem_ArvAVL(raiz);
	printf("\n");
	insere_ArvAVL(raiz, 5);
	insere_ArvAVL(raiz, 6);
	insere_ArvAVL(raiz, 4);
	insere_ArvAVL(raiz, 3);
	insere_ArvAVL(raiz, 7);
	insere_ArvAVL(raiz, 8);
	x = altura_ArvAVL(raiz);
	y = totalNO_ArvAVL(raiz);
	printf("A altura eh %d, e o numero de nos eh %d \n", x, y);
	emOrdem_ArvAVL(raiz);
	printf("\n");
	insere_ArvAVL(raiz, 9);
	x = altura_ArvAVL(raiz);
	y = totalNO_ArvAVL(raiz);
	printf("A altura eh %d, e o numero de nos eh %d \n", x, y);
	emOrdem_ArvAVL(raiz);
	printf("\n");
	remove_ArvAVL(raiz, 6);
	x = altura_ArvAVL(raiz);
	y = totalNO_ArvAVL(raiz);
	printf("A altura eh %d, e o numero de nos eh %d \n", x, y);	
	emOrdem_ArvAVL(raiz);
	printf("\n");
	remove_ArvAVL(raiz, 5);
	x = altura_ArvAVL(raiz);
	y = totalNO_ArvAVL(raiz);	
	printf("A altura eh %d, e o numero de nos eh %d \n", x, y);
	emOrdem_ArvAVL(raiz);
}
