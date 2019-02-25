#ifndef MATRIZ_ESPARSA_H
#define MATRIZ_ESPARSA_H

typedef struct matriz_esparsa MATRIZ_ESPARSA;

typedef struct CELULA {
    int linha;
    int coluna;
    float valor;
    struct CELULA *direita;
    struct CELULA *abaixo;
} CELULA;

struct matriz_esparsa {
    CELULA **linhas;
    CELULA **colunas;
    int nr_linhas;
    int nr_colunas;
};

MATRIZ_ESPARSA *criar_matriz(int nr_linhas, int nr_colunas);

void apagar_matriz(MATRIZ_ESPARSA *matriz);

int set_matriz(MATRIZ_ESPARSA *matriz, int lin, int col, float val);

float get_matriz(MATRIZ_ESPARSA *matriz, int lin, int col);

MATRIZ_ESPARSA *somar_matriz (MATRIZ_ESPARSA *m1, MATRIZ_ESPARSA *m2);

MATRIZ_ESPARSA *multiplicar_matriz (MATRIZ_ESPARSA *m1, MATRIZ_ESPARSA *m2);

MATRIZ_ESPARSA *transposta_matriz(MATRIZ_ESPARSA *matriz);

double determinante_matriz(MATRIZ_ESPARSA *matriz);

void print_matriz(MATRIZ_ESPARSA *matriz);

void resumo_matriz(MATRIZ_ESPARSA *matriz);

MATRIZ_ESPARSA *ler_matriz(const char nome[]);

#endif // MATRIZ_ESPARSA_H
