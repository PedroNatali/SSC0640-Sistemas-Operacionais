#include <stdio.h>
#include <malloc.h>
#include "matriz_esparsa.h"

MATRIZ_ESPARSA *criar_matriz (int nr_linhas, int nr_colunas) {

    MATRIZ_ESPARSA* matriz = (MATRIZ_ESPARSA*) malloc(sizeof(MATRIZ_ESPARSA));


    if (matriz != NULL){
        int i;

        matriz->nr_linhas = nr_linhas;
        matriz->nr_colunas = nr_colunas;


        matriz->linhas = (CELULA**) malloc(nr_linhas*sizeof(CELULA));
        matriz->colunas = (CELULA**) malloc(nr_colunas*sizeof(CELULA));


        if (matriz->colunas != NULL && matriz->linhas != NULL){

            for (i=0; i < nr_linhas; i++) {
                matriz->linhas[i] = (CELULA*) malloc(sizeof (CELULA));
                matriz->linhas[i]->direita = NULL;
            }

            for (i=0; i < nr_colunas; i++) {
                matriz->colunas[i] = (CELULA*) malloc(sizeof (CELULA));
                matriz->colunas[i]->abaixo = NULL;
            }
        }
    }
    return matriz;
}

int set_matriz(MATRIZ_ESPARSA* matriz, int lin, int col, float val){
    if (lin < matriz->nr_linhas && col <  matriz->nr_colunas) {
        CELULA *aux = matriz->linhas[lin];

        while (aux->direita != NULL && aux->direita->coluna <= col){
            aux = aux->direita;
        }
        if (aux->coluna ==  col){
            aux->valor = val;
        } else {
            CELULA *pn = (CELULA *) malloc(sizeof(CELULA));
            if (pn != NULL){
                pn->linha = lin;
                pn->coluna = col;
                pn->valor = val;
                pn->direita = aux->direita;
                aux->direita = pn;

                aux = matriz->colunas[col];
                while (aux->abaixo != NULL && aux->abaixo->linha <= lin) {
                    aux = aux->abaixo;
                }

                pn->abaixo = aux->abaixo;
                aux->abaixo = pn;
            }
        }
       return 1;
    }
    return 0;
}

float get_matriz(MATRIZ_ESPARSA *matriz, int lin, int col){
    if (lin < matriz->nr_linhas && col < matriz->nr_colunas){
        CELULA *aux1 = matriz->linhas[lin];
        while (aux1->direita != NULL && aux1->direita->coluna <= col){
            aux1 = aux1->direita;
        }
        if (aux1->coluna == col){
            return aux1->valor;
        }
    }
    return 0;
}

void apagar_matriz(MATRIZ_ESPARSA *matriz){
    int i;
    for(i = 0; i < matriz->nr_linhas; i++) {
        CELULA *aux = matriz->linhas[i]->direita;

        while (aux != NULL) {
            CELULA *prm = aux;
            aux = aux->direita;
            free(prm);
        }
        free(matriz->linhas[i]);
    }
    free (matriz->linhas);
    free (matriz->colunas);
    free (matriz);
    matriz = NULL;
}



MATRIZ_ESPARSA *somar_matriz(MATRIZ_ESPARSA *m1, MATRIZ_ESPARSA *m2){
    if (m1->nr_linhas == m2->nr_linhas && m1->nr_colunas == m2->nr_colunas){
        MATRIZ_ESPARSA *sum = (MATRIZ_ESPARSA *) malloc (sizeof(MATRIZ_ESPARSA));
        sum = criar_matriz(m1->nr_linhas, m1->nr_colunas);
        int i, j;
        double value;
        for (i = 0 ; i < m1->nr_linhas; i++){
            for (j = 0; j < m1->nr_colunas; j++){
                value = get_matriz(m1, i, j) + get_matriz(m2, i, j);
                set_matriz(sum, i, j, value);
            }
        }
        return sum;
    }
    return NULL;
}
void print_matriz(MATRIZ_ESPARSA *matriz){
    int i, j;
    for (i = 0; i < matriz->nr_linhas; i++){
        for (j = 0; j < matriz->nr_colunas; j++){
            float v = get_matriz(matriz, i, j);
            printf("%.1lf ", v);
        }
        printf("\n");
    }
}

