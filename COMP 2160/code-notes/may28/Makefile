all: main-list main-array

.PHONY: clean # "clean" is just the name of a target, not a file.

main-list: main.c strings-list.o
	clang -Wall main.c strings-list.o -o main-list

main-array: main.c strings-array.o
	clang -Wall main.c strings-array.o -o main-array

strings-list.o: strings-list.c
	clang -Wall strings-list.c -c -o strings-list.o

strings-array.o: strings-array.c
	clang -Wall strings-array.c -c -o strings-array.o

clean:
	rm -f main-list main-array strings-list.o strings-array.o
