all: main queue.o

.PHONY: clean

main: main.c queue.o
	clang -Wall main.c queue.o -o main

queue.o: queue.c
	clang -Wall queue.c -c -o queue.o

clean:
	rm -f main queue.o
