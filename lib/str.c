#include "str.h"
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"

#define STR_MIN_ALLOC 64 /* minimum allocation size for string data */

/**
 * initialize a str_t string and allocte some memory for the data
 *
 * @param   str: a pointer to the string to initialize
 */
void
str_new (str_t *str)
{
    str->str = smalloc (STR_MIN_ALLOC * sizeof (char));
    str->str[0] = '\0';
    str->len = 0;
    str->cap = STR_MIN_ALLOC;
}

/**
 * initialize a str_t string with a given capacity (allocation size). can be
 * used in oder to reduce the amount of calls to realloc.
 *
 * @param   str: a pointer to the string to initialize
 */
void
str_new_cap (str_t *str, size_t want_cap)
{
    size_t cap;

    cap = max (next_pow_of_two (want_cap), STR_MIN_ALLOC);
    str->str = smalloc (cap);
    str->str[0] = '\0';
    str->len = 0;
    str->cap = cap;
}

/**
 * initialize a str_t string with a given data. the data will be copied into
 * the string.
 *
 * @param   str: a pointer to the string to initialize
 * @param   src: the data to put into the string
 */
inline void
str_new_from (str_t *str, const char *src)
{
    return str_new_from_len (str, src, strlen (src));
}

/**
 * initialize a str_t string with a given data. the data will be copied into
 * the string. the length of the data is provided as a parameter.
 *
 * @param   str: a pointer to the string to initialize
 * @param   src: the data to put into the string
 * @param   len: the length of `src`. undefined behaviour occurs if `len !=
 *               strlen (src)`
 */
void
str_new_from_len (str_t *str, const char *src, size_t len)
{
    size_t cap;

    cap = max (next_pow_of_two (len + 1), STR_MIN_ALLOC);
    str->str = smalloc (cap * sizeof (char));
    str->len = len;
    str->cap = cap;
    strncpy (str->str, src, len);
    str->str[len] = '\0';
}

/**
 * free the contents of a str_t string.
 *
 * @param   str: a pointer to the string to free
 */
inline void
str_free (str_t *str)
{
    if (str)
        free (str->str);
}

/**
 * append a string to the end of a str_t string.
 *
 * @param   str: the str_t string to append to
 * @param   src: the cstring to append
 */
inline void
str_append (str_t *str, const char *src)
{
    str_append_len (str, src, strlen (src));
}

/**
 * append a string to the end of a str_t string. the length of the appended
 * string is provided as a parameter.
 *
 * @param   str: the str_t string to append to
 * @param   src: the cstring to append
 * @param   len: the length of `src`. undefined behaviour occurs if `len !=
 *               strlen (src)`
 */
void
str_append_len (str_t *str, const char *src, size_t len)
{
    size_t cap;

    cap = max (next_pow_of_two (str->len + len + 1), STR_MIN_ALLOC);
    if (cap > str->cap)
    {
        str->str = srealloc (str->str, cap * sizeof (char));
        str->cap = cap;
    }
    strncpy (str->str + str->len, src, len);
    str->len += len;
    str->str[str->len] = '\0';
}

/**
 * compare a str_t string with a cstring.
 *
 * @param   str: the str_t string to compare
 * @param   s2: the cstring to compare
 *
 * @return  integer less than, equal to, or greater than zero if str is found
 *          to be less than, to match, or to be greater than s2
 */
int
str_cmp (const str_t *str, const char *s2)
{
    return strcmp (str->str, s2);
}

/**
 * check if a str_t string equals a cstring.
 *
 * @param   str: the str_t string to compare
 * @param   s2: the cstring to compare
 *
 * @return  true if str equals s2, else false
 */
inline bool
str_eq (const str_t *str, const char *s2)
{
    return str_cmp (str, s2) == 0;
}
