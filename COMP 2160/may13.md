## Good Practices

Note:  char * == char[]

- always declare variables at top of functions
- buffer means array
- pass length of arrays to functions
- cannot return array from a function, so pass an array we will be modifying effectively
- 

## Line-based Input
- getchar() --> get single char
- fgets() --> string line


```c
char *fgets(char *s, int size, FILE *stream);
```
