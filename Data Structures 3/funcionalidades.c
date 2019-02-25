/*
@authors
	Pedro Natali - 10310655
	Rafael Pinho - 10276737
	Paulo de Moura - 10310471
	Renan Varoni - 10310676
*/


//bibliotecas utilizadas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <math.h>
#include <time.h>

/* *************************************************** STRUCTS UTILIZADAS ********************************************************************* */

//define uma estrutura para usar de registro
typedef struct{
    int nusp;
    char nome[30];
    char livros[20];
    char data[10];
} REGISTRO;

//defina as variaveis true e false
typedef enum {false, true} Boolean;

//define uma estrutura para no da arvore do metodo 6
typedef struct{
	int index;
	int value;
} NODE;


/* *************************************************** FUNCOES NECESSARIAS ********************************************************************* */

//funcao semelhante a escreve_arq_bin, porem cria o registro e nao soh escreve nele
void escrever_arq_bin_novo(int k, REGISTRO *reg,char arqbin[30],int size){
	FILE* arq_bin;
	arq_bin = fopen(arqbin, "wb");
	for(k;k<size;k++){
		fwrite(&reg[k].nusp,sizeof(int),1,arq_bin);
		fwrite(&reg[k].nome,30*sizeof(char),1,arq_bin);
		fwrite(&reg[k].livros,20*sizeof(char),1,arq_bin);
		fwrite(&reg[k].data,10*sizeof(char),1,arq_bin);
	}	
	fclose(arq_bin);
}


//retorna true se o registro 1 for maior e - se o registro 2 for maior
//trata-se simplesmente de uma comparacao campo a campo
int maior(REGISTRO reg1, REGISTRO reg2){
	if (reg1.nusp > reg2.nusp)
		return true;
	else if (reg1.nusp < reg2.nusp)
		return false;
	else {
		if (strcmp(reg1.nome, reg2.nome) > 0)
			return true;
		else if (strcmp(reg1.nome, reg2.nome) < 0)
			return false;
		else {
			if (strcmp(reg1.livros, reg2.livros) > 0)
				return true;
			else if (strcmp(reg1.livros, reg2.livros) < 0)
				return false;
			else {
				if (strcmp(reg1.data, reg2.data) > 0)
					return true;
				else if (strcmp(reg1.data, reg2.data) < 0)
					return false;
			}
		}
	}
}

//algoritmo de ordenacao baseado em shellSort
void shellSort(REGISTRO *reg, int size) {
    int i , j;
    REGISTRO temp;
    int div = 1;
    while(div < size) {
        div = 3*div+1; //faz a manutencao do gap ate que seja maior que a quantidade de registros
    }
    while ( div > 1) {
        div /= 3; //divide o array inteiro em partes menores para utilizar o metodo de insercao
        for(i = div; i < size; i++) {
            temp = reg[i];
            j = i;
			//faz um metodo de insercao entre o indice gap e o valor de j
            while (j >= div && maior(reg[j - div], temp)) {
            	reg[j] =  reg[j - div]; //faz a troca  no indice j pelo mesmo indice subtriado do gap
                j = j - div;
            }
            reg [j] = temp;
        }
    }
}


int Encontra_tamanho_subarquivo(char * subArq){
    FILE *f;
    f = fopen(subArq, "rb");
    int tamanho = ftell(f); 
    fseek(f, 0L, SEEK_END);
    tamanho = ftell(f);
    tamanho = tamanho/65;
    fclose(f);
    return tamanho;
}


/* *************************************************** PRIMEIRA FUNCIONALIDADE ********************************************************************* */

//funcao que escreve no arquivo reg2 todos os registros
void escrever_arq_bin(REGISTRO *reg,FILE* file_regbinario,int size){
	int i;
	for(i=0;i<size;i++){
		fwrite(&reg[i].nusp,sizeof(int),1,file_regbinario);
		fwrite(&reg[i].nome,30*sizeof(char),1,file_regbinario);
		fwrite(&reg[i].livros,20*sizeof(char),1,file_regbinario);
		fwrite(&reg[i].data,10*sizeof(char),1,file_regbinario);
	}	
}

//funcao que gera os registros repetidos, respeitando as devidas porcentagens
void repeticoes(REGISTRO *reg, int size){
	srand(time(NULL));
	int i,aux2,aux = 0.7 * size;
	
	while(aux<size){
	aux2 = rand()%aux;
		reg[aux].nusp = reg[aux2].nusp;              //substitui os ultimos 30% dos numeros usp 
		aux++;                                       //por valores repetidos do campo 1
	}
	aux = 0.75*size;
	while(aux<size){
		aux2 = rand()%aux;
		for(i=0;i<30;i++){							//substitui os ultimos 25% dos nomes
			reg[aux].nome[i] = reg[aux2].nome[i];	//por valores repetidos do campo 2
		}
		aux++;
	}
	aux = 0.8*size;

	while(aux<size){
		aux2 = rand()%aux;
		for(i=0;i<20;i++){
		reg[aux].livros[i] = reg[aux2].livros[i];     //substitui os ultimos 20% dos nomes de livros
		}											//por valores repetidos do campo 3
		aux++;
	} 
	aux = 0.85*size;
	
	while(aux<size){
		aux2 = rand()%aux;
		for(i=0;i<10;i++){
		reg[aux].data[i] = reg[aux2].data[i];		//substitui os ultimos 15% dos nomes de livros
		}											//por valores repetidos do campo 4
		aux++;
	}
}


void geracao_aleatoria(REGISTRO* reg, int size){
	int i,aleatorio;
	REGISTRO aux;
	srand(time(NULL));
	for (i=0;i<size;i++){
		aleatorio = rand()%size;
		aux = reg[i];
		reg[i].nusp = reg[aleatorio].nusp;
		reg[aleatorio].nusp = aux.nusp;
		aleatorio = rand()%size;
		aux = reg[i];
		strcpy(reg[i].nome,reg[aleatorio].nome);
		strcpy(reg[aleatorio].nome,aux.nome);
		aux = reg[i];
		strcpy(reg[i].livros,reg[aleatorio].livros);
		strcpy(reg[aleatorio].livros,aux.livros);
		aux = reg[i];
		strcpy(reg[i].data,reg[aleatorio].data);
		strcpy(reg[aleatorio].data,aux.data);
	}
}


