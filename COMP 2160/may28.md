## Assignment2
- assignment2 usage has info on how to use the functions in stack.h
- to work with stack implementations, use aviary cuz compiled on linux x86
- prob need destroy_stack and check_stack

#### Makefile
- tells how to compile code and what have you
- can run mulitple commands at same time with `make`

```
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
```

- never tested on, can take and use
- not required for assignemnt 2

## Testing
- Tests simulate human interaction with our code.
- Write code to run our code.
- We need to figure out what data to use.

### Varietry of Inputs: 3 classifications
- General Cases (valid, expected inputs)
- Edge Cases 
- Memory leaks

#### General Cases for A Sort Function
- lists of length n (for any n > 1)
- Content of lists doesn't matter (as long as it's non-NULL)
- Expected output:
    - sequence is same size
    - is in order
    - same number of elements

#### General Cases for a Sort Function
- strange to be using it, but valid nontheless
    - a list of length 0
    - a list of length 1
    - n sorted numbers
    - n reverse sorted numbers
    - n identical numbers

### Activity - For substring function
- General test cases
    - word, 2, 3, gives rd
    - dog, 1, 1, gives o
    - Not invalid data
- Edge cases
    - Hello, 0, 5, expect entire thing
    - "", 0, 0, expect empty sting


Why not NULL?
    - I think because it would break the code, not valid input
        - no reasonable input to return.

### Manual testing
- Change the main function of your program to accept standard input
- Run the program
- Enter the nth test case, type it in like an animal
- check the output
- go back to 2 until done
- did it all work?
- Extremely Tedious

### Automated Testing
- We can write code to do tedious things
    - **test scaffolding**, we write it.
- Example for perfectlybalanced.c

#### Organising Tests
- Each test function should be as atomic as possible
    - Test ONE thing (and test it well)
- The data for the test belongs in the test function
    - create, populate and destroy stack for each test
- the main function should ONLY call other functions.

