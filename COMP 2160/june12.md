## Notes:
- Use function pointers to paramaterise behaviours


## "Classes" in C

## Inheritence in C
- Classes are not apart of the language
- Can we simulate this behaviour, kind of
- Need some new tools:

### Union
- a tool that can simulate polymorphism
- looks a lot like a struct

```c
union THING
{
    double x;
    int y;
};
typedep union THING thing;
```

- ONly one property can be used at a time
- sizeof() a union is the sizeof it's widest type
- has space for one thing OR the other.
- size of a struction is the sum of components.

## Polymorphism in C
- When call parent class it will figure out what to do
- Kind of awkward with unions.

### Working on shapes.c 


## Fucntion Pointers
**Pointer**
- a variable who's value is an address

Now:
- Your *code* exists in memory at an address (recall that its at the top)
    - so we can point at code
- A funciton pointer is avaribale

### Declaring Function Pointers

```c
char func1(char c); //from this function

char (*pointerFun1)(char c); // to this fucntion pointer
```

```c
char func2(char *c); //from this function

char *(*pointerFun2)(char *c); // to this fucntion pointer
```

### Initialising a function pointer

```c
pointerFun1 = func1;
pointerFun2 = func2;
```

- without parenthesis

### Invoking Function Pointers

```c
char x = pointerFun1('C');
char *y = pointerFun2("Hello");
```

#### *Adding more to shapes*

// END OF THE COURSE YAYYYY. EXTRA NOW. >>

## How to even start - Gameboy Program
- GPAdev.net has extensive documentation about the gameboy.
- already know how to program, like in C
- Learn about the hardware and its idioms.
- Set up your development environment, what he wants us to do.

### Caveat
- GBA games not typically written in C, were writtne in ARM7 assembly
- We will approach without a library to help. But there are libraries. ex: libgba

### GBA
- Released 2001
- 2 processors
    - ARM7 processor at 16.8MHz
    - Zilog processor at 8.2MHz, why? For game boy games
- 32kb ram (on CPU), 96kb vram (video), 256kb dram (off CPU)
- Games have up to 32mb ROM, memory on cartridges, can only read.
- 240x160 pixel display 

## GBA IDIOMS
- I/O memory mapped
    - work with ahrdware by reading and writing know memory locations
- You can work with bitmaps (and we will)
    - but you shouldn't... (use tiles and sprites instead)
- You need to know about interleaving display processin, inptit, blah blah
- be aware of where in memory your data is going
    - on CPU is faster

## Writing a Simple program
- cool

## Notes
- EVERYTHING FUCNTION POINTERS.

For gameboy game:
- check makefile
- need docker and mgba emulator
- then run:

```bash
mgba-qt main.gba
```


