/* Pedro Natali - 10310655
- Para compilação no linux, utilizar -lm. 
- gcc nome_programa.c -o nome_programa - lm */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <gmp.h>


void monte_carlo(int numero_iteracoesM){
	//definindo a precisao
    mpf_set_default_prec(pow(10,5));

    //declarando variaveis
	mpf_t ptos, pto_dentro, pi;

	//iniciando as variaveis
	mpf_init(pto_dentro);
	mpf_init(ptos);
	mpf_init(pi);
	int i;
	double x;
	double y;

	//ptos = numero de iteracoes
	mpf_init_set_ui(ptos, numero_iteracoesM);

	//srand(time(NULL));

	for(i = 0; i < numero_iteracoesM; i++){
		x = ((double)rand()/(double)RAND_MAX); 
		y = ((double)rand()/(double)RAND_MAX);
		if(x*x + y*y <= 1){
			mpf_add_ui(pto_dentro, pto_dentro, 1);
		}
	}
	//ptos_dentro = 4 * ptos_dentro
	mpf_mul_ui(pto_dentro, pto_dentro, 4);

	//pi = (4*pto_dentro/ptos); //calcula pi
	mpf_div(pi, pto_dentro, ptos);

    gmp_printf("Monte Carlo : %.6Ff\n", pi);
	//return pi;


    //limpando as variaveis da memoria
	mpf_clear(pto_dentro);
	mpf_clear(ptos);
	mpf_clear(pi);
}
int main (){
    int num_int = 1000000000; //numero desejado para as interações 
    //printf("Monte Carlo: %1.6f\n", monte_carlo(num_int));
    monte_carlo(num_int);
    return 0;
}