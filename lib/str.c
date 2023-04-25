#include "str.h"
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "cstr.h"

#define STR_MIN_ALLOC 64 /* minimum allocation size for string data */

/**
 * initialize a str_t string and allocte some memory for the data
 *
 * @return  a new, empty str_t instance
 */
str_t
str_new (void)
{
    str_t str;

    str.str = smalloc (STR_MIN_ALLOC * sizeof (char));
    str.str[0] = '\0';
    str.len = 0;
    str.cap = STR_MIN_ALLOC;

    return str;
}

/**
 * initialize a str_t string with a given capacity (allocation size). can be
 * used in oder to reduce the amount of calls to `realloc()`.
 *
 * @param   want_cap: the minimum wanted capacity
 *
 * @return  a new, empty str_t instance with given capacity.
 */
str_t
str_new_cap (size_t want_cap)
{
    size_t cap;
    str_t str;

    cap = max (next_pow_of_two (want_cap), STR_MIN_ALLOC);
    str.str = smalloc (cap);
    str.str[0] = '\0';
    str.len = 0;
    str.cap = cap;

    return str;
}

/**
 * initialize a str_t string with a given data. the data will be copied into
 * the string.
 *
 * @param   src: the data to put into the string
 *
 * @return  a new, empty str_t with given data.
 */
inline str_t
str_new_from (const char src[static 1])
{
    return str_new_from_len (strlen (src), src);
}

/**
 * initialize a str_t string with a given data. the data will be copied into
 * the string. the length of the data is provided as a parameter.
 *
 * @param   src: the data to put into the string
 * @param   len: the length of `src`. undefined behaviour occurs if `len !=
 *               strlen (src)`
 *
 * @return  a new, empty str_t with given data.
 */
str_t
str_new_from_len (size_t len, const char src[restrict len])
{
    size_t cap;
    str_t str;

    cap = max (next_pow_of_two (len + 1), STR_MIN_ALLOC);
    str.str = smalloc (cap * sizeof (char));
    str.len = len;
    str.cap = cap;
    strncpy (str.str, src, len);
    str.str[len] = '\0';

    return str;
}

/**
 * clone the contents of a str_t string into a new str_t string.
 *
 * @param   orig: the original str_t string
 *
 * @return  a new str_t instance with the same data as `str`
 */
inline str_t
str_clone (const str_t orig[static 1])
{
    return str_new_from_len (orig->len, orig->str);
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
str_append (str_t str[static 1], const char src[static 1])
{
    str_append_len (str, strlen (src), src);
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
str_append_len (str_t str[static 1], size_t len, const char src[restrict len])
{
    str_resize (str, str->len + len + 1);
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
inline int
str_cmp (const str_t str[static 1], const char *s2)
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
str_eq (const str_t str[static 1], const char *s2)
{
    return str_cmp (str, s2) == 0;
}

/**
 * check if a str_t string starts with a cstring.
 *
 * @param   str: the str_t string to search in
 * @param   find: the cstring to search for
 *
 * @return  true if `str` starts with `find`, else false
 */
inline bool
str_starts_with (const str_t str[static 1], const char find[static 1])
{
    return str_starts_with_len (str, strlen (find), find);
}

/**
 * check if a str_t string starts with a cstring of given length.
 *
 * @param   str: the str_t string to search in
 * @param   find: the cstring to search for
 * @param   len: the length of `find`. undefined behaviour occurs if `len !=
 *               strlen (src)`
 *
 * @return  true if `str` starts with `find`, else false
 */
inline bool
str_starts_with_len (const str_t str[static 1], size_t len,
                     const char find[restrict len])
{
    return strncmp (str->str, find, len) == 0;
}

/**
 * check if a str_t string ends with a cstring.
 *
 * @param   str: the str_t string to search in
 * @param   find: the cstring to search for
 *
 * @return  true if `str` ends with `find`, else false
 */
inline bool
str_ends_with (const str_t str[static 1], const char find[static 1])
{
    return str_ends_with_len (str, strlen (find), find);
}

/**
 * check if a str_t string ends with a cstring of given length.
 *
 * @param   str: the str_t string to search in
 * @param   find: the cstring to search for
 * @param   len: the length of `find`. undefined behaviour occurs if `len !=
 *               strlen (src)`
 *
 * @return  true if `str` ends with `find`, else false
 */
inline bool
str_ends_with_len (const str_t str[static 1], size_t len,
                   const char find[restrict len])
{
    return strcmp (str->str + str->len - len, find) == 0;
}

/**
 * find a substring in a str_t string. a pointer to the beginning of the
 * substring is returned.
 *
 * @param   str: the str_t string to search in
 * @param   find: the cstring to search for
 *
 * @return  beginning of found substring as pointer, or NULL if not found
 */
inline char *
str_find (const str_t str[static 1], const char *find)
{
    return strstr (str->str, find);
}

/**
 * find a substring in a str_t string. the starting index of the substring is
 * returned.
 *
 * @param   str: the str_t string to search in
 * @param   find: the cstring to search for
 *
 * @return  beginning of found substring as string index, or -1 if not found
 */
ssize_t
str_pos (const str_t str[static 1], const char *find)
{
    char *pos;

    pos = str_find (str, find);
    if (pos)
        return pos - str->str;
    return -1;
}

/**
 * check if a string only consists of whitespace characters. whitespaces
 * include the following characters: ' ', '\n', '\r', '\t', '\v', '\f'.
 *
 * @param   str: the string to check
 *
 * @return  true if the string only consists of whitespace characters, or false
 *          if other characters are present. false in case of error.
 */
inline bool
str_is_blank (const str_t str[static 1])
{
    return strisblank (str->str);
}

/**
 * transform all uppercase characters in a str_t string to lowercase
 * characters. this will modify the string data.
 *
 * @param   str: the string to modify
 */
inline void
str_downcase (str_t str[static 1])
{
    strdowncase (str->str);
}

/**
 * transform all lowercase characters in a str_t string to uppercase
 * characters. this will modify the string data.
 *
 * @param   str: the string to modify
 */
inline void
str_upcase (str_t str[static 1])
{
    strupcase (str->str);
}

/**
 * resize the allocated data of a str_t string.
 *
 * @param   str: the string to expand
 * @param   cap: the minimum amount of capacity to resize to
 */
void
str_resize (str_t str[static 1], size_t cap)
{
    cap = max (next_pow_of_two (cap), STR_MIN_ALLOC);
    if (cap > str->len && cap != str->cap) {
        str->str = srealloc (str->str, cap * sizeof (char));
        str->cap = cap;
    }
}
