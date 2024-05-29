COMP 2160 - Lecture 13 examples
===============================

This is further work on our string data type from lecture 12.

Compiling all code
------------------

A new thing has been added to this folder: a `Makefile`!

We'll talk about `make` in class, but it's a "build management tool", and it
helps take away the error-prone tedium of recompiling code that uses multiple
files and libraries.

You can compile all code samples in this directory by running the following
command on the command line:

    make

You can also remove all compiled outputs using the following command on the
command line:

    make clean

`strings.h`
-----------

`strings.h` is now a public interface to two implementations of a string, one
using an array (in `strings-array.c`) and one using a list (in
`strings-list.c`).

`strings-array.c`
-----------------

This code has not changed since lecture 12.

You cannot run this code on its own.

`strings-list.c`
----------------

This code has had some portions filled in to work with lists since lecture 12:

1. The `check_string` function (our invariant) now counts the number of nodes
   and confirms that the number of nodes in the list is the same as the length
   of the string.
2. There's a *giant* diagram comment in `make_string`. This is where we will be
   working today.
3. The `destroy_string` function now destroys the entire list. We'll look at
   this in class, but we won't write it.
4. The `char_at` function now uses lists (it does a linear search of nodes to
   find the node at the index).

You cannot run this code on its own.

`main.c`
--------

The main code has not changed, but our `Makefile` produces two runnable
programs:

1. One that uses the array-based string, and
2. One that uses the list-based string.

You can run each program on the command line with the following command:

    ./main-array
    ./main-list
