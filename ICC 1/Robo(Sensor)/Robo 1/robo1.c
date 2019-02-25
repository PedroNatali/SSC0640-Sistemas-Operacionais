#include <stdio.h>
#include <stdlib.h>

int main()
{
   char = s1, s2, s3, m1, m2;
   while(1)
   if(kbhit()){
    tecla = getch()
    if(tecla=='a'){
        s1=0;
        s2=0;
        s3=1;
    }
    if(tecla=='s'){
        s1=1;
        s2=1;
        s3=1;
    }
    if(tecla=='d'){
        s1=1;
        s2=0;
        s3=0;
    }
   }
   if((s1==0)&&(s2==0)&&(s3==0)){
    m1=1;
    m2=1;
   }  else if((s1==1)&&(s2==0)&&(s3==0)){
       m1=1;
       m2=0;
      }
      else if((s1==0)&&(s2==1)&&(s3==0)){
       m1=0;
       m2=1;
      }
      else if((s1==0)&&(s2==0)&&(s3==1)){
       m1=0;
       m2=1;
      }
      else if((s1==1)&&(s2==1)&&(s3==0)){
       m1=1;
       m2=0;
      }
      else if((s1==1)&&(s2==0)&&(s3==1)){
       m1=1;
       m2=1;
      }
      else if((s1==0)&&(s2==1)&&(s3==1)){
       m1=0;
       m2=1;
      }

      else if((s1==1)&&(s2==1)&&(s3==1)){
      m1=0;
      m2=1;
      }
}
