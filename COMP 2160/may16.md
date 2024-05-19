## Differentiating Java and C
- Java has exception, bounds checking, and can close streams
- Cannot mess up going out of bounds of the stack in java, because array are not in the stack in Java, they are on the heap.

## Compiling
- javac and python have several compilation stages
    - but we don't care how they work
- clang has 4 stages to compilation
    1. Preprocessor
    2. Code Generator
    3. Assembler
    4. Linker
    - ... and we need to know a bit about how it works

### Preprocessor
- Is a text replacement engine
    - Finds lines that start with #
    - Replaces those lines with file contents (#include)
    - Uses those lines to replace other text in the files (#define)
- You can run just the preporcessor with `clang -E`

### Code Generator
- Takes output from preprocessor
- Bulds an **abstract syntax tree (AST)** and optimizes the tree
- Translates AST to **assembly** (Processor-specific instructions)
    - Still text based, but can be directly translated to binary
- Can run with `clang -S`

### Assembler
- Takes output from code generator
- Translates assembly to an "object file" (binary/machine code)
- Object files can't be executed yet! (just declared, funciton signature)
- Can run preprocessor, code generator, and assembler with `clang -C`

### Linker
- Takes output from assembler (the object file)
    - Links the object file with function **implementations**
    - Implementations are platform/OS-specific
- Produces an executable file
- use just `clang`

# Objects in C!

## Objects in java
- Primitives, 
- Strings are like primitives, but different
- Arrays
- Parallel arrays  (2D)
- Classes! Objects!

## Struct
- A named grouping of related, heterogeneous data
- like a class, but no behaviour, no methods

```c
// 1.2345 x 10 ^ 2
struct SCIENTIFIC_NOTATION
{
    int exponent;
    float mantissa;
};
```
- need semicolon

## Privacy?
- get? set?
    - C does not have methods on struct
- public, private, protected?
    - C has no concept of information hiding for struct
    - Everything is effectively public

## Strings
- Lets build our own data type, the String type.

1. Define the string struct
2. Write a main method that populates it
3. Write some functions to replicate String from Java


