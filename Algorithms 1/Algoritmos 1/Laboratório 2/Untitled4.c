#include <stdio.h>
#include <stdlib.h>

#define MAX 10000
int contador = 0;

void merge(int vetor[], int comeco, int meio, int fim) {
    int com1 = comeco, com2 = meio+1, comAux = 0, tam = fim-comeco+1;
    int *vetAux;
    vetAux = (int*)malloc(tam * sizeof(int));

    while(com1<=meio && com2<=fim){
        if(vetor[com1] <= vetor[com2]){
            vetAux[comAux] = vetor[com1];
            com1++;
            contador++;
        }else{
            vetAux[comAux] = vetor[com2];
            com2++;
            contador++;
        }
        comAux++;
    }

    while(com1<=meio){  //Caso ainda haja elementos na primeira metade
        vetAux[comAux] = vetor[com1];
        comAux++;com1++;
        contador++;
    }

    while(com2<=fim){   //Caso ainda haja elementos na segunda metade
        vetAux[comAux] = vetor[com2];
        comAux++;com2++;
        contador++;
    }

    for(comAux=comeco;comAux<=fim;comAux++){    //Move os elementos de volta para o vetor original
        vetor[comAux] = vetAux[comAux-comeco];
        contador++;
    }
    
    free(vetAux);
}

void mergeSort(int vetor[], int comeco, int fim){
    if (comeco < fim) {
        int meio = (fim+comeco)/2;
        mergeSort(vetor, comeco, meio);
        mergeSort(vetor, meio+1, fim);
        merge(vetor, comeco, meio, fim);
    }
}


int main (void) {
  int i, v[MAX];
  srand(time(NULL));
  for(i=0; i<MAX; i++){
    v[i] = rand()%(2*MAX);
  }
  mergeSort(v,0, MAX-1);
  printf("%d\n", contador);
  return 0;
}