//Funcao que gera o arquivo binario com os registros
void geracao_de_registros(char* nomeArquivoGerado,int size){
	REGISTRO reg[size];
	FILE *file_nomes = fopen("nomes.txt","r");				//abertura dos arquivos de onde ser�o retirados cada um dos campos dos registros
	FILE *file_livros = fopen("results_livros.txt","r");
	FILE *file_nusp = fopen("nusp.txt","r");
	FILE *file_data = fopen("data_de_aluguel.txt","r");
	FILE *file_regbinario = fopen(nomeArquivoGerado,"wb");
	char numero[100],name[100],livros[100],date[100];
	int i = 0,k = 0,result;
	
	for(k=0;k<size;k++){
	
		
		if(file_nusp == NULL){
			printf("arquivo nulo");
		}
	
	
	
		fgets(numero,100,file_nusp);       //recebe do arquivo de numeros usp um valor de numero usp para a variavel numero
		
		for(i=0;i<strlen(numero);i++){	   //retira o \n para que nao seja pulado uma linha
			if(numero[i] == '\n'){
				numero[i] = numero[i+1];
				numero[i+1] = ' ';
			}
		}
	
		reg[k].nusp = atoi(numero);

		fgets(name,100,file_nomes);			//recebe do arquivo de nomes de pessoas uma string de nome para a variavel name
		
		for(i=0;i<30;i++){					//dentro desse for eh feito o preenchimento dos espacos vazios no final do campo
			if(name[i] == '\n'){			//por '*' e tirado o \n para que nao seja pulado uma linha
				name[i] = name[i+1];
				name[i+1] = ' ';
			}
			if(name[i] == '\0'){
				name[i+1]=name[i];
				name[i] = '*';
			}
		}
		name[29] ='\0';
		strcpy(reg[k].nome,name);
	
	
		fgets(livros,100,file_livros);	   //recebe do arquivo de livros uma string com nome do livro para a variavel livro
		
		for(i=0;i<19;i++){				   //dentro desse for eh feito o preenchimento dos espacos vazios no final do campo
			if(livros[i] == '\n'){		   //por '*' e tirado o \n para que nao seja pulado uma linha
				livros[i] = livros[i+1];
				livros[i+1] = ' ';
			}
			if(livros[i] == '\0'){
				livros[i+1]=livros[i];
				livros[i] = '*';
			}
			reg[k].livros[i] = livros[i];
		}
		livros[19] ='\0';
		strcpy(reg[k].livros,livros);
		
		fgets(date,100,file_data);		  //recebe do arquivo de datas uma string de data para a variavel date no formato **/**/****
		
		strcpy(reg[k].data,date);
		


	}
	
	geracao_aleatoria(reg,size);
	repeticoes(reg,size);										//chama a funcao que gera as repeticoes nos registros
	escrever_arq_bin(reg,file_regbinario,size);			    //chama a funcao que escreve no arquivo binario os registros

	if(file_regbinario != NULL){
		printf("Arquivo gerado. \n");
	}else{
		printf("Falha no processamento. \n");
	}
	
	fclose(file_nusp);											//por fim sao fechados todos os arquivos utilizados no codigo
	fclose(file_nomes);
	fclose(file_data);
	fclose(file_livros); 
	fclose(file_regbinario);
	
}


/* *************************************************** SEGUNDA FUNCIONALIDADE ********************************************************************* */
//funcao que imprime cada registro dentro do arquivo binario
//imprimir_arq_bin(file_regbinario,nomeArquivoGerado,reg[k]); chama a funcao que imprimi os registros na tela

void imprimir_arq_bin(char *nome_arquivo){
	REGISTRO reg;
	FILE* arq= fopen(nome_arquivo,"rb");
	if(arq == NULL){
		printf("Arquivo vazio");     					//retorna mensagem de erro caso ocorra algum problema no arquivo
		exit(1);
	}

	
	while(fread(&reg,sizeof(REGISTRO),1,arq) != 0){
		printf("%d %s %s %s\n",reg.nusp,reg.nome,reg.livros,reg.data);   //imprimi os valores de cada um dos registros
		
	}
	fclose(arq);
}


/* *************************************************** TERCEIRA FUNCIONALIDADE ********************************************************************* */

