	/* Pedro Natali - 10310655
- Para compilação no linux, utilizar -lm. 
- gcc nome_programa.c -o nome_programa - lm */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

void black_scholes(){
	int i, M;
	double S, E, r, sigma, T;
	double aux1,aux2,aux4,aux5,aux6,aux7,t;
	double soma= 0;
	double soma2 = 0;
	double vari, conf_min, conf_max, stddev, max, itv_conf;
	//pegando os valores do arquivo de entrada
	scanf("%lf %lf %lf %lf %lf %d ", &S, &E, &r, &sigma, &T, &M);
	double trials[M], media;
	srand(time(NULL));

	for(i = 0; i < M; i++){

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

}

int main(){
	black_scholes();
	return 0;
}