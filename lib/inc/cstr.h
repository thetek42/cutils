#ifndef CUTILS_CSTR_H_
#define CUTILS_CSTR_H_

#include <stddef.h>
#include <sys/types.h>

char *strtrim (char *str); /* trim whitespace of a cstring (both beginning and end) */
char *strtriml (char *str); /* trim whitespace of a cstring on the left (beginning of string). */
ssize_t strtrimr (char *str); /* trim whitespace of a cstring on the right (end of string) */
ssize_t strcount (const char *str, char c);
void strdowncase (char *str);
void strupcase (char *str);

#endif // CUTILS_CSTR_H_
