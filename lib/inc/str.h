#ifndef CUTILS_STR_H_
#define CUTILS_STR_H_

#include <stddef.h>

typedef struct
{
    char *str;
    size_t len;
    size_t cap;
} str_t;

void str_new (str_t *str);
void str_new_cap (str_t *str, size_t want_cap);
void str_new_from (str_t *str, const char *src);
void str_new_from_len (str_t *str, const char *src, size_t len);
void str_free (str_t *str);

#endif // CUTILS_STR_H_
