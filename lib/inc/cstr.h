#ifndef CUTILS_CSTR_H_
#define CUTILS_CSTR_H_

#include <stdbool.h>
#include <stddef.h>
#include <sys/types.h>

char *strtrim (char str[static 1]); /* trim whitespace of a cstring (both beginning and end) */
char *strtriml (char str[static 1]); /* trim whitespace of a cstring on the left (beginning of string) */
size_t strtrimr (char str[static 1]); /* trim whitespace of a cstring on the right (end of string) */
size_t strcount (const char str[static 1], char c); /* count number of occurances of a character within a string */
void strdowncase (char str[static 1]); /* transform all uppercase letters of a string into lowercase letters */
void strupcase (char str[static 1]); /* transform all lowercase letters of a string into uppercase letters */
bool strisblank (const char str[static 1]); /* check if a string only consists of whitespace characters */

#endif // CUTILS_CSTR_H_
