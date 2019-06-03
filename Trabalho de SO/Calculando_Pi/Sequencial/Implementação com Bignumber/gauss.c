/* Pedro Natali - 10310655
- Para compilação no linux, lembrar de incluir as bibliotecas, como descrito abaixo. 
- gcc nome_programa.c -o nome_programa - lm -lgmp */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <gmp.h>    

void gauss(int numero_iteracoesG){
    //definindo a precisao
    mpf_set_default_prec(pow(10,5));

    //declarando as variaveis que serao inicializadas como 0
    mpf_t pi,a_prox,b_prox,t_prox,aux_1,aux_2,
    aux_3,aux_4,aux_5,p,a,b,t,aux,aeb_aux,peaux3_aux;
    mpf_init(pi);
    mpf_init(a_prox);
    mpf_init(b_prox);
    mpf_init(t_prox);
    mpf_init(aux);
    mpf_init(aux_1);
    mpf_init(aux_2);
    mpf_init(aux_3);
    mpf_init(aux_4);
    mpf_init(aux_5);
    mpf_init(aeb_aux);
    mpf_init(peaux3_aux);

    //definindo a,b,p e t iniciais
    mpf_init_set_d(a, 1);
    mpf_init_set_d (b, 1/sqrt(2));
    mpf_init_set_d (t, 0.25);
    mpf_init_set_d (p, 1);

    //iterador
    int i;

    //double a = 1;
    //double b = 1/sqrt(2);
    //double t = 0.25;
    //double p = 1;
    //double pi;
    //double a_prox, b_prox, t_prox, aux_1, aux_2;
    
    for(i = 0; i < numero_iteracoesG; i++){
        //a_prox = (a + b)/2 - calcula a(n+1)
        mpf_add(aux, a, b);
        mpf_div_ui(a_prox,aux,2);

        //b_prox = sqrt(a * b) - calcula b(n+1)
        mpf_mul(aeb_aux, a, b);
        mpf_sqrt(b_prox, aeb_aux);

        //aux_1 = a - a_prox;
        mpf_sub(aux_1, a, a_prox);

        //t_prox = t - p*(pow(aux_1, 2)) - calcula t(n+1)
        mpf_pow_ui(aux_3, aux_1, 2);
        mpf_mul(peaux3_aux, p, aux_3);
        mpf_sub(t_prox, t, peaux3_aux);

        //p = p * 2 - calcula p(n+1)
        mpf_mul_ui(p, p, 2);

        //atualiza as variáveis
        mpf_set(a,a_prox);
        mpf_set(b,b_prox);
        mpf_set(t,t_prox);

        //a = a_prox;
        //b = b_prox;
        //t = t_prox;
    }
    //calcula pi

    //aux_2 = a + b;
    mpf_add(aux_2, a, b);

    //aux 4 = aux2²
    mpf_pow_ui(aux_4, aux_2, 2);

    //aux 5 = 4*t
    mpf_mul_ui(aux_5,t, 4);

    //pi = aux 4 / aux 5 = pow(aux2, 2) / 4 * t
    mpf_div(pi, aux_4,aux_5);
    gmp_printf("Gauss : %.6Ff\n", pi);
}

int main (){
    int num_itg = 100000; //numero maximo que o Gauss roda
    //printf("Gauss: %1.6f\n", gauss(num_intg));
    gauss(num_itg); 
    return 0;
}