#include "str.h"
#include <stdlib.h>
#include <string.h>
#include "common.h"

#define STR_MIN_ALLOC 64

void
str_new (str_t *str)
{
    str->str = smalloc (STR_MIN_ALLOC * sizeof (char));
    str->len = 0;
    str->cap = STR_MIN_ALLOC;
}

void
str_new_cap (str_t *str, size_t want_cap)
{
    size_t cap;

    cap = max (next_pow_of_two (want_cap), STR_MIN_ALLOC);
    str->str = smalloc (cap);
    str->len = 0;
    str->cap = cap;
}

inline int
str_new_from (str_t *str, const char *src)
{
    if (src)
        return str_new_from_len (str, src, strlen (src)), 0;
    else
        return errno = EINVAL, -1;
}

int
str_new_from_len (str_t *str, const char *src, size_t len)
{
    size_t cap;

    if (!src)
        return errno = EINVAL, -1;
    cap = max (next_pow_of_two (len + 1), STR_MIN_ALLOC);
    str->str = smalloc (cap * sizeof (char));
    str->len = len;
    str->cap = cap;
    strcpy (str->str, src);
    return 0;
}

inline void
str_free (str_t *str)
{
    if (str)
        free (str->str);
}
