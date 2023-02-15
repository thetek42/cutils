#ifndef CUTILS_STR_H_
#define CUTILS_STR_H_

#include <stdbool.h>
#include <stddef.h>
#include <sys/types.h>

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
bool str_starts_with (const str_t *str, const char *find); /* check if a str_t string starts with a cstring. */
bool str_starts_with_len (const str_t *str, const char *find, size_t len); /* check if a str_t string starts with a cstring of given length. */
bool str_ends_with (const str_t *str, const char *find); /* check if a str_t string ends with a cstring. */
bool str_ends_with_len (const str_t *str, const char *find, size_t len); /* check if a str_t string ends with a cstring of given length. */
char *str_find (const str_t *str, const char *find); /* find a substring in a str_t string as a pointer. */
ssize_t str_pos (const str_t *str, const char *find); /* find the index of a substring in a str_t string. */
bool str_is_blank (const str_t *str); /* check if a string only consists of whitespace characters. */
void str_downcase (str_t *str); /* transform all uppercase characters in a str_t string to lowercase */
void str_upcase (str_t *str); /* transform all lowercase characters in a str_t string to uppercase */

#endif // CUTILS_STR_H_
