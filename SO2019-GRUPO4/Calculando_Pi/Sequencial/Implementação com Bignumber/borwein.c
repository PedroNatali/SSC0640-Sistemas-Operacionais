/* Pedro Natali - 10310655
- Para compilação no linux, utilizar -lm. 
- gcc nome_programa.c -o nome_programa - lm */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <gmp.h>

void borwein(int numero_interacoesB){
    //definindo a precisao
    mpf_set_default_prec(pow(10,5));

    //declarando as variaveis
	int i;
	mpf_t pi, aux,aux2, aux3, aux4, aux5, aux6, aux7, aux8, aux9;
	mpf_t i8, n_1, n_2, n_4, n_8, n_16;
	mpf_init(pi);
	mpf_init(i8);
	mpf_init(aux);
	mpf_init(aux2);
	mpf_init(aux3);
	mpf_init(aux4);
	mpf_init(aux5);
	mpf_init(aux6);
	mpf_init(aux7);
	mpf_init(aux8);
	mpf_init(aux9);

	//setando algumas variaveis
	mpf_init_set_ui(n_1,1);
	mpf_init_set_ui(n_2,2);
	mpf_init_set_ui(n_4,4);
	mpf_init_set_ui(n_8,8);
	mpf_init_set_ui(n_16,16);

	//double aux = 0;
	//double pi = 0;
	//double aux2,aux3,aux4,aux5,aux6,aux7;


	for(i = 0; i < numero_interacoesB; i++){

		//aux2 = pow(16,i);
		mpf_pow_ui(aux2, n_16, i);
		mpf_div(aux2, n_1, aux2);
		
		//aux3 = 8*i + 1;
		mpf_mul_ui(i8, n_8, i);
		mpf_add_ui(aux3,i8, 1);
		mpf_div(aux3, n_4, aux3);

		//aux4 = 8*i + 4;
		mpf_add_ui(aux4, i8, 4);
		mpf_div(aux4, n_2, aux4);

		//aux5 = 8*i + 5;
		mpf_add_ui(aux5, i8, 5);
		mpf_div(aux5, n_1, aux5);

		//aux6 = 8*i + 6;
		mpf_add_ui(aux6, i8, 6);
		mpf_div(aux6, n_1, aux6);

		//aux = (1/aux2) * ((4/aux3) - (2/aux4) - (1/aux5)- (1/aux6));
		mpf_sub(aux7,aux3,aux4);
		mpf_sub(aux8,aux7,aux5);
		mpf_sub(aux9,aux8,aux6);
		mpf_mul(aux,aux2,aux9);

		mpf_add(pi, pi, aux);
		//pi = pi + aux;
	}

    gmp_printf("Borwein : %.6Ff\n", pi);

    mpf_clear(pi);
	mpf_clear(i8);
	mpf_clear(aux);
	mpf_clear(aux2);
	mpf_clear(aux3);
	mpf_clear(aux4);
	mpf_clear(aux5);
	mpf_clear(aux6);
	mpf_clear(aux7);
	mpf_clear(aux8);
	mpf_clear(aux9);

}

int main (){
    int num_int = 100000; //numero desejado para as interações 
    //printf("Borwein: %1.6f\n", borwein(num_int));
    borwein(num_int);
    return 0;
}