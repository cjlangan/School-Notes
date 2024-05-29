#pragma once // alternative to #infdef + #define

#ifndef __STRINGS_H
#define __STRINGS_H

/**
 * This is the public interface for my
 * string type in C.
 */

// Declares a string type for use
// but does not expose how that
// string type is implemented:
typedef struct STRING string;
// typedef also means I can use
// string as a bareword to declare
// a variable:
//      string myString;

/**
 * Create an instance of a string structure.
 *
 * Args:
 *  characters: the characters to put into the string. Must be allocated with
 *              `num_chars` bytes.
 *  num_chars: the number of characters to copy. Must be >= 0.
 * Return: a **heap-allocated** instance of the string struct. **May return 
 *         `NULL` if memory cannot be allocated on the heap.
 */
string *make_string(char *characters, int num_chars);

/**
 * Destroy an instance of a string.
 *
 * Args:
 *  s: this string to destroy. Must not be NULL, must be a valid string.
 */
void destroy_string(string *s);

/**
 * Return the character at the specified index.
 *
 * Args:
 *  s:      the string to get the character from. Must not be NULL. Must a
 *          valid string. The contents of s will not be changed.
 *  index:  the index of the character. Must be >= 0,
 *                                      must be < string length.
 * Return: the character at that index, or the NULL byte if invalid index.
 */
char char_at(const string *s, int index);

#endif
