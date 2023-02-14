#include "str.h"
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"

#define STR_MIN_ALLOC 64

int
str_new (str_t *str)
{
    if (!str)
        return errno = EINVAL, -1;
    str->str = smalloc (STR_MIN_ALLOC * sizeof (char));
    str->str[0] = '\0';
    str->len = 0;
    str->cap = STR_MIN_ALLOC;
    return 0;
}

int
str_new_cap (str_t *str, size_t want_cap)
{
    size_t cap;

    if (!str)
        return errno = EINVAL, -1;
    cap = max (next_pow_of_two (want_cap), STR_MIN_ALLOC);
    str->str = smalloc (cap);
    str->str[0] = '\0';
    str->len = 0;
    str->cap = cap;
    return 0;
}

inline int
str_new_from (str_t *str, const char *src)
{
    if (str && src)
        return str_new_from_len (str, src, strlen (src));
    else
        return errno = EINVAL, -1;
}

int
str_new_from_len (str_t *str, const char *src, size_t len)
{
    size_t cap;

    if (!str || !src)
        return errno = EINVAL, -1;
    cap = max (next_pow_of_two (len + 1), STR_MIN_ALLOC);
    str->str = smalloc (cap * sizeof (char));
    str->len = len;
    str->cap = cap;
    strncpy (str->str, src, len);
    str->str[len] = '\0';
    return 0;
}

inline void
str_free (str_t *str)
{
    if (str)
        free (str->str);
}

inline int
str_append (str_t *str, const char *src)
{
    if (str && src)
        return str_append_len (str, src, strlen (src));
    else
        return errno = EINVAL, -1;
}

int
str_append_len (str_t *str, const char *src, size_t len)
{
    size_t cap;

    if (!str || !src)
        return errno = EINVAL, -1;
    cap = max (next_pow_of_two (str->len + len + 1), STR_MIN_ALLOC);
    str->str = srealloc (str->str, cap * sizeof (char));
    strncpy (str->str + str->len, src, len);
    str->len += len;
    str->cap = cap;
    str->str[str->len] = '\0';
    return 0;
}
