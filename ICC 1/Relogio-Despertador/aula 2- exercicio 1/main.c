#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int main()
{
    int hora, minuto, segundo, x, y, z;
    hora=minuto=segundo=x=y=z=0;
    printf("Escolha a hora para despertar :\n");
    scanf("%d %d %d",&x,&y,&z);
;
while(1)
    {
    printf("\r %2dh %2dm %2ds", hora, minuto, segundo);
    if((hora==x)&&(minuto==y)&&(segundo==z)){
    printf("\n ACORDA!!!!!!!");
    break;
    }
    segundo++;
    if(segundo==60){segundo=0; minuto++;}
    if(minuto==60){minuto=0; hora++;}
    if(hora==24){hora=0;}
    sleep(1);
    }
    return 0;
}


