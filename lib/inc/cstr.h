#ifndef CUTILS_CSTR_H_
#define CUTILS_CSTR_H_

#include <stddef.h>
#include <sys/types.h>

char *strtrim (char *str); /* trim whitespace of a cstring (both beginning and end) */
char *strtriml (char *str); /* trim whitespace of a cstring on the left (beginning of string) */
ssize_t strtrimr (char *str); /* trim whitespace of a cstring on the right (end of string) */
ssize_t strcount (const char *str, char c); /* count number of occurances of a character within a string */
void strdowncase (char *str); /* transform all uppercase letters of a string into lowercase letters */
void strupcase (char *str); /* transform all lowercase letters of a string into uppercase letters */

#endif // CUTILS_CSTR_H_
