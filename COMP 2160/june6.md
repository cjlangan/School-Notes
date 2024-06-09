## Term Test:
- popping off stack frame just leaves the values in it the same.

## Assignment 3:
- if have zone with bytes, if someone tries to copy thousand characters past zone
    - can't do anything about it.
- zone_size function just return zone size
- struct can have more data
- our invariant will be static, invariant for node as well.
- first fit in a separate function, I'll have to change that.
- must functions are static.
- linked list doesn't have to be in different files. So don't do.

isntalled kcachegrind

## Notes:
- identify where problem is in code, offer tehniques and improvements.

## Profiling
- Have code that works, but slowly

### Spelunking
- Read the code.
- mentally execute, and manually with paper
- identify spots doin more work that necessary

### Printf
- to see where it starts slowing down
- better understand the flow fo the application

### What if it is not observantly slow.
- Profilers

## Profilers
- tools to help identify parts of code that are slow
- There are many different profilers
- we will look at gprof and valgrind/kcachegrind

### gprof
Three Steps:
1. Compile your code with the -pg flag
2. Run your code like normal
    - code added to executable is instrumentation code;
    - checks function time length
    - creates gmon.out
3. gprof `< prog name >`

pass -X flag when entering aviary
- want to be able to run GUI programs on virtual, but see on local

### valgrind
1. compile code normally with -g flag, or -gdwarf-4 if on aviary
2. Run code with valgrind, specify tool

`valgrind --tool=callgrind ./mycode`

3. use kcachegrind to open new file


## you should
- be able to use a profiler to see info about your program