void ordena_arquivo(char *nomeArquivo, char *nomeArquivoOrdenado){
	int i; //variavel que ira nos dizer a quantidade de registros no arquivo
	FILE *arq_sem_ord = fopen(nomeArquivo, "rb+"); // abre-se o arquivo sem ordenacao
	FILE *arq_com_ord = fopen(nomeArquivoOrdenado, "wb+"); // abre-se o arquivo com ordenacao
	REGISTRO v_s_ordenacao[6000]; //criaremos um vetor de REGISTROS com o tamanho maximo de registros
	REGISTRO registro; // tambem criaremos um registro para iteracoes
	
	//aqui eh feita a leitura dos registros do arquivo para o vetor de registros	
	for (i = 0; fread(&v_s_ordenacao[i].nusp, sizeof(registro.nusp), 1, arq_sem_ord); i++){
		fread(&v_s_ordenacao[i].nome, sizeof(registro.nome), 1, arq_sem_ord);
		fread(&v_s_ordenacao[i].livros, sizeof(registro.livros), 1, arq_sem_ord);
		fread(&v_s_ordenacao[i].data, sizeof(registro.data), 1, arq_sem_ord);
	}
	
	//a ordenacao foi efetuada por meio de um shellsort
	shellSort(v_s_ordenacao, i);
	

	int k; //variavel auxiliar
	fseek(arq_sem_ord, 0, SEEK_SET);//setamos o arquivo sem ordenacao no comeco

	//aqui para cada registro no arquivo sem ordenacao, escrevemos um registro do vetor de registros para o arquivo com ordenacao
	for (k = 0; fread(&registro, sizeof(registro), 1, arq_sem_ord); k++){
		fwrite(&v_s_ordenacao[k].nusp, sizeof(registro.nusp), 1, arq_com_ord);
		fwrite(&v_s_ordenacao[k].nome, sizeof(registro.nome), 1, arq_com_ord);
		fwrite(&v_s_ordenacao[k].livros, sizeof(registro.livros), 1, arq_com_ord);
		fwrite(&v_s_ordenacao[k].data, sizeof(registro.data), 1, arq_com_ord);
	}


	//teste para saber se funcionou
	if (arq_com_ord!= NULL)
		printf("Arquivo gerado.\n");
	else
		printf("Falha no processamento.\n");
	
	//fecha-se os arquivos
	fclose(arq_com_ord);
	fclose(arq_sem_ord);
}


