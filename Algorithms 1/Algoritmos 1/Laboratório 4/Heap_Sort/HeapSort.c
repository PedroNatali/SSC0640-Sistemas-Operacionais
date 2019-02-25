#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
#define TA 100000

int c = 0;

void swap(int *x, int *y){ 
   int temp;
   temp=*x;
   *x=*y;
   *y=temp;
}
	
void heapify(int arr[], int n, int i){
	int largest = i;
	int l = 2*i + 1;
	int r = 2*i + 2;
	if (l < n && arr[l] < arr[largest]){
		largest = l;
		c++;
	}
	if (r < n && arr[r] < arr[largest]){
		largest = r;
		c++;
	}
	if (largest != i){
		c++;
		swap(&arr[i], &arr[largest]);
		heapify(arr, n, largest);
		}
}

void heapSort(int arr[], int n){
	int i;
	for (i = n / 2 - 1; i >=0; i--){
		c++;
		heapify(arr, n, i);
	}
	for (i = n-1; i >=0; i--){
		c++;
		swap(&arr[0], &arr[i]);
		heapify(arr, i, 0);
	}
}

int main() {
	int v[TA], i, j;
	srand(time(NULL));
	
	for(i = 0; i<TA; i++){
		v[i] = rand()%TA;
	} 	
	
	heapSort(v,TA);
	
	printf("%d", c);
	
	return 0;
}
