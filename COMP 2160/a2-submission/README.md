COMP 2160 assignment 2
======================

Name: Connor Langan
Student number: 7993941
E-mail address: <langanc@myumanitoba.ca>

Question 1
----------

This is an implementation of a stack ADT as a library, using a linked list.

You can compile this code by running the following commands:

   clang -Wall -c stack.c -o stack.o

You cannot run this code.

Question 2
----------

The code for this question has a test scaffold for the stack implemented in 
question 1. It tests general and edge cases for the stack.

### Part 1

This is the test suite itself. You can compile and run this code on the command
line by running the following commands:

   clang -Wall -c stack.c -o stack.o
   clang -Wall stack-test.c stack.o -o stack-test
   ./stack-test

### Part 2

In part 2 we are trying to figure out why Franklin is a bad programmer.

#### `stack1.o`

I think Franklin is a bad programmer for `stack1.o` because empty() always 
returns true. Even when the stack is populated.

#### `stack2.o`

I think Franklin is a fantastic programmer for `stack2.o` because it passed 
all tests in the test suite.

#### `stack3.o`

I think Franklin is a bad programmer for `stack3.o` because push() appears
to make a new node point to the head node, then make head point to the new node.
So the head node stays on top after pushing.

#### `stack4.o`

I think Franklin is a bad programmer for `stack4.o` because pop() appears to 
pop off two elements from the stack and returns the second value.

#### `stack5.o`

I think Franklin is a bad programmer for `stack5.o` because peek() modifies
the value it was peeking.

Question 3
----------

This is a program that implements bracket matching. You can compile and run this
code on the command line with the following commands:

   clang -Wall -c stack.c -o stack.o
   clang -Wall match.c stack.o -o match
   ./match

and then entering test cases in the following format:

   ((()())()) 2
   ^D

or by redirecting a file to standard input:

   ./match < brackets.txt

Bonus (Optional)
----------------

This is the bonus implementation for assignment 3. It prints the input with matching
brackets colour-coded with eachother. 

You can compile and run this code on the command line with the following commands:

   clang -Wall -c stack.c -o stack.o
   clang -Wall colour-match.c stack.o -o colour-match
   ./colour-match

and then entering test cases in the following format:

   ((()())()) 2
   ^D

or by redirecting a file to standard input:

   ./colour-match < brackets.txt
