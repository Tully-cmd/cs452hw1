#Run the Deq shared library.

prog=deq
include ../GNUmakefile
try: main.o liblistdeq.so
	gcc -o $@ $< -L. -ldeq -Wl,-rpath=.
