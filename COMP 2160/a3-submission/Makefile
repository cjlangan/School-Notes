all: main-zones

.PHONY: clean submit

main-zones: main-zones.c zones.o
	clang -Wall main-zones.c zones.o -g -o main-zones

zones.o: zones.c
	clang -Wall zones.c -c -o zones.o

clean:
	rm -f main-zones zones.o

submit:
	cp zones.c main-zones.c README.md Makefile a3-submission/
   