MATRIZ_ESPARSA *multiplicar_matriz(MATRIZ_ESPARSA *m1, MATRIZ_ESPARSA *m2){
    if (m1->nr_colunas == m2->nr_linhas){
        MATRIZ_ESPARSA* multiply = (MATRIZ_ESPARSA*) malloc (sizeof(MATRIZ_ESPARSA));
        multiply = criar_matriz(m1->nr_linhas, m2->nr_colunas);
        int i, j, k;
        for (i = 0; i < multiply->nr_linhas; i++){
            for (j = 0; j < multiply->nr_colunas; j++){
                float v = 0;
                for (k = 0; k < multiply->nr_linhas; k++){
                    v += get_matriz(m1, i, k) * get_matriz(m2, k, j);
                }
                set_matriz(multiply, i, j, v);
            }
        }
        return multiply;
    }
    return NULL;
}


MATRIZ_ESPARSA *transposta_matriz(MATRIZ_ESPARSA *matriz){
    if (matriz != NULL) {
        MATRIZ_ESPARSA* transposta = (MATRIZ_ESPARSA*) malloc(sizeof(MATRIZ_ESPARSA));
        transposta = criar_matriz(matriz->nr_colunas, matriz->nr_linhas);
        int i, j;
        for (i = 0; i < transposta->nr_linhas; i++){
            for (j = 0; j < transposta->nr_colunas; j++){
                float v = get_matriz(matriz, j, i);
                set_matriz(transposta, i, j, v);
            }
        }
        return transposta;
    }
    return NULL;
}

MATRIZ_ESPARSA *ler_matriz(const char nome[]){
    FILE *arq;
    arq = fopen(nome, "r");
    int nr_linhas, nr_colunas;
    fscanf(arq, "%d %d", &nr_linhas, &nr_colunas);
    int i,j;
    MATRIZ_ESPARSA* matriz = (MATRIZ_ESPARSA*)malloc(sizeof(MATRIZ_ESPARSA));
    matriz = criar_matriz(nr_linhas, nr_colunas);
    for (i = 0; i < nr_linhas; i++){
        for (j = 0; j < nr_colunas; j++){
            float n;
            fscanf(arq, "%f ", &n);
            set_matriz(matriz, i, j, n);
        }
    }
    fclose(arq);
    return matriz;
}


void resumo_matriz(MATRIZ_ESPARSA *matriz){
    int i, j;
    for (i = 0; i < matriz->nr_linhas; i++){
        for (j = 0; j < matriz->nr_colunas; j++){
            float value = get_matriz(matriz, i, j);
            if (value != 0){
                printf("%.1f ", value);
            }
        }
    }
    printf("\n");
}

double determinante_matriz(MATRIZ_ESPARSA *matriz){
    if (matriz->nr_colunas == matriz->nr_linhas){
        int m = 0;
        int i = 0, j = 0, k = 0;
        double fator = 0;
        double temp = 0;
        int count = 0;

        m = matriz->nr_colunas;

        for(i = 0; i < m - 1; i++)
        {
            if(get_matriz(matriz, i, i) == 0)
            {
                for(k = i; k < m; k++)
                {
                    if(get_matriz(matriz, k, i) != 0)
                    {
                        for(j = 0; j < m; j++)
                        {
                            temp = get_matriz(matriz, i, j);
                            set_matriz(matriz, i, j, get_matriz(matriz, k, j));
                            set_matriz(matriz, k, j, temp);
                        }
                        k = m;
                    }
                }
                count++;
            }

            if(get_matriz(matriz, i, i) != 0)
            {
                for(k = i + 1; k < m; k++)
                {
                    fator = -1.0 * get_matriz(matriz, k, i) / get_matriz(matriz, i, i);
                    for(j = i; j < m; j++)
                    {
                        set_matriz(matriz, k, j, get_matriz(matriz, k, j) + (fator * get_matriz(matriz, i, j)));
                    }
                }
            }
        }

        temp = 1.0;
        for(i = 0; i < m; i++)
            temp *= get_matriz(matriz, i, i);

        if(count % 2 == 0)
            return temp;
        else
            return (-1.0)* temp;

    }

}
