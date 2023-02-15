#ifndef CUTILS_STR_H_
#define CUTILS_STR_H_

#include <stdbool.h>
#include <stddef.h>

/* represents a string, where length and capacity are stored alongside the string data. */
typedef struct
{
    char *str; /* string data */
    size_t len; /* string length */
    size_t cap; /* capacity (allocated size) */
} str_t;

void str_new (str_t *str); /* initialize a str_t string. */
void str_new_cap (str_t *str, size_t want_cap); /* initialize a str_t string with a given capacity. */
void str_new_from (str_t *str, const char *src); /* initialize a str_t string with a given data. */
void str_new_from_len (str_t *str, const char *src, size_t len); /* initialize a str_t string with a given data and length. */
void str_free (str_t *str); /* free the contents of a str_t string. */
void str_append (str_t *str, const char *src); /* append a string to the end of a str_t string. */
void str_append_len (str_t *str, const char *src, size_t len); /* append a string to the end of a str_t string with a given length. */
int str_cmp (const str_t *str, const char *s2); /* compare a str_t string with a cstring. */
bool str_eq (const str_t *str, const char *s2); /* check if a str_t string equals a cstring. */

#endif // CUTILS_STR_H_
