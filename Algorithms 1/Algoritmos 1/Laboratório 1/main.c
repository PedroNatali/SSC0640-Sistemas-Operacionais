#include <stdio.h>
#include <stdlib.h>
 
// Define uma constante
// Define a constant
#define MAX 100000
 
// Protótipo da função de ordenação
// Ordination function prototype
void insertion_sort(int *a);
 
 int buscaBinaria (int x, int n, int v[]) {
   int e, m, d;                              // 1
   e = 0; d = n-1;                           // 2
   while (e <= d) {                          // 3
      m = (e + d)/2;                         // 4
      if (v[m] == x) return m;               // 5
      if (v[m] < x) e = m + 1;               // 6
      else d = m - 1;                        // 7
   }                                         // 8
   return -1;                                // 9
}        

int buscaSimples(int tamanho, int vetor[],int p)
{
 int i;
 for(i=0;i<=tamanho;i++)
 {
  if(vetor[i]==p){
   return i;
   }
 }
 return -1;

}

// Função main
// Main Function
int main(int argc, char** argv)
{
 int i, vet[MAX];
 srand(time(NULL));
 
 // Lê MAX ou 10 valores
 // Read MAX or 10 values
 for(i = 0; i < MAX; i++)
 {
	vet[i] = rand()%MAX;
 }
 // Ordena os valores
 // Order values

// tirar esse comentário se as funções requeridas forem a insertion ou a busca binária, deixar só -> insertion_sort(vet);
// tirar esse comentário se a função requerida for a busca Binária, deixar só -> buscaBinaria(rand()%MAX, 2*MAX, vet);
// tirar esse comentário se a função requerida for a Busca Simples, deixar só ->buscaSimples(2*MAX, vet, rand()%MAX);
return 0;
}
 
// Função de Ordenação por Inserção
// Insertion sort function
void insertion_sort(int *a)
{
 int i, j, tmp;
  
 for(i = 1; i < MAX; i++)
 {
  tmp = a[i];
  for(j = i-1; j >= 0 && tmp < a[j]; j--)
  {
   a[j+1] = a[j];
  }
  a[j+1] = tmp;
 }
}
