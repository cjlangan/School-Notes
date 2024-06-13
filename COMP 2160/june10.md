## Notes:
- Test suites are up.
- we still write our own.
- he runs with DNDEBUG to test our defensive programming.
- tests our destroy zone with valgrind, shows his valgrind output.
    - not in test cases separately, just must be no leaks.
- dump function will have to be tested, just look at what he put.
    - format doesnt have to be identical, just show proper content.
- don't use asserts in tests.
- best practices
- `diff` to check difference between files

## His Test Suites
- 5 tests
- must put our zones.c into each
- use `ln`
    - makes links between files
    - use soft links
    `ln -s ../zones.c`
        - make link to this file within this directory.
- curses library leaks memory
    - all in libncurses, this is how it should be. None in zones.o

## Today
- given an existing solution, gives algortithms data structurs and techniques, such as caches and tables to provide better optimisation
- describe benefits of modularity, coupling, cohesion, measurments of them.

## Optimising for Space
bad when:

1. Sparse data sets (lots of unused space) // partially filled arrays
2. High volume of data

### High volumes of data : Video
- imagine a 4k (3820x2160) video at 60fps
- each pixel takes 3 bytes (red, blue, green)
- 1.38 gigabytes per second of data.
- most SSD's cannot keep up with this.
    - watching videos online would be very stuttery

## Compression
- To save space.
- analyze the data to find redundant data
- Two types: lossless and lossy

### Types of Compression
**Lossless**
- reduce size of input without losing any info from input
- able to reproduce the input perfectly after decompression
- ex: zip and unzip.

**Lossy**
- Reduce size of input by discarding information
- usually unimportant data
- ex: things we humans cant see nor hear.
- able to reproduce and approximation of the input after decompression.


### Doing strip of papaer:


## Compression
- can involve tough math, coding theory

## Not Compression
- compression is out of scope for this course
- we have to change how we represent out data
- use a data structure that only uses the space that it needs
    - linked list is better than partially filled array.
    - matrices -> sparce matrix is better (a list of lists)

### why Search code is slow, (given code)
- cuz uses linked list, not hash table.


- useful `time` command, tells how long whole program took.

## Maximising Space Usage
- changing data structure should always be the first approach
- squeezing out last few bits ?

## Manipulating Bits
- **all values** are ultimately represented in memory as bits
