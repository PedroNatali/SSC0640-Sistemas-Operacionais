
#include <stdio.h>

int primo(int n, int j, int a){
     if (j>1){
           if(n%j==0){
                primo(n,j-1, a+1);
               }
           else {
                primo(n,j-1,a);
           }

      } else {
            return a;
      }
}

int main (){

int n;
scanf ("&d", &n);
int k = primo (n,n,0);
printf("%d", k);

return 0;
}


