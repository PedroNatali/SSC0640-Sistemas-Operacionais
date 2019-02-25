#include <stdio.h>


int main(){

    int x1,x2,x3;

    int n1,n2,n3;

    scanf("%d %d %d", &n1, &n2, &n3);

    if(n1<=n2){

        if(n1<=n3){

            x1=n1;

            if(n2<=n3){

                x2=n2;

                x3=n3;

            }else{

                x2=n3;

                x3=n2;

            }

        }else{

            x1=n2;

            x2=n3;

            x3=n1;

        }

    }else{

        if(n1<=n3){

        x1=n2;

        x2=n1;

        x3=n3;

        }else{

            x1=n2;

            x2=n3;

            x3=n1;

        }

    }

printf("%d %d %d", x1, x2, x3);

return 0;

}
