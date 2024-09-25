# Run the Deq I implemented.

val: deq #valgrind
	printf "\n\n"
	valgrind --leak-check=full --leak-resolution=high ./prg
	printf "\n\n"

deq: main.o deq.o #linker step
	gcc -o prg main.o deq.o -Wall

# New target for shared library
libdeq.so: deq.o
	gcc -shared -o $@ $< -lc

# New phony target to build shared library
.PHONY: shared
shared: libdeq.so

#g debug (gdb)
#-O optimization not debug mode
main.o: main.c #compile main
	gcc -Wall -c -g main.c

deq.o: deq.c #compile deq
	gcc -Wall -c -fPIC -g deq.c

clean: #clean remove object and executables and clear screen
	rm -f main.o deq.o prg a.out deq deq.d main.d libdeq.so
	clear
