/* Pedro Natali - 10310655
- Para compilação no linux, utilizar -lm. 
- gcc nome_programa.c -o nome_programa - lm */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>


double gauss(int numero_interacoesG){
    double a = 1;
    double b = 1/sqrt(2);
    double t = 0.25;
    double p = 1;
    double pi;
    double a_prox, b_prox, t_prox, aux_1, aux_2;
    int i;


    for(i = 0; i < numero_interacoesG; i++){
        a_prox = (a + b)/2; //calcula a(n+1)
        b_prox = sqrt(a * b); //calcula b(n+1)
        aux_1 = a - a_prox;
        t_prox = t - p*(pow(aux_1, 2)); //calcula t(n+1)
        p = p * 2 ; // calcula p(n+1)

        //atualiza as variáveis
        a = a_prox;
        b = b_prox;
        t = t_prox;
    }
    //calcula pi
    aux_2 = a + b;
    pi = pow(aux_2, 2) / (4*t);
    return pi;
}

int main (){
    int num_intg = 1024; //numero maximo que o Gauss roda
    printf("Gauss: %1.6f\n", gauss(num_intg));
    return 0;
}