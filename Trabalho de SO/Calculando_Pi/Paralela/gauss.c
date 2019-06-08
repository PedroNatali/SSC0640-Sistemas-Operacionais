/* Pedro Natali - 10310655
- Para compilação no linux, lembrar de incluir as bibliotecas, como descrito abaixo. 
- gcc nome_programa.c -o nome_programa - lm -lgmp */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <gmp.h> 
#include <pthread.h>

#define numero_iteracoesG 10000

mpf_t a, b, a_prox; 
mpf_t b_prox,aux_1,p,t, t_prox;

void *calc_a(){
    //a_prox = (a + b)/2 - calcula a(n+1)
    mpf_add(a_prox, a, b);
    mpf_div_ui(a_prox,a_prox,2);

    //aux_1 = a - a_prox;
    mpf_sub(aux_1, a, a_prox);
    mpf_pow_ui(aux_1, aux_1, 2);
    
    pthread_exit(0);
}

void *calc_b(){
    //b_prox = sqrt(a * b) - calcula b(n+1)
    mpf_mul(b_prox, a, b);
    mpf_sqrt(b_prox, b_prox);
    
    pthread_exit(0);
}

void gauss(){
    //definindo a precisao
    mpf_set_default_prec(pow(10,5));

    //declarando as variaveis que serao inicializadas como 0
    mpf_t pi,aux_2;

    //iniciando variaveis como 0
    mpf_init(pi);
    mpf_init(a_prox);
    mpf_init(b_prox);
    mpf_init(t_prox);
    mpf_init(aux_1);
    mpf_init(aux_2);

    //definindo a,b,p e t iniciais
    mpf_init_set_d(a, 1);
    mpf_init_set_d(b, 1/sqrt(2));
    mpf_init_set_d(t, 0.25);
    mpf_init_set_d(p, 1);

    //iterador
    int i;

    pthread_t tid_auxa[numero_iteracoesG];// ID das threads
    pthread_t tid_auxb[numero_iteracoesG];// ID das threads
    
    for(i = 0; i < numero_iteracoesG; i++){

        //cria as threads
        pthread_create (&tid_auxa[i], NULL, calc_a, &i);
        pthread_create (&tid_auxb[i], NULL, calc_b, &i);

        //espera que as threads terminem para que a main continue
        pthread_join(tid_auxa[i],NULL);
        pthread_join(tid_auxb[i],NULL);

        //t_prox = t - p*(pow(aux_1, 2)) - calcula t(n+1)
        mpf_mul(aux_2, p, aux_1);
        mpf_sub(t_prox, t, aux_2);

        //atualiza as variáveis
        mpf_mul_ui(p, p, 2);
        mpf_set(a,a_prox);
        mpf_set(b,b_prox);
        mpf_set(t,t_prox);
    }
    //calcula pi

    //aux_2 = a + b;
    mpf_add(a, a, b);

    //aux 4 = aux2²
    mpf_pow_ui(a, a, 2);

    //aux 5 = 4*t
    mpf_mul_ui(t,t, 4);

    //pi = aux 4 / aux 5 = pow(aux2, 2) / 4 * t
    mpf_div(pi, a,t);
    gmp_printf("Gauss : %.6Ff\n", pi);

    //dando clear nas variaveis
    mpf_clear(pi);
    mpf_clear(a_prox);
    mpf_clear(b_prox);
    mpf_clear(t_prox);
    mpf_clear(aux_1);
    mpf_clear(aux_2);
    mpf_clear(a);
    mpf_clear(b);
    mpf_clear(t);
    mpf_clear(p);
}

int main (){
    //printf("Gauss: %1.6f\n", gauss(num_intg));
    gauss(); 

    return 0;
}