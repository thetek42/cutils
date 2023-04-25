#ifndef CUTILS_STR_H_
#define CUTILS_STR_H_

#include "common.h"

/* represents a string, where length and capacity are stored alongside the string data. */
typedef struct {
    char *str; /* string data */
    usize len; /* string length */
    usize cap; /* capacity (allocated size) */
} str_t;

str_t str_new (void); /* initialize a str_t string. */
str_t str_new_cap (usize want_cap); /* initialize a str_t string with a given capacity. */
str_t str_new_from (const char src[static 1]); /* initialize a str_t string with a given data. */
str_t str_new_from_len (usize len, const char src[restrict len]); /* initialize a str_t string with a given data and length. */
str_t str_clone (const str_t orig[static 1]); /* clone the contents of a str_t string into a new str_t string. */
void str_free (str_t *str); /* free the contents of a str_t string. */
void str_append (str_t str[static 1], const char src[static 1]); /* append a string to the end of a str_t string. */
void str_append_len (str_t str[static 1], usize len, const char src[restrict len]); /* append a string to the end of a str_t string with a given length. */
int str_cmp (const str_t str[static 1], const char *s2); /* compare a str_t string with a cstring. */
bool str_eq (const str_t str[static 1], const char *s2); /* check if a str_t string equals a cstring. */
bool str_starts_with (const str_t str[static 1], const char find[static 1]); /* check if a str_t string starts with a cstring. */
bool str_starts_with_len (const str_t str[static 1], usize len, const char find[restrict len]); /* check if a str_t string starts with a cstring of given length. */
bool str_ends_with (const str_t str[static 1], const char find[static 1]); /* check if a str_t string ends with a cstring. */
bool str_ends_with_len (const str_t str[static 1], usize len, const char find[restrict len]); /* check if a str_t string ends with a cstring of given length. */
char *str_find (const str_t str[static 1], const char *find); /* find a substring in a str_t string as a pointer. */
isize str_pos (const str_t str[static 1], const char *find); /* find the index of a substring in a str_t string. */
bool str_is_blank (const str_t str[static 1]); /* check if a string only consists of whitespace characters. */
void str_downcase (str_t str[static 1]); /* transform all uppercase characters in a str_t string to lowercase */
void str_upcase (str_t str[static 1]); /* transform all lowercase characters in a str_t string to uppercase */
void str_resize (str_t str[static 1], usize cap); /* resize the allocated data of a str_t string. */

#endif // CUTILS_STR_H_
