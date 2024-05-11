# Using Aviary via SSH

## Commands
- **ls -l**
    - this shows permissions and access, and metadata, of all files
- **pwd**
    - shows the present working directory
- **touch**
    - type name after to create a file
- **cp charizard comp2160/blastoise**
    - copies file into a directory, and changes its name
    - use -r recursively for all files in a directory
- **mv**
    - to move or rename files
- **rm**
    - remove, -r for directories but will ask for each file.  -f also to force.
- **cat > filename**
    - concatonates, ctrl+c or ctrl+d, writes text to file.
- **more**  or **less**
    - pagers, less is more, prints contents, use arrows key to move, q to quit
- **man**
    - look at manual of a command
    - / to search for something, n to go to next found item
    - g to go to the top
    - find [-H] [-D] [expression] --> changes behaviour of command, flags
        - expression is typically a file or a folder
- **tree**
    - shows directory files structure


## Special Places
- **.**
    - current directory
- **..**
- **home** / **~**
- **-**
    - back to previous folder we were in

## Text Editors
- use vim. 

```c
  8 #include <stdio.h>
  7 #include <stdlib.h>
  6 
  5 // int is number of arguments, char* is array of strings
  4 int main(int argc, char* argv[]) {
  3         printf("Hello, world!\n");
  2 
  1         return EXIT_SUCCESS;
  0 }

```

## Compiling a C program
clang -Wall file.c -o file
    - -Wall will show us warnings

## Sending a Directory to Aviary
scp -r directory langanc@aviary.cs.umanitoba.ca:
    - colon is important
    - transfers directory to aviary
