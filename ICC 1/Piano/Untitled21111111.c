#include <windows.h>

int main(){
    int tecla;
    while(1)
    if(kbhit()){
    tecla = getch();
       if (tecla == 'a'){
          printf("Do\n") ;
          Beep (261, 50);
       }
       if (tecla == 's'){
          printf("Re\n");
          Beep (293, 5000);
       }
       if (tecla == 'd'){
          printf("Mi\n");
          Beep (329, 500);
       }
       if (tecla == 'f'){
          printf("Fa\n");
          Beep (349, 500);
       }
       if (tecla == 'g'){
          printf("Sol\n");
          Beep (392, 500);
       }
       if (tecla == 'h'){
          printf("La\n");
          Beep (440, 500);
       }
       if (tecla == 'j'){
          printf("Si\n");
          Beep (493, 500);
       }
    }
    return 0;
}

