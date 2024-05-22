## Design by Contract
- a tool to prevent programming errors
    - not language specific
    - not a tool for preventing user errors
- This is code you write that encodes your assumptions about the inputs, outputs, and stats of your program

### Programming Errors
- Syntax errors (handled by the compuler)
- Forget to check inputs (types of data, NULL)
- Index and bounds errors

### DBC: Exception Prevention
- Remember: C does not have exceptions
    - Generally: DBC is intended to prevent exceptional behaviour during development

### What is an Exception?
- Something happens while your program is running where it can't (or shouldn't) proceed
    - a null pointer exception
    - File-related issues (ex: file not found)
    - Division by 0
    - Index/bounds errors

### Preventing Exceptions
- Exceptions come froma  violations of our assumptions ..usually.
- Three places out assumptions can be violated:
    - Before we start processing data,
    - After we finish processing data,
    - The state of an object throughout execution.

### Assumptions

`string *make_string(char characters[], int num_chars);`

#### Input Assumptions
- num_chars is greater than or equal to zero
- characters is not NULL (can characters equal NULL?) (yes it can!)
- characters is a valid C string with a \0 at cahracters[num_chars];

#### Output Assumptions
- We are returninga "valid" struct STRING
    - the contents are equal to characters
    - A \0 is in the right place
    - the length is >= 0

`char char_at(string myString, int index);`

#### Input Assumptions
- index is >=0
- index is less than the length of the string
- myString as a "valid" struct STRING

#### Output Assumptions
- The character we return is actually in the string, OR
- We are returning a \0 because tinput assumptions were violated
- The string we originally had has not been modified

```c
#define LINE_LENGTH 80

//..
char string[LINE_LENGTH] = "Hello, world!";
for(int i = 0; i < LINE_LENGTH; i++)
{
    printf("[%c] ", string[i]);
}
```
- Give unexpected output, since LINE_LENGTH is passed actual string length

### Assumptions
- we may have implicit assumptions about the state of inputs
    - "Of course that's true"
        - still, must be **explicitly stated**


## Implementing Design by Contract
- Now that we have defined our assumption, we need to code them
- can be implemented using the assert statement

### assert-ions

from `#include <assert.h>`
- test fro thruthiness
- execution halts if false, continues if true

```c
int value = 10;
assert(value > 100);
```

### Preconditions
- One or more well-defined conditions that must be met befroe execution
- check that inputs to a function/block meet certain conditions

#### Example: In strings.c
```c
#ifndef NDEBUG
    char copy_of_string[MAX_STRING_LENGTH] = {0};
    int original_length = string.length;
    strncpy(copy_of_string, string.characters, original_length);
#endif
```

### Postconditions
- One or more well-defined conditions that must be met after execution
- May be similar to the lsit of preconditions, but will be about output
- ensure block outputs meets certain conditions

#### Example in strings.c
```c
#ifndef NDEBUG
    assert(original_length == string.length);
    assert(strncmp(copy_of_string, string.characters, original_length) == 0);
#endif
```

### Invariants
- we are focussing on class or type invariants
- verify that an object or data meets certain conditions during execution (state)
    - specifically: obeject properties
- Usually implemented as a function
    - Often called in pre and post conditions

#### Example in strings.c
```c
// invariant for checking if condtions of function are met while it's running, (state)
void check_string(string *s)
{
    // a valid string has a length that is >= 0 and is < MAX_STRING_LENGTH
    // also, has a null byte at the length of the string
    // also, has length == number of characters counted before the null bytes
    
    assert(s != NULL);
    assert(s->length >= 0 && s->length < MAX_STRING_LENGTH);
    assert(s->characters[s->length] == '\0');

    // exercise: implement checking if the number of characters before the null byte
    // is equal to length. Use ifndef and NDEBUG

#ifndef NDEBUG
    int size = 0;
    while(s->characters[size] != '\0')
    {
        size++;
    }
    assert(size == s->length);
#endif
}
```
- then use check_string at end of functions for example.
