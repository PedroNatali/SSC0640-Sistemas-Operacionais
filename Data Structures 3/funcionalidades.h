/*
@authors
	Pedro Natali - 10310655
	Rafael Pinho - 10276737
	Paulo de Moura - 10310471
	Renan Varoni - 10310676
*/


//header file

#ifndef FUNCIONALIDADES_H
#define FUNCIONALIDADES_H

void geracao_de_registros(char* nomeArquivoGerado,int size);

void imprimir_arq_bin(char *nome_arquivo);

void ordena_arquivo(char* nomeArquivo, char* nomeArquivoOrdenado);

void matching_arquivo(char *arquivo_1, char *arquivo_2, char *arquivo_saida);

void merging_arquivo(char *arquivo_1, char *arquivo_2, char *arquivo_saida);

void multiway_arquivo(int max, char** nomeArquivo);

void sort_arquivo(char* nomeArquivo, char* nomeArquivoGerado);


#endif