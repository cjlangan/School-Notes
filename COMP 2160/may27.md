## Implementation of ADT with Private Data Structure
- pre conditions, post conditions, invariants
- a linked lsit data structure
- general case and edge case test data for an ADT

*Work on strings.c*

### Resource Management
- must free().

### const
- like final in Java, cant change contens

`char char_at(const string* s, int index)`

## Linked List
- Will not be modifying the header file
- just modify strings.c


#### Differences between dot and arrow
- use dot (.) when using stack allocated structures
- use arrow (->) when using heap allocated structures (pointer)
	- shorthand for:
	- `*(curr).next;`


## Assignment 2
- Identify THE matching bracket.
- use given header file to implement interface.
- preconditions are generally stated, maybe add more?
- can have additional functions inimplementation, but no changing header file.

```c
int value;
//make the stack, push stuff, sue the stack
bool peeked = peek(s, &value);
printf("The value peeked is %d\n", value);

// inside peek fnction, to set the value in *value:
//dereference the pointer:
*value = 10; //for example, but likely top of stack.
// * is dereferencing, "value at"
```

### Part two of Assignment
- testing the stack, 
- given stacks, test your against compiled ones, our code should find what is wring with given code.
- one is correct, other 4 are wrong, use test suite to identify problem in each

### Part three
- implement algorithm to find matching bracket and print it


- use dynamic sizing, graders just use test files we have access to.
- last instance of space as the SEPARATION character
- BONUS, coloured bracket matching.
- linked list of integers
- psuh 1, push 2, psuh 3, pop, push 4, pop, pop, push 5
