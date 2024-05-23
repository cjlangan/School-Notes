// #pragma once //alternative to #infndef + #define

#ifndef __STRINGS_H
#define __STRINGS_H

/**
 * This is the public interface for my string type in C.
 */

// Declares a string type for use but does not expose implementation
typedef struct STRING string;
// typedef alse means I can use string as a bareword to declare a variable:
//        string myString;

string *make_string(char characters[], int num_chars);

/**
 * Destroy an instance of a string
 *
 * Args:
 *  s: string to destroy. Must not be NULL, must be a valid string
 *
 */
void destroy_string(string *s);

/**
 * Return the character at a specified locations
 */
char char_at(string myString, int index);

#endif
