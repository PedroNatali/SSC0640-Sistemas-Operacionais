	/* Pedro Natali - 10310655
- Para compilação no linux, utilizar -lm. 
- gcc nome_programa.c -o nome_programa - lm */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <pthread.h>

#define numero_threads 4 

//variaveis globais
double S, E, r, sigma, T;
double trials[100000];
int M;

int acerto_0, acerto_1, acerto_2, acerto_3;

void *black_scholes(void *numero_int){
	int thrnum = *((int *)numero_int);
	int i = 0;
	double aux1,aux2,aux4,aux5,aux6,aux7,t, max;
	srand(time(NULL));

	if(acerto_0 == 1 && thrnum == 0){
		thrnum = 1;
		if(acerto_1 == 1){
			thrnum = 2;
			if(acerto_2 == 1){
				thrnum = 3;
			}
		}
	}

	if(acerto_1 == 1 && thrnum == 1){
		thrnum = 2;
		if(acerto_2 == 1){
			thrnum = 3;
			if(acerto_3 == 1){
				thrnum = 0;
			}
		}
	}
	
	if(acerto_2 == 1 && thrnum == 2){
		thrnum = 3;
		if(acerto_3 == 1){
			thrnum = 0;
			if(acerto_0 == 1){
				thrnum = 1;
			}
		}
	}

	if(acerto_3 == 1 && thrnum == 3){
		thrnum = 0;
		if(acerto_0 == 1){
			thrnum = 1;
			if(acerto_1 == 1){
				thrnum = 2;
			}
		}
	}	

	if(thrnum == 0){
		acerto_0 = 1;
		for(i = 0; i < M/4; i++){

			aux1 = T*(r - 0.5*sigma*sigma);
			//printf("aux1 %d = %lf\n",i, aux1);
			aux2 = sigma*sqrt(T);
			//printf("aux2 %d = %lf\n",i, aux2);
			aux4 = ((double)rand()/(double)RAND_MAX);
			//printf("aux4 %d = %lf\n",i, aux4);
			aux5 = aux2*aux4;
			//printf("aux5 %d = %lf\n",i, aux5);
			aux6 = aux1+aux5;
			//printf("aux6 %d = %lf\n",i, aux6);

			t = S*pow(M_E, aux6); //aqui foi calculado t, temporario.
			
			//max{t-E, 0}
			if(t-E > 0){
	        	max = t-E;
			}else{
	        	max = 0;
			}

			//agora vamos encontrar o trials
			aux7 = pow(M_E, -r*T);
			trials[i] = aux7*max;
		}
	
	}else if(thrnum == 1){
		acerto_1 = 1;
		for(i = M/4; i < M/2; i++){

			aux1 = T*(r - 0.5*sigma*sigma);
			//printf("aux1 %d = %lf\n",i, aux1);
			aux2 = sigma*sqrt(T);
			//printf("aux2 %d = %lf\n",i, aux2);
			aux4 = ((double)rand()/(double)RAND_MAX);
			//printf("aux4 %d = %lf\n",i, aux4);
			aux5 = aux2*aux4;
			//printf("aux5 %d = %lf\n",i, aux5);
			aux6 = aux1+aux5;
			//printf("aux6 %d = %lf\n",i, aux6);

			t = S*pow(M_E, aux6); //aqui foi calculado t, temporario.
			
			//max{t-E, 0}
			if(t-E > 0){
	        	max = t-E;
			}else{
	        	max = 0;
			}

			//agora vamos encontrar o trials
			aux7 = pow(M_E, -r*T);
			trials[i] = aux7*max;
		}
		
	}else if(thrnum == 2){
		acerto_2 = 1;
		for(i = (M/2); i < 3*M/4; i++){

			aux1 = T*(r - 0.5*sigma*sigma);
			//printf("aux1 %d = %lf\n",i, aux1);
			aux2 = sigma*sqrt(T);
			//printf("aux2 %d = %lf\n",i, aux2);
			aux4 = ((double)rand()/(double)RAND_MAX);
			//printf("aux4 %d = %lf\n",i, aux4);
			aux5 = aux2*aux4;
			//printf("aux5 %d = %lf\n",i, aux5);
			aux6 = aux1+aux5;
			//printf("aux6 %d = %lf\n",i, aux6);

			t = S*pow(M_E, aux6); //aqui foi calculado t, temporario.
			
			//max{t-E, 0}
			if(t-E > 0){
	        	max = t-E;
			}else{
	        	max = 0;
			}

			//agora vamos encontrar o trials
			aux7 = pow(M_E, -r*T);
			trials[i] = aux7*max;
		}

	}else if(thrnum == 3){
		acerto_3 = 1;
		for(i = (3*M/4); i < M; i++){

			aux1 = T*(r - 0.5*sigma*sigma);
			//printf("aux1 %d = %lf\n",i, aux1);
			aux2 = sigma*sqrt(T);
			//printf("aux2 %d = %lf\n",i, aux2);
			aux4 = ((double)rand()/(double)RAND_MAX);
			//printf("aux4 %d = %lf\n",i, aux4);
			aux5 = aux2*aux4;
			//printf("aux5 %d = %lf\n",i, aux5);
			aux6 = aux1+aux5;
			//printf("aux6 %d = %lf\n",i, aux6);

			t = S*pow(M_E, aux6); //aqui foi calculado t, temporario.
			
			//max{t-E, 0}
			if(t-E > 0){
	        	max = t-E;
			}else{
	        	max = 0;
			}

			//agora vamos encontrar o trials
			aux7 = pow(M_E, -r*T);
			trials[i] = aux7*max;
			}
	}	
}


int main(){

	int i = 0;
	double soma= 0;
	double soma2 = 0;
	double vari, conf_min, conf_max, stddev, itv_conf, media;
	//pegando os valores do arquivo de entrada
	scanf("%lf %lf %lf %lf %lf %d ", &S, &E, &r, &sigma, &T, &M);
	pthread_t tid[numero_threads];  // ID das threads

	// Para todas as threads      
	for (i = 0; i< numero_threads ; i++){
		// cria a i-esima thread
		pthread_create (&tid[i], NULL, black_scholes, &i);
	}
    
 
	// Para cada thread 
	for (i = 0; i< numero_threads ; i++){
		// espera que as threads terminem
		pthread_join (tid[i], NULL);
    }	

    //calculando a media
	for(i = 0 ; i < M ; i++){
		soma = soma + trials[i];
	} 
	media = soma/(double)M;

	//calculando a variancia e o desvio padrao
	for(i = 0 ; i < M; i++){
        soma2 = soma2 + ((trials[i]-media)*(trials[i]-media));
    }
    vari = soma2/(double)M;
    stddev = sqrt(vari);

    //calculando o intervalo de confianca
	itv_conf = (1.96*stddev)/(double)(sqrt(M));
	conf_min = media - itv_conf;
	conf_max = media + itv_conf;


	//imprimindo o intervalo de confianca
	printf("S        %0.lf\n",S);
	printf("E        %0.lf\n",E);
	printf("r        %0.lf\n",r);
	printf("sigma    %0.lf\n",sigma);
	printf("T        %0.lf\n",T);
	printf("M        %d\n",M);
	printf("Confidence interval: (%lf,%lf)\n", conf_min,conf_max);

	return 0;
}