#include<stdio.h>

#include<math.h>


int main () {

  float n;

  scanf("%f", &n);

  if (n>=0){

  double param, result;

  param = n;

  result = sqrt (param);

  printf("(%.2f\n)", result);

  } else {

  printf("Inválido");

  }

  return 0;

}