/* *************************************************** QUARTA FUNCIONALIDADE ********************************************************************* */
void merging_arquivo(char* arquivo_1, char* arquivo_2, char* arquivo_saida){
	REGISTRO novo_reg, novo_reg2, aux1, aux2; //variaveis que representam os registros de cada arquivo
    FILE *arquivo; //primeiro arquivo de registros
	FILE *arquivo2; //segundo arquivo de registros
	FILE *arquivo_out; //arquivo resultante
	int tamanho_total = 0 ,n = 0 ,n1 = 0 ,n2 = 0 ; //tamanho total == tamanho dos 2 arquivos de registros juntos, n == numero de iteracoes, n1 == numero de registros do arq1 - respectivo pra n2
	
    //abrindo o arquivo binario de saida
	
   	arquivo = fopen(arquivo_1, "rb");
	arquivo2 = fopen(arquivo_2,"rb"); 
	arquivo_out = fopen(arquivo_saida, "wb+");  


    //contando quantos elementos tem em cada lista e no total
	while(fread(&aux1, sizeof(REGISTRO), 1, arquivo) != 0){
		n1++;
		while(fread(&aux2, sizeof(REGISTRO), 1, arquivo2) != 0){
			n2++;
		}
	} 
	tamanho_total = n1+n2;
	
	fclose(arquivo);
	fclose(arquivo2);

	arquivo = fopen(arquivo_1, "rb");
	arquivo2 = fopen(arquivo_2,"rb"); 
	
	//MERGING
	n = 0; //variavel que utilizaremos para saber quantas vzs iteramos no total
	int i1 = 1; //variavel para analisar quantos elementos da primeira lista foram iterados
	int i2 = 1; //variavel para analisar quantos elementos da segunda lista foram iterados
	fread(&novo_reg2, sizeof(REGISTRO), 1, arquivo2);
	fread(&novo_reg, sizeof(REGISTRO), 1, arquivo); 

	
	
    //verifica se o arquivo terminou ou nao
    while(n < tamanho_total){
    	//se o nusp do registro1 for menor que o do registro2
    	if(novo_reg.nusp < novo_reg2.nusp){
    		//se ainda nao esta no ultimo elemento da primeira lista
    		if(i1<n1){
	    		//escreve no arquivo de saida o nome1 e le o proximo nome na lista 1
				fwrite(&novo_reg, sizeof(REGISTRO), 1, arquivo_out);
	    		n++;
	    		i1++;
				fread(&novo_reg,sizeof(REGISTRO),1,arquivo);
			//se esta no ultimo elemento, printa ele e printa a segunda lista em ordem	
			}else{
				fwrite(&novo_reg, sizeof(REGISTRO),1,arquivo_out);
				fwrite(&novo_reg2, sizeof(REGISTRO),1,arquivo_out);
				while(fread(&novo_reg2,sizeof(REGISTRO),1,arquivo2)!=0){
					fwrite(&novo_reg2, sizeof(REGISTRO),1,arquivo_out);
				}
				break;
			}
		}
		//se o nusp do registro 1 for maior que do registro 2
		else if (novo_reg.nusp > novo_reg2.nusp){
			//se ainda nao esta no ultimo elemento da segunda lista
			if(i2 < n2){
				//escreve no arquivo de saida o nome 2 e le o proximo nome na lista 2
				fwrite(&novo_reg2, sizeof(REGISTRO), 1, arquivo_out);
				n++;
				i2++;
				fread(&novo_reg2,sizeof(REGISTRO),1,arquivo2);
			//se esta no ultimo elemento, printa ele e printa a primeira lista em ordem	
			}else{
				fwrite(&novo_reg2, sizeof(REGISTRO),1,arquivo_out);
				fwrite(&novo_reg, sizeof(REGISTRO),1,arquivo_out);
				while(fread(&novo_reg,sizeof(REGISTRO),1,arquivo)!=0){
					fwrite(&novo_reg, sizeof(REGISTRO),1,arquivo_out);
				}
				break;
			}
		}
		else{
			//analisa o nome para ordenar
			if(strcmp(novo_reg.nome, novo_reg2.nome) < 0){
				//funcionou quando coloquei o de baixo aqui;
				//se ainda nao esta no ultimo elemento da segunda lista
	    		if(i1<n1){
		    		//escreve no arquivo de saida o nome1 e le o proximo nome na lista 1
		    		fwrite(&novo_reg, sizeof(REGISTRO), 1, arquivo_out);
		    		n++;
		    		i1++;
					fread(&novo_reg,sizeof(REGISTRO),1,arquivo);
				//se esta no ultimo elemento, printa ele e printa a segunda lista em ordem	
				}else{
					fwrite(&novo_reg, sizeof(REGISTRO),1,arquivo_out);
					fwrite(&novo_reg2, sizeof(REGISTRO),1,arquivo_out);
					while(fread(&novo_reg2,sizeof(REGISTRO),1,arquivo2)!=0){
						fwrite(&novo_reg2, sizeof(REGISTRO),1,arquivo_out);
					}
					break;
				}
			}
			//se o nome do registro 1 for maior que do registro 2
			else if (strcmp(novo_reg.nome, novo_reg2.nome) > 0){
				//se ainda nao esta no ultimo elemento da segunda lista
				if(i2 < n2){
					//escreve no arquivo de saida o nome 2 e le o proximo nome na lista 2
					fwrite(&novo_reg2, sizeof(REGISTRO), 1, arquivo_out);
					n++;
					i2++;
					fread(&novo_reg2,sizeof(REGISTRO),1,arquivo2);
				//se esta no ultimo elemento, printa ele e printa a primeira lista em ordem	
				}else{
					fwrite(&novo_reg2, sizeof(REGISTRO),1,arquivo_out);
					fwrite(&novo_reg, sizeof(REGISTRO),1,arquivo_out);
					while(fread(&novo_reg,sizeof(REGISTRO),1,arquivo)!=0){
						fwrite(&novo_reg, sizeof(REGISTRO),1,arquivo_out);
					}
					break;
				}
			}
			else{
				//analisa agora os nomes dos livros
				if(strcmp(novo_reg.livros, novo_reg2.livros) < 0){
		    		//se ainda nao esta no ultimo elemento da primeira lista
		    		if(i1<n1){
			    		//escreve no arquivo de saida o nome1 e le o proximo nome na lista 1
			    		fwrite(&novo_reg, sizeof(REGISTRO), 1, arquivo_out);
			    		n++;
			    		i1++;
						fread(&novo_reg,sizeof(REGISTRO),1,arquivo);
					//se esta no ultimo elemento, printa ele e printa a segunda lista em ordem	
					}else{
						fwrite(&novo_reg, sizeof(REGISTRO),1,arquivo_out);
						fwrite(&novo_reg2, sizeof(REGISTRO),1,arquivo_out);
						while(fread(&novo_reg2,sizeof(REGISTRO),1,arquivo2)!=0){
							fwrite(&novo_reg2, sizeof(REGISTRO),1,arquivo_out);
						}
						break;
					}
				}
				//se o nome do livro do registro 1 for maior que do registro 2
				else if (strcmp(novo_reg.livros, novo_reg2.livros) > 0){
					//se ainda nao esta no ultimo elemento da segunda lista
					if(i2 < n2){
						//escreve no arquivo de saida o nome 2 e le o proximo nome na lista 2
						fwrite(&novo_reg2, sizeof(REGISTRO), 1, arquivo_out);
						n++;
						i2++;
						fread(&novo_reg2,sizeof(REGISTRO),1,arquivo2);
					//se esta no ultimo elemento, printa ele e printa a primeira lista em ordem	
					}else{
						fwrite(&novo_reg2, sizeof(REGISTRO),1,arquivo_out);
						fwrite(&novo_reg, sizeof(REGISTRO),1,arquivo_out);
						while(fread(&novo_reg,sizeof(REGISTRO),1,arquivo)!=0){
							fwrite(&novo_reg, sizeof(REGISTRO),1,arquivo_out);
						}
						break;
					}
				}
				else{
					//analisa as datas
					if(strcmp(novo_reg.data, novo_reg2.data) < 0){
			    		//se ainda nao esta no ultimo elemento da primeira lista
			    		if(i1<n1){
				    		//escreve no arquivo de saida o nome1 e le o proximo nome na lista 1
				    		fwrite(&novo_reg, sizeof(REGISTRO), 1, arquivo_out);
				    		n++;
				    		i1++;
							fread(&novo_reg,sizeof(REGISTRO),1,arquivo);
						//se esta no ultimo elemento, printa ele e printa a segunda lista em ordem	
						}else{
							fwrite(&novo_reg, sizeof(REGISTRO),1,arquivo_out);
							fwrite(&novo_reg2, sizeof(REGISTRO),1,arquivo_out);
							while(fread(&novo_reg2,sizeof(REGISTRO),1,arquivo2)!=0){
								fwrite(&novo_reg2, sizeof(REGISTRO),1,arquivo_out);
							}
							break;
						}
					}
					//se a data do registro 1 for maior que do registro 2
					else if (strcmp(novo_reg.data, novo_reg2.data) > 0){
						//se ainda nao esta no ultimo elemento da segunda lista
						if(i2 < n2){
							//escreve no arquivo de saida o nome 2 e le o proximo nome na lista 2
							fwrite(&novo_reg2, sizeof(REGISTRO), 1, arquivo_out);
							n++;
							i2++;
							fread(&novo_reg2,sizeof(REGISTRO),1,arquivo2);
						//se esta no ultimo elemento, printa ele e printa a primeira lista em ordem	
						}else{
							fwrite(&novo_reg2, sizeof(REGISTRO),1,arquivo_out);
							fwrite(&novo_reg, sizeof(REGISTRO),1,arquivo_out);
							while(fread(&novo_reg,sizeof(REGISTRO),1,arquivo)!=0){
								fwrite(&novo_reg, sizeof(REGISTRO),1,arquivo_out);
							}
							break;
						}
					}
					else{
						//os registros sao o mesmo, entao podemos ignorar um deles
						fwrite(&novo_reg, sizeof(REGISTRO), 1, arquivo_out);
						n++;
						fread(&novo_reg,sizeof(REGISTRO),1,arquivo);
						fread(&novo_reg2,sizeof(REGISTRO),1,arquivo2);
					}
				}
			}
		}
	}
	
	//teste para analisar se funcionou ou nao
	if(arquivo_out != NULL){
		printf("Arquivo gerado. \n");
	}else{
		printf("Falha no processamento. \n");
	}
	
	fclose(arquivo_out);
	fclose(arquivo2);
	fclose(arquivo);
		
} 


