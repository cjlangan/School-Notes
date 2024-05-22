## Questions for Assignment 1
- Which magic character do i need to #define, which do I not?
    - e.g: (, ), t, f, space, \0, \n
    - colours, t, f, for NULL char use null, space, 
- Should the colours be defined right before they are used, or is this a case where I can leave them defined at the top?
- Is it good practice to have my function return the length and then also set the input array at the same time?
    - depends, in my case it is probably fine.
- Maybe think of simple implementation using getchar()

## fgets()
name:   F, r, a, n, k, l, i, n, \n, \0    .. .. 50
    - newline from me pressing enter
    - NULL character is inserted by fgets()

fgets reads untill newline, so may have unwanted newline char
- solution, replace it with a null byte

```c
#define NAME_LENGTH 50
    char name[NAME_LENGTH];

    while(fgets(name, NAME_LENGTH, stdin) != NULL)
    {
        // This replaces the newline at the end of the string
        name[strlen(name) - 1] = '\0';

        printf("Your name is: %s!!!!!!!!!!\n", name);
        printf("8th character is: %c\n", name[7]);
    }
```

fgets is a blocking operation, take block by block of string
- solution, just know how many character you will be reading in.

## Memory Layout
F, r, a, n, k, l, i, n, \n, \0    .. .. 50

0, 1, 2, 3, 4, 5, 6, 7 ....
- this isn't perfect

### Memory Layout (For a process, or From the OS)
- draws in vertical shape
- Whole thing is called a Address Space
    - is hexadecimal (base 16)

numbers | sections | whats there | address 
-|-|-|- 
0 | code | int main(void){} | 0x0000
1 | Heap | 
2 | sd | 
ffff | Stack | | 0xffff

- The address space for each block it filled with individual locations where each has an address, each is effectivel one element in an array

- So far we have been exclusively using runtime stack and code section
- Heap is just another region of memory we can use

## Three main parts to memory
- The Code section
- The Heap section
- The Stack section

## The Stack

![](Images/stack.png)

## Returning an Array
- an array in C is just an address
- location is where memory starts
- We need a new type: **pointer**

## Pointers
- a type that's value is an address
- declared with modifiers (*) on primitive types        *

```c
int *val;
char *val;
float *val;
```
- can return pointers, which have addresses stored in them.
















