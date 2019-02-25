
typedef struct Dados {
		char nome[50];
		int idade;
		struct Dados *prox;
} dados_t;

typedef struct LISTA{

	dados_t* inicio;
	dados_t* fim;	

} lista_t;


lista_t* criar_lista();

void inserir(lista_t* lista, char nome[50], int idade);

dados_t buscar(dados_t* dados, int indice);

void apagar_item(lista_t* lista);

void excluir(dados_t* dados);
  