/* *************************************************** QUINTA FUNCIONALIDADE ********************************************************************* */
void matching_arquivo(char *arquivo_1, char *arquivo_2, char *arquivo_saida){
    REGISTRO reg1, reg2; // define as variaveis que serão utilizadas como registro

    FILE *file_1 = fopen(arquivo_1, "rb"); // abre o arquivo 1 
    FILE *file_2 = fopen(arquivo_2, "rb"); // abre o arquivo 2
	FILE *file_3 = fopen(arquivo_saida, "wb"); //abre o arquivo de saida que queremos 

	fread(&reg1, sizeof(REGISTRO), 1, file_1); // le o primeiro registro do primeiro arquivo
	fread(&reg2, sizeof(REGISTRO), 1, file_2); // le o primeiro registro do segundo arquivo

	//enquanto os arquivos nao terminaram
    while(!feof(file_1) && !feof(file_2)){
		
		//se o nusp do reg1 eh menor que o nusp do reg2
        if(reg1.nusp < reg2.nusp){
			//le o proximo reg de reg1
        	fread(&reg1, sizeof(REGISTRO), 1, file_1);
        }

		//se o nusp do reg2 eh menor que o nusp do reg1
        else if(reg1.nusp > reg2.nusp){
			//le o proximo reg de reg2
        	fread(&reg2, sizeof(REGISTRO), 1, file_2);
        }
		
		//senao, os dois registros sao iguais, o que significa MATCH.
        else{ 
			//grava os 2 registros no arquivo de saida e le o proximo de ambos
        	fwrite(&reg1, sizeof(REGISTRO), 1 ,file_3);
			fwrite(&reg2, sizeof(REGISTRO), 1, file_3);
			fread(&reg2, sizeof(REGISTRO), 1, file_2);
			fread(&reg1, sizeof(REGISTRO), 1, file_1);
		}
	}

    //fecha os arquivos
	fclose(file_1);
	fclose(file_2);
	fclose(file_3);
		
	//verifica se o codigo funcionou como deveria
	FILE *teste = fopen(arquivo_saida, "rb");
	if(arquivo_saida != NULL){
		printf("Arquivo gerado. \n");
	}else{
		printf("Falha no processamento. \n");
	}
	fclose(teste);
}
	
