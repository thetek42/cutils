#include "cstr.h"
#include <ctype.h>
#include <errno.h>
#include <string.h>

/**
 * trim whitespace of a cstring (both beginning and end). a null terminator
 * will be placed after the last non-whitespace character. this modifies the
 * string.
 *
 * @param   str: the string to trim
 *
 * @return  a pointer to the beginning of the trimmed string. the string is not
 *          copied, and the returned pointer points to somewhere within the
 *          original string.
 */
char *
strtrim (char *str)
{
    if (str == NULL) return errno = EINVAL, NULL;

    strtrimr (str);
    return strtriml (str);
}

/**
 * trim whitespace of a cstring on the left (beginning of string). the original
 * string will be preserved.
 *
 * @param   str: the string to trim
 *
 * @return  a pointer to the beginning of the trimmed string. the string is not
 *          copied, and the returned pointer points to somewhere within the
 *          original string.
 */
char *
strtriml (char *str)
{
    if (str == NULL) return errno = EINVAL, NULL;

    while (*str && isspace (*str))
        str++;

    return str;
}

/**
 * trim whitespace of a cstring on the right (end of string). a null terminator
 * will be placed after the last non-whitespace character. this modifies the
 * string.
 *
 * @param   str: the string to trim
 *
 * @return  the new string length
 */
ssize_t
strtrimr (char *str)
{
    size_t len, i;

    if (str == NULL) return errno = EINVAL, -1;

    i = len = strlen (str);
    while (i <= len && isspace (str[i - 1]))
        i--;
    str[i] = '\0';

    return i;
}

ssize_t
strcount (const char *str, char c)
{
    size_t count;

    if (str == NULL) return errno = EINVAL, -1;

    count = 0;
    while (*str)
        if (*str++ == c)
            count += 1;
    
    return count;
}

void
strdowncase (char *str)
{
    if (str == NULL)
        errno = EINVAL;
    else
        while (*str)
        {
            if (isupper (*str))
                *str += 0x20;
            str++;
        }
}

void
strupcase (char *str)
{
    if (str == NULL)
        errno = EINVAL;
    else
        while (*str)
        {
            if (islower (*str))
                *str -= 0x20;
            str++;
        }
}
