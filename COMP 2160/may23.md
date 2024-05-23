# DBC Reveiw
- Explicitly stating and enforcing assumptions about inputs, outputs, and state
- use assert(), and comment in plain english
- all for programmers and internal state, not for the end user.
- #ifndef NDEBUG only for non assert statements. 
    - is during text replacement
    - clang -DNDEBUG strings.c -o strings
        - to compile with assertions turned off.


## Work on String Data Type
- gonna do:
    - Header guards in our interface
    - Resource management with dynamic memory allocation
    - Add more behaviour!
    - Add and enforce DBC and defensive programming
    - Explore const
    - Replace arrays with linked lists

## Header Guards
- preprocessor directives to prevent repeated function prototypes and type declarations in main.c or anything #including it
- so, at top of strings.h:

```c
#ifndef __STRINGS_H
#define __STRINGS_H

// code

#endif
```

## Resource Management
- For every Malloc, there must be a free
- We malloc in our "constructor", so we must add a free in a "destructor"
- `free(s)` where s is the object?
