/* Pedro Natali - 10310655
- Para compilação no linux, utilizar -lm. 
- gcc nome_programa.c -o nome_programa - lm */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <gmp.h>
#include <pthread.h>

#define numero_threads 100000

mpf_t aux2,aux3,aux4,aux5,aux6,aux7, aux8 ,aux9,i8,pi, aux, n_1, n_2, n_4, n_8, n_16;

void *calc_aux2(void *numero_int){
	int thrnum2 = *((int *)numero_int);
	//aux2 = pow(16,i);
	mpf_pow_ui(aux2, n_16, thrnum2);
	mpf_div(aux2, n_1, aux2);
	pthread_exit(0);
}

void *calc_aux3(void *numero_int2){
	int thrnum3 = *((int *)numero_int2);
	
	//aux3 = 8*i + 1;
	mpf_add_ui(aux3,i8, 1);
	mpf_div(aux3, n_4, aux3);
	pthread_exit(0);
}

void *calc_aux4(void *numero_int3){
	int thrnum4 = *((int *)numero_int3);

	//aux4 = 8*i + 4;
	mpf_add_ui(aux4, i8, 4);
	mpf_div(aux4, n_2, aux4);
	pthread_exit(0);
}

void *calc_aux5(void *numero_int4){
	int thrnum5 = *((int *)numero_int4);

	//aux5 = 8*i + 5;
	mpf_add_ui(aux5, i8, 5);
	mpf_div(aux5, n_1, aux5);
	pthread_exit(0);
}

void *calc_aux6(void *numero_int5){
	int thrnum6 = *((int *)numero_int5);

	//aux6 = 8*i + 6;
	mpf_add_ui(aux6, i8, 6);
	mpf_div(aux6, n_1, aux6);
	pthread_exit(0);
}


void borwein(){
    //definindo a precisao
    mpf_set_default_prec(pow(10,5));

    //setando algumas variaveis como 0
	int i = 0;
	mpf_init(i8);
	mpf_init(pi);
	mpf_init(aux);
	mpf_init(aux2);
	mpf_init(aux3);
	mpf_init(aux4);
	mpf_init(aux5);
	mpf_init(aux6);
	mpf_init(aux7);
	mpf_init(aux8);
	mpf_init(aux9);

	//setando algumas variaveis diferentes de 0
	mpf_init_set_ui(n_1,1);
	mpf_init_set_ui(n_2,2);
	mpf_init_set_ui(n_4,4);
	mpf_init_set_ui(n_8,8);
	mpf_init_set_ui(n_16,16);

    pthread_t tid_aux2[numero_threads];  // ID das threads
    pthread_t tid_aux3[numero_threads];  // ID das threads
    pthread_t tid_aux4[numero_threads];  // ID das threads
    pthread_t tid_aux5[numero_threads];  // ID das threads
    pthread_t tid_aux6[numero_threads];  // ID das threads

	for(i = 0; i < numero_threads; i++){

		mpf_mul_ui(i8, n_8, i);
		// cria as threads necessarias
		pthread_create (&tid_aux2[i], NULL, calc_aux2, &i);
		pthread_create (&tid_aux3[i], NULL, calc_aux3, &i);
		pthread_create (&tid_aux4[i], NULL, calc_aux4, &i);
		pthread_create (&tid_aux5[i], NULL, calc_aux5, &i);
		pthread_create (&tid_aux6[i], NULL, calc_aux6, &i);
		

		// espera que as threads terminem
		pthread_join (tid_aux2[i], NULL);
		pthread_join (tid_aux3[i], NULL);
		pthread_join (tid_aux4[i], NULL);
		pthread_join (tid_aux5[i], NULL);
		pthread_join (tid_aux6[i], NULL);


		//aux = (1/aux2) * ((4/aux3) - (2/aux4) - (1/aux5)- (1/aux6));
		mpf_sub(aux7,aux3,aux4);
		mpf_sub(aux8,aux7,aux5);
		mpf_sub(aux9,aux8,aux6);
		mpf_mul(aux,aux2,aux9);
		mpf_add(pi, pi, aux);
	}

    gmp_printf("Borwein : %.6Ff\n", pi);

}

int main (){
    //printf("Borwein: %1.6f\n", borwein(num_int));
    borwein();

    //dando clear nas variaveis
    mpf_clear(i8);
	mpf_clear(pi);
	mpf_clear(aux);
	mpf_clear(aux2);
	mpf_clear(aux3);
	mpf_clear(aux4);
	mpf_clear(aux5);
	mpf_clear(aux6);
	mpf_clear(aux7);
	mpf_clear(aux8);
	mpf_clear(aux9);
	mpf_clear(n_1);
	mpf_clear(n_2);
	mpf_clear(n_4);
	mpf_clear(n_8);
	mpf_clear(n_16);
    return 0;
}