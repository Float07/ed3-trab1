all: *.c
	gcc -o programaTrab aux.c main.c -Wall
run:
	./programaTrab