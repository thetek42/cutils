#ifndef CUTILS_CSTR_H_
#define CUTILS_CSTR_H_

#include <stddef.h>

char *strtrim (char *str); /* trim whitespace of a cstring (both beginning and end) */
char *strtriml (const char *str); /* trim whitespace of a cstring on the left (beginning of string). */
size_t strtrimr (char *str); /* trim whitespace of a cstring on the right (end of string) */

#endif // CUTILS_CSTR_H_
