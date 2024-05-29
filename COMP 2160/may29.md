## Notes
- edge case: empty lists. size of empty list.
- peek empty list, pop empty list, empty and empty list
- destroy empty list, etc...

### Terminal Text Effects
- can pipe output ot this program if install it.

- won't have to write makefile on final exam
- test suites dont have programming practices.

## Test Harness
- NULL is not good test case becuase not valid input, like it cant be type in on keyboard


His test suit was like 200 lines long
- 4-5 funciton evaluating behaviour
- so he has 300-400 lines for his test cases in solution I think.
- we dont test if memory was freed.

valgrind ./main
- on aviary
- tests for memory leaks, shows errors

### Assignment
- invariant depends on implementation. Length for stack.
- length = 0 and no nodes
- length > 0 and has nodes
- dont have to test of nodes have integers.
- dont test invalid test cases, should be caught by invariant
- add size to stack struct
- says look at realloc, resize previous allocation, not necessary

## Build Tools
- making object files, says compile up to assembler, but no further
- what if have n files? Need to automate.
- building is same as compiling
- different languages heve different build tools
- java has 3 main ones: Ant, Maven, Gradle
- python: pip
- C: GNU make, CMake, Ninja
	- we look at GNU make
	- make automates figuring out what need to be recompiled when files change
	- build graph of dependencies

### Make
- Tell make dependencies in Makefile
- consists of rules

```
target: prereq1 prereq2
	cmd1 -o target
```

Each rule has 3 parts
- A target (name to generate)
- A list of prereqs
- A list of commands to make it

#### Let's Modify a Makefile