/* *************************************************** SEXTA FUNCIONALIDADE ********************************************************************* */	
void multiway_arquivo(int max, char** nomeArquivo){

	//Area para declaracao de variaveis
    int full_size = 0;
    int tamanho = max - 1;														
    int size[tamanho];
    int tamanhoPart[tamanho];
    for(int i = 0; i < tamanho; i++){
        size[i] = 0;
        full_size = full_size + Encontra_tamanho_subarquivo(nomeArquivo[i+2]);
        tamanhoPart[i] = Encontra_tamanho_subarquivo(nomeArquivo[i+2]);
    }
    NODE* no = (NODE*)malloc(tamanho*sizeof(NODE));
    FILE* f_entradas[tamanho];
    FILE* f_final;
    f_final = fopen(nomeArquivo[tamanho+2], "wb");

    REGISTRO* reg = (REGISTRO*)malloc(tamanho*sizeof(REGISTRO));
    for(int i = 0; i < tamanho; i++){
		//Abertura dos arquivos q serao chamados na funcao
        f_entradas[i] = fopen(nomeArquivo[i+2], "rb");						
        fread(&reg[i], sizeof(REGISTRO), 1, f_entradas[i]);
        no[i].index = i;
		//Coloca o primeiro nusp de cada arquivo nos nos													
        no[i].value = reg[i].nusp;											
    }

    int contador = 0;
    int x = 0;
    
    //Arvore de selecao
    while(true){
        int num = tamanho;
        int escolhido[num];
        for(int i = 0; i<num; i++){
            escolhido[i] = i;
        }
        int aux;
        while(num != 1){
            if (num%2 == 0){
                num = num/2;
            } else {
                num = (num/2) + 1;
            }
    
            for(int i = 0; i < num; i++){
                if(no[escolhido[2*i]].value < no[escolhido[(2*i)+1]].value){	//
                    escolhido[i] = escolhido[2*i];
                } else {
                    escolhido[i] = escolhido[(2*i)+1];
                }

                if((2*i)+1 == num){
                    escolhido[i] = escolhido[2*i];
                }
            }
            if(num == 1){
                aux = escolhido[0];
            }
        }
        x++;
		//escrita no arquivo final da funcao
        fwrite(&reg[aux].nusp, sizeof(int), 1, f_final);
        fwrite(&reg[aux].nome, 30, 1, f_final);							
        fwrite(&reg[aux].livros, 20, 1, f_final);
        fwrite(&reg[aux].data, 10, 1, f_final);
        size[aux]++;

        if(size[aux] < tamanhoPart[aux]){
			//escreve o menor valor da arvore no arquivo de saida
            fread(&reg[aux], sizeof(REGISTRO), 1, f_entradas[aux]);		
            no[aux].index = aux;
            no[aux].value = reg[aux].nusp;

		//caso o arquivo nao possua mais registros
        } else {
            fclose(f_entradas[aux]);								
            no[aux].index = aux;		
			//\E9 atribuido um valor "infinito" para nao ser mais escolhido								
            no[aux].value = 999999999;
        }

        contador++;
        if(contador == full_size) break;
    }

	//verifica se o codigo funcionou como deveria
	if(f_final != NULL){
		printf("Arquivo gerado. \n");
	}else{
		printf("Falha no processamento. \n");
	}

	//fechamento de arquivos
    fclose(f_final);													
    free(reg);
    free(no);

	
}

