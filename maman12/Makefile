.PHONY: all

all: list_ab list_ab.o clean

list_ab.o:
	gcc -c list_ab.c -o list_ab.o -Wall -ansi -std=c90 -pedantic

list_ab: list_ab.o
	gcc list_ab.o -o list_ab -Wall -ansi -std=c90 -pedantic


clean:
	rm *.o
	@echo "Done ...\n"