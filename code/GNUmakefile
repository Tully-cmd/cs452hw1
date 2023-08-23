#prog=deq
#include ../GNUmakefile
#try: main.o libdeq.so
#	gcc -o $@ $< -L. -ldeq -Wl,-rpath=.

val: deq
	printf "\n\n"
	valgrind --leak-check=full --leak-resolution=high ./prg
	printf "\n\n"

deq: main.o deq.o
	gcc -o prg main.o deq.o -L libdeq.so

main.o: main.c
	gcc -Wall -c -g main.c

deq.o: deq.c
	gcc -Wall -c -g deq.c

clean: 
	rm -f main.o deq.o prg a.out
	clear
