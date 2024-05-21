## Structs
- they are objects, chunk of allocated memory with names parts
- when returning a struct instance from a funciton, the contents are copied to where it was called from.

## Modular Design
- Programs get very big
    - difficult to understand
    - difiicult fro multiple people to work on

#### Goals:
- smaller, easier to understand components
- Ability fro multiple people to work together
- Extract reusable structures and concepts

### Libraries
- e.g. System library in java, has class `out`

### 2 Parts
1. The **interface** of your idea
2. The **implementation** of your idea

#### Main Goal:
- Separate these two things into different parts

### Interfaces
- only public function signaturs/prototypes
- Data type declarations only, no defining

```c
// no implementation details, just a name.
typedef struct STRING string;
```

The **minimal** set of information you need to know to use this thing.

### Implementation
1. Function implementations (public and provate)
2. Data type definitions


#### Where to start?
Two concepts
1. Functional decomposition - conceptually
2. implementations - physically

### Funtional Decomposition
- Identify your data model
- Identify any invariants
- Identify how the data is input, modified, and output

#### Data model
- What are you being asked to represent?
- What data types best represent that?
Should I build compound data types?

#### Functions
- What input do I have, 
- How do I get the input
- How to transform it

## Implementing the Interface

### Preparing
Use a header file (.h)

Contains:
- Function prototypes (declarations)
- struct declarations (as necessary)

Does not expose any internal implementation details

### Implementing the implementation
Your .c files will implement the prototypes

- use the #include preprocessor directive
- Function definitions
- INternal implementation details

```bash
clang -Wall strings.c -c -o strings.o
clang -Wall main.c string.o -o main.c
``````

strings.o is object file, has function definitions
- use -> operator
- dont need struct STRING

strings.h has the typedef declaration of STRING string

```c
// Declares a string type for use but does not expose implementation
typedef struct STRING string;
// typedef alse means I can use string as a bareword to declare a variable:
//        string myString;

string *make_string(char characters[], int num_chars);

char char_at(string myString, int index);
```

main.c has the actual usage of them

```c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Double quotes mean look in this directory fo the header file
#include "strings.h"

int main(int argc, char **argv)
{
    string *myString;

    myString = make_string("Franklin", 8);

    return EXIT_SUCCESS;
}
```
