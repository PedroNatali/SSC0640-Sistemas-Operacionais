#include <stdio.h>
#include <stdlib.h>

#define TA 100000
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

void bubble_sort_4 (int vetor[], int n) {
 	int k, j, aux;
 	int c=0;
 	for (k = 0; k < n; k++) {
 		c++;
 		for (j = k-1 ; j >= 0; j--) {
			if (vetor[j] < vetor[j + 1]) {
				aux = vetor[j];
				vetor[j] = vetor[j + 1];
 				vetor[j + 1] = aux;
 			}
 		c++;
		}
 	}
	printf("%d",c);
}
int main(int argc, char *argv[]) {
	int i, vet[TA];
	srand(time(NULL));
	
	 for(i = 0; i < TA; i++){
		vet[i] = rand()%TA;
 	}
 	
 	bubble_sort_4(vet, TA);
 	
	return 0;
}
