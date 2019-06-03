/* Pedro Natali - 10310655
- Para compilação no linux, utilizar -lm. 
- gcc nome_programa.c -o nome_programa - lm */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>


double monte_carlo(int numero_interacoesM){
	double ptos;
	double pto_dentro = 0;
	double x;
	double y;
	double pi;
	srand(time(NULL));


	for(ptos = 0; ptos < numero_interacoesM; ptos++){
		x = (rand()%101);
		x = x/100; // encontra 0<x<1
		y = (rand()%101);
		y = y/100; // encontra 0<y<1
		if(pow(x,2) + pow(y,2) <= 1){
			pto_dentro = pto_dentro + 1; //atualiza os pontos dentro do círculo se x²+y² <= 1 (definição)
		}
	}
	pi = (4*pto_dentro/ptos); //calcula pi
	return pi;
}
int main (){
    int num_int = 1000000000; //numero desejado para as interações 
    printf("Monte Carlo: %1.6f\n", monte_carlo(num_int));
    return 0;
}