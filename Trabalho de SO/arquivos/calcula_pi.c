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
    int num_intg = 1024; //numero maximo que o Gauss roda
    printf("Gauss: %1.6f\n", gauss(num_intg));
    printf("Monte Carlo: %1.6f\n", monte_carlo(num_intg));
    printf("Borwein: %1.6f\n", borwein(num_int));
    return 0;
}