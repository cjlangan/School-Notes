all: main-list main-array main-test

.PHONY: clean # "clean" is just the name of a target, not a file.

main-test: main-test.c strings-list.o
	clang -Wall -g main-test.c strings-list.o -o main-test

main-list: main.c strings-list.o
	clang -Wall -g main.c strings-list.o -o main-list

main-array: main.c strings-array.o
	clang -Wall -g main.c strings-array.o -o main-array

strings-list.o: strings-list.c
	clang -Wall -g strings-list.c -c -o strings-list.o

strings-array.o: strings-array.c
	clang -Wall -g strings-array.c -c -o strings-array.o

clean:
	rm -f main-list main-array *.o main-test
