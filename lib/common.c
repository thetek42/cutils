#include "common.h"
#include <stdlib.h>
#include "log.h"

/**
 * safe malloc. instead of returning null on error, the program will exit.
 *
 * @param   size: the number of bytes to allocate
 */
void *
smalloc (usize size)
{
    void *ptr;

    ptr = malloc (size);
    if (!ptr)
        log_fatal ("failed to allocate %zu bytes of memory\n", size);

    return ptr;
}

/**
 * safe realloc. instead of returning null on error, the program will exit.
 *
 * @param   ptr: the pointer to reallocate
 * @param   size: the new number of bytes
 */
void *
srealloc (void *ptr, usize size)
{
#if __STDC_VERSION__ >= 202000L // C23 or above
    if (ptr == nullptr)
        return smalloc (size);
#endif

    ptr = realloc (ptr, size);
    if (!ptr)
        log_fatal ("failed to allocate %zu bytes of memory\n", size);

    return ptr;
}

/**
 * create a random number within an interval
 *
 * @param   min: the lower bound (inclusive)
 * @param   max: the upper bound (inclusive)
 *
 * @return  a pseudo-random number within the given bounds
 */
int
rand_range (int min, int max)
{
    return (rand () % (max - min + 1)) + min;
}
