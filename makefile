all: *.c
	gcc -o programaTrab *.c -Wall
run:
	./programaTrab
debug: 
	gcc -o programaTrab *.c -Wall -g
drun:
	gdb programaTrab 
	