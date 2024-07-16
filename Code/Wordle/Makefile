all: wordle api-wordle

.PHONY: clean

wordle: wordle.c
	clang -Wall wordle.c -o wordle

api-wordle:
	clang -Wall api-wordle.c -o api-wordle -lcurl -ljson-c

clean:
	rm -f wordle api-wordle
