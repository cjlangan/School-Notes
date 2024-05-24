/**
 * This is the public interface for my string type in C.
 */

// Declares a string type for use but does not expose implementation
typedef struct STRING string;
// typedef alse means I can use string as a bareword to declare a variable:
//        string myString;

string *make_string(char characters[], int num_chars);

char char_at(string myString, int index);


