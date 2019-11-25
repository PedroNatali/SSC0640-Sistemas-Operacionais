# Implementação Paralela

Implementação dos três métodos numéricos(Borwein, Gauss e Monte Carlo) com a utilização da biblioteca gmp (bignumber) e pthreads. 

Método de compilação:
```
gcc nome_programa.c -o nome_programa -lm -lgmp -lpthread
```
Método de execução normal:
```
./nome_programa
```

Método de execução para que a saída seja printada no arquivo saida.txt.
```
./nome_programa<entrada_pi.txt>saida_pi.txt