void sort_arquivo(char* nome_arq, char* nome_fim){
	FILE* arq = fopen(nome_arq,"rb");
	REGISTRO* aux = malloc(sizeof(REGISTRO));
	int size,i = 0,j = 0;
	while(!feof(arq)){
		fread(aux,sizeof(REGISTRO),1,arq);
		size++;
	}
	REGISTRO *reg = malloc(size*(sizeof(REGISTRO)));
	fseek(arq,0,SEEK_SET);
	while(!feof(arq)){
		fread(&reg[i],64,1,arq);
		printf("%s\n",reg[i].nome);
		i++;
	}
	
	
	int quantidade = size/1000;									//quantidade de arquivos a ser criado, so cabe 1000 registros em cada pagina de disco
	char str[quantidade][50],str2[quantidade][50];
	FILE** arquivos = malloc((quantidade+1)*sizeof(FILE*));
	char nome[50];
	strcpy(str[quantidade], "sub_arquivo");
	strcpy(str2[quantidade], "sub_arquivof");
	
	//Criam-se strings para os nomes ods arquivos
	
	for(i=0;i<quantidade+1;i++){
		printf("oi");
		sprintf(str[i],"sub_arquivo%d.bin",i);					//sprintf escreve um valor na string
		sprintf(str2[i],"sub_arquivo%d.bin",i);
		arquivos[i] = fopen(str[quantidade],"wb");
		while(reg != NULL){

			fwrite(&reg[j],sizeof(REGISTRO),1,arquivos[i]);		//escrita no arquivo
			j++;
		}
		ordena_arquivo(str[i],str2[i]);							//ordena cada um ods subarquivos um por um
		fclose(arquivos[i]);
	}
	
	
	//multiway_arquivo(1000,str2);								//Usa-se o multiway merging para juntar todos os subv arquivos
	//NAO CONSEGUIMOS CHAMAR A FUNCAO MULTIWAY, PARAMOS O ALGORITMO AQUI
	
	fclose(arq);
}