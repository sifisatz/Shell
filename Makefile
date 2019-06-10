#Sifis - Shell - Makefile - csd3094

main.o: main.c main.h
	gcc -c main.c
all: main.o
	gcc -ansi -pedantic -Wall -o main main.o
clean:
	rm *.o