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

	//double ptos;
	//double pto_dentro = 0;
	//double x;
	//double y;
	//double pi;
	//declarando as variaveis
	mpf_t ptos, pto_dentro, x, y, pi;
	mpf_t aux_x, aux_y, aux_x_y, aux_4_pto;
	gmp_randstate_t state;

	//iniciando as variaveis
	mpf_init(pto_dentro);
	mpf_init(ptos);
	mpf_init(x);
	mpf_init(y);
	mpf_init(pi);
	mpf_init(aux_y);
	mpf_init(aux_x);
	mpf_init(aux_x_y);
	mpf_init(aux_4_pto);
	gmp_randinit_default(state);
	int i;

	//ptos = numero de iteracoes
	mpf_init_set_ui(ptos, numero_iteracoesM);

	//srand(time(NULL));

	for(i = 0; i < numero_iteracoesM; i++){
		//x = ((double)rand()/(double)RAND_MAX); 
		mpf_urandomb (x,state,10);

		//y = ((double)rand()/(double)RAND_MAX);
		mpf_urandomb (y,state,10);

		//aux_x = x²
		mpf_pow_ui(aux_x, x, 2);

		//aux_y = y²
		mpf_pow_ui(aux_y, y, 2);

		//aux_x_y = x² + y²
		mpf_add(aux_x_y, aux_x, aux_y);
    	//gmp_printf("aux_x_y : %.6Ff\n", aux_x_y); 

		//se x²+y² <= 1
		if(mpf_cmp_ui(aux_x_y, 1) < 1){
			mpf_add_ui(pto_dentro, pto_dentro, 1);
    		//gmp_printf("pto_dentro : %.6Ff\n", pto_dentro);
			//pto_dentro = pto_dentro + 1; - atualiza os pontos dentro do círculo se x²+y² <= 1 (definição)
		}
	}
	//aux_4_pto = 4 * ptos_dentro
	mpf_mul_ui(aux_4_pto, pto_dentro, 4);

	//pi = (4*pto_dentro/ptos); //calcula pi
	mpf_div(pi, aux_4_pto, ptos);

    gmp_printf("Monte Carlo : %.6Ff\n", pi);
	//return pi;
}
int main (){
    int num_int = 1000000000; //numero desejado para as interações 
    //printf("Monte Carlo: %1.6f\n", monte_carlo(num_int));
    monte_carlo(num_int);
    return 0;
}