#JUAN CARLOS ELIAS OBANDO VALDIVIA nro USP:7487156

all: clean matriz_esparsa.o main.o compile clean
compile:
	@gcc matriz_esparsa.o main.o -o trab3 -lm
main.o:
	@gcc -c main.c
matriz_esparsa.o:
	@gcc -c matriz_esparsa.c
clean:
	@find -name ’*~’ | xargs rm -rf {}
	@find -name ’*.o’ | xargs rm -rf {}
run:
	@./trab3
zip:
	zip -r trab3 *.c *.h Makefile
