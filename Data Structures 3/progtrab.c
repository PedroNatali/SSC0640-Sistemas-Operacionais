/*
@authors
	Pedro Natali - 10310655
	Rafael Pinho - 10276737
	Paulo de Moura - 10310471
	Renan Varoni - 10310676

@about
	Trabalho referente a disciplina de Estrutura de Dados 3 (SCC06070). 
	USP - Sao Carlos.

*/


#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include "funcionalidades.h"

enum {
	NOME,
	OPERACAO,
	ARG1,
	ARG2,
	ARG3
};


int main(int argc, char *argv[]) {
	
	//variavel que analisa qual operacao sera utilizada
	int funcionalidade = atoi(argv[OPERACAO]);
	int auxiliar;

	switch (funcionalidade) {
		case 1: //Gera arquivo binario
			if(atoi(argv[ARG2]) > 6000){
				printf("O maior número permitido de registros é 6000. \n");
				break;
			}
			geracao_de_registros(argv[ARG1], atoi(argv[ARG2]));
			break;

		case 2 : //printa arquivo inteiro
			imprimir_arq_bin(argv[ARG1]);
			break;

		case 3 : //ordenacao interna do arquivo
			ordena_arquivo(argv[ARG1], argv[ARG2]);
			break;

		case 4 : //executa a operacao de merging no arquivo
			merging_arquivo(argv[ARG1], argv[ARG2], argv[ARG3]);
			break;

		case 5 : //executa a operacao de matching no arquivo
			matching_arquivo(argv[ARG1], argv[ARG2],argv[ARG3]);
			break;

		case 6 : //executa a operacao de multiway merging
			auxiliar = argc - 2;
			multiway_arquivo(auxiliar, argv); //descobrir como chamar a multiway
			break;

		case 7 : //executa a operacao de sort-merge externo
			sort_arquivo(argv[ARG1], argv[ARG2]);
			break;
		
		default :
			printf("Valor invalido de operacao. \n");
			printf("As operacoes permitidas variam de 1 a 7. \n");
	}
	return 0;
}

