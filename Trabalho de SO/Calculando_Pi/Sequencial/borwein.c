/* Pedro Natali - 10310655
- Para compilação no linux, utilizar -lm. 
- gcc nome_programa.c -o nome_programa - lm */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

double borwein(int numero_interacoesB){
	int i;
	double aux = 0;
	double pi = 0;
	double aux2,aux3,aux4,aux5,aux6,aux7;
	for(i = 0; i < numero_interacoesB; i++){
		aux2 = pow(16,i);
		aux3 = 8*i + 1;
		aux4 = 8*i + 4;
		aux5 = 8*i + 5;
		aux6 = 8*i + 6;
		aux = (1/aux2) * ((4/aux3) - (2/aux4) - (1/aux5)- (1/aux6));
		pi = pi + aux;
	}
	return pi;

}

int main (){
    int num_int = 1000000000; //numero desejado para as interações 
    printf("Borwein: %1.6f\n", borwein(num_int));
    return 0;
}