
typedef struct DADOS {
	int idade;
	struct DADOS *prox;
} dados_f;

typedef struct FILA {
	dados_f* inicio;
	dados_f* fim;
} fila_f;


void adiciona_elemento(fila_f* fila, int num);

void remove_elementos(fila_f* fila);

void printa_fila(fila_f* fila);

fila_f* inicializa_fila();
