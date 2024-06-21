all: main table.o

.PHONY: clean

main: main.c table.o
	clang -Wall main.c table.o -o main

queue.o: queue.c
	clang -Wall table.c -c -o table.o

clean:
	rm -f main table.o
