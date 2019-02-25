#include<stdio.h>


int main () {

  int X, Y, Z;

  scanf("%d%d%d", &X, &Y, &Z);

  if ((X>Y)&&(X>Z)){

    printf("%d", X);

  }

  if ((Y>X)&&(Y>Z)){

    printf("%d", Y);

  }

  if ((Z>Y)&&(Z>X)){

    printf("%d", Y);

  }

  if ((X==Y)&&(Y==Z)&&(X==Z)){

    printf("%d\n", Y);

  }

  return 0;

}
