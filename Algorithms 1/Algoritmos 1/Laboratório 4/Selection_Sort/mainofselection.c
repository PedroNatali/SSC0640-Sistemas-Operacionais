#include <stdio.h>
#include <stdlib.h>

#define TA 10
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

void bubble_sort_4 (int vetor[], int n) {
 int k, j, aux;
 	for (k = n - 1; k > 0; k--) {
 		for (j = k; j > 0; j--) {
			if (vetor[j] < vetor[j + 1]) {
				aux = vetor[j];
				vetor[j] = vetor[j + 1];
 				vetor[j + 1] = aux;
 			}
 		}
 	}
}
int main(int argc, char *argv[]) {
	int i, vet[TA];
	srand(time(NULL));
	
	 for(i = 0; i < TA; i++){
		vet[i] = rand()%TA;
 	}
 	
 	bubble_sort(vet, TA);
 	
 	
 	
	return 0;
}
