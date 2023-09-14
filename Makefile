CC = gcc

all: run

run:
	./main

clean:
	rm -rf myMalloc.o main
main:
	gcc -c myMalloc.c -o myMalloc.o
	gcc my_main.c myMalloc.o -o main

.PHONY: all run compile clean
