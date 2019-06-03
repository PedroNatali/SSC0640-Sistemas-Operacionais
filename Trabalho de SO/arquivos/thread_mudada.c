/* Pedro Natali - 10310655
- Para compilação no linux, utilizar -lm. 
- gcc nome_programa.c -o nome_programa - lm -lpthread*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <pthread.h>

void *gauss(void* arg){
	int *num_int = (int*) arg;
	int numero_interacoesG = *num_int;
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
    printf("Gauss : %1.6lf\n", pi);
    pthread_exit(0);
}

void *borwein(void* arg){
	int *num_int2 = (int*) arg;
	int numero_interacoesB = *num_int2;
	int i;
	double aux = 0;
	double pi = 0;
	double aux2,aux3,aux4,aux5,aux6,aux7;
	//calcula o algoritmo pela definicao
	for(i = 0; i < numero_interacoesB; i++){
		aux2 = pow(16,i);
		aux3 = 8*i + 1;
		aux4 = 8*i + 4;
		aux5 = 8*i + 5;
		aux6 = 8*i + 6;
		aux = (1/aux2) * ((4/aux3) - (2/aux4) - (1/aux5)- (1/aux6));
		pi = pi + aux; //somatorio
	}
	printf("Borwein : %1.6lf\n", pi);
	pthread_exit(0);
}

void *monte_carlo(void* arg){
	int *num_int3 = (int*) arg;
	int numero_interacoesM = *num_int3;
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
	printf("Monte Carlo : %1.6lf\n", pi);
	pthread_exit(0);
}

int main (){
	pthread_t thread_idA;
 	pthread_t thread_idB;
 	pthread_t thread_idC;
 	int rstatus;
 	int numero_interacoesG = 1024; //numero maximo que consigo rodar o gauss
 	int numero_interacoes = 1000000000; //10⁹ interacoes

 	//Cria Thread A
 	rstatus = pthread_create (&thread_idA, NULL, gauss, &numero_interacoesG);
 	if(rstatus != 0){
 		printf ("Erro ao criar o thread A.\n");
 		exit(EXIT_FAILURE);
 	}
 	printf ("Thread A criado com sucesso!\n");
 	
 	//Cria Thread B
 	rstatus = pthread_create (&thread_idB, NULL, borwein, &numero_interacoes);
 	if(rstatus != 0){
 		printf ("Erro ao criar o thread B.\n");
 		exit(EXIT_FAILURE);
 	}
 	printf ("Thread B criado com sucesso!\n");

 	//Cria Thread C
 	rstatus = pthread_create (&thread_idC, NULL, monte_carlo, &numero_interacoes);
 	if(rstatus != 0){
 		printf ("Erro ao criar o thread C.\n");
 		exit(EXIT_FAILURE);
 	}
 	printf ("Thread C criado com sucesso!\n");

	//Finaliza Thread A
 	rstatus = pthread_join (thread_idA, NULL);
 	if(rstatus != 0){
		printf ("Erro ao aguardar finalização do thread A.\n");
 		exit(EXIT_FAILURE);
 	}else{
 		printf("Thread A Finalizada com Sucesso!\n");
 	}

 	//Finaliza Thread B
 	rstatus = pthread_join (thread_idB, NULL);
 	if(rstatus != 0){
		printf ("Erro ao aguardar finalização do thread B.\n");
 		exit(EXIT_FAILURE);
 	}else{
 		printf("Thread B Finalizada com Sucesso!\n");
 	}

 	//Finaliza Thread C
 	rstatus = pthread_join (thread_idC, NULL);
 	if(rstatus != 0){
		printf ("Erro ao aguardar finalização do thread C.\n");
 		exit(EXIT_FAILURE);
 	}else{
 		printf("Thread C Finalizada com Sucesso!\n");
 	}
    return 0;
}