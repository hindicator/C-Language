.PHONY: all

all: mat.o input.o mainmat clean

mat.o: mat.c
	gcc -c mat.c -o mat.o -Wall -ansi -std=c90 -pedantic

input.o: input.c
	gcc -c input.c -o input.o -Wall -ansi -std=c90 -pedantic

mainmat: mat.o input.o input.c mat.c mainmat.c
	gcc mat.o input.o mainmat.c -o mat -Wall -ansi -std=c90 -pedantic

clean:
	rm *.o
	@echo "Done ...\n"