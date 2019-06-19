/* Pedro Natali - 10310655
- Para compilação no linux, utilizar -lm. 
- gcc nome_programa.c -o nome_programa - lm */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <gmp.h>
#include <pthread.h>

#define numero_iteracoesM 25000000
#define numero_threads 4

mpf_t num_ptos_cir[numero_threads], pi, totalc;

void *monte_carlo(void *numero_int){
	int thrnum = *((int *)numero_int);
	//definindo a precisao
	mpf_set_default_prec(pow(10,5));
	mpf_init(num_ptos_cir[thrnum]);
	double x, y;;

	int i;
	//printf("%d\n",thrnum );

	for(i = 0; i < numero_iteracoesM; i++){
		x = (rand() % 10000001);
		y = (rand() % 10000001);
		x = x/10000000;
		y = y/10000000;
		//se x²+y² <= 1
		if( ((x*x) + (y*y)) <= 1){
			//adiciona o ponto ao vetor de pontos dentro
			mpf_add_ui(num_ptos_cir[thrnum], num_ptos_cir[thrnum],1);
		}
			//gmp_printf("Numero de pontos: %.6Ff\n", num_ptos_cir[thrnum]);
	}
	pthread_exit(0);
}
	
int main (){
	//definindo a precisao
	mpf_set_default_prec(pow(10,5));
	srand(time(NULL));

    int i = 0; //definindo iterador
    mpf_t totalp;
    mpf_init(totalc);
   	mpf_init(pi);

   	int ptos_total = numero_threads*numero_iteracoesM;
   	mpf_init_set_ui(totalp, ptos_total);

    pthread_t tid[numero_threads];  // ID das threads

	// Para todas as threads      
	for (i = 0; i< numero_threads ; i++){
		// cria a i-esima thread
		pthread_create (&tid[i], NULL, monte_carlo, &i);
    }	
 
	// Para cada thread 
	for (i = 0; i< numero_threads ; i++){
		// espera que as threads terminem
		pthread_join (tid[i], NULL);
    }	

    //cria uma variavel para esperar as iteracoes acabarem
    for (i = 0; i< numero_threads ; i++){
    	mpf_add(totalc, totalc, num_ptos_cir[i]);
    	//gmp_printf("totalc : %.6Ff	\n", totalc);
    }	
	mpf_mul_ui(pi, totalc, 4);
	mpf_div(pi,pi,totalp);

    gmp_printf("Monte Carlo : %.6Ff\n", pi);
    mpf_clear(pi);
    mpf_clear(totalp);
    mpf_clear(totalc);
}
