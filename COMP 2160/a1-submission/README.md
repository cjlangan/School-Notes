# COMP 2160 Assignment 1
- **Name:** Connor Langan
- **Student Number:** 7993941
- **E-mail address:** langanc@myumanitoba.ca

## Question 1
- This is a direct translation of a Java program called `PerfectlyBalanced.java`.
- You can compile and run this program by running the following commands:

```bash
clang -Wall perfectlybalanced.c -o perfectlybalanced
./perfectlybalanced
```

## Question 2
- This is a modified verison of the direct translation in question 1 that allows entering test cases on standard input.
- You can compile and run this program by running the following commands:

```bash
clang -Wall perfectlybalanced-input.c -o perfectlybalanced-input
./perfectlybalanced-input
```

- and then entering test cases in the following format:

```bash
(()())) f
(()) t
^D
```

- or by redirecting a file to standard input:

```bash
./perfectlybalanced-input < balanced-cases.txt
```
