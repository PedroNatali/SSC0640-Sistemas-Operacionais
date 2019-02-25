#include <stdio.h>
#include <stdlib.h>
int a=0;
int FF (int n){
    if (n <= 1){
        return n;
    } else {
        return n * FF(n-1);
    }
}

 void primo(int n, int j){
     if (j>1){
           if(n%j==0){
                a++;
                primo(n,j-1);
      }
      }
      if (a==1){
        printf("e");
      }
      else{
        printf("NE");
      }


 }

int main(){
    int n, j;
    scanf("%d", &n);
    j = FF(n);
    printf(" %d  \n ", j);
    primo(j,j);

    return 0;
}
