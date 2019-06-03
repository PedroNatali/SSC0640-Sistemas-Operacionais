	/* Pedro Natali - 10310655
- Para compilação no linux, utilizar -lm. 
- gcc nome_programa.c -o nome_programa - lm -lpthread*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <pthread.h>


double black_scholes(){
	int i, M;
	double S, E, r, sigma, T;
	double aux1,aux2,aux4,aux5,aux6,aux7,t;
	double soma= 0;
	double soma2 = 0;
	double vari, conf_min, conf_max, stddev, max, itv_conf;
	//pegando os valores do arquivo de entrada
	scanf("%lf %lf %lf %lf %lf %d ", &S, &E, &r, &sigma, &T, &M);
	double trials[M - 1], media;
	srand(time(NULL));

	for(i = 0; i < M - 1; i++){

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
		
		//nao sei fazer essa parte, tentar fazer depois
		if(t-E > 0){
        	max = t-E;
		}else{
        	max = 0;
		}
		//agora vamos encontrar o trials
		aux7 = pow(M_E, -r*T);
		trials[i] = aux7*max;

	}

	//calculando a media
	for(i = 0 ; i < M - 1 ; i++){
		soma = soma + trials[i];
	} 
	media = soma/(M - 1);

	//calculando a variancia e o desvio padrao
	for(i = 0 ; i < M - 1; i++){
        soma2 = soma2 + ((trials[i]-media)*(trials[i]-media));
    }
    vari = soma2/M - 1;
    stddev = sqrt(vari);

	itv_conf = (1.96*stddev)/(double)(sqrt(M - 1));
	conf_min = media - itv_conf;
	conf_max = media + itv_conf;

	printf("%lf\n", conf_min);
	printf("%lf\n", conf_max);

	return 0;

}

int main(){
	black_scholes();
	return 0;
}