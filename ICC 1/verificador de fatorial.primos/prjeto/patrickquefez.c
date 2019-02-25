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
               }
      primo(n,j-1);
      } else if (j==1){
      if (a==1){
        printf("primo");
      }else if ( a > 1) {
        printf("Nao primo");
      }
}

 }
//
//int primo (int j){
//    int a=0, n=j;
//    if (n>1){
//        if ((j%n) == 0){
//            a++;
 //           n--
 //           return primo(j);
 //       }
 //   }
 //   if (n==1){
 //       if(a==1){
 //           printf("E primo");
 //       }else{
 //           printf ("Nao e primo");
 //       }
//    }
//}//


int main(){
    int n, j;
    scanf("%d", &n);
    j = FF(n);
    printf(" %d  \n ", j);
    primo(j,j);

    return 0;
}
