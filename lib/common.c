#include "common.h"
#include <stdlib.h>
#include "log.h"

/**
 * safe malloc. instead of returning null on error, the program will exit.
 *
 * @param   size: the number of bytes to allocate
 */
void *
smalloc (size_t size)
{
    void *ptr;

    ptr = malloc (size);
    if (!ptr)
    {
        log_error ("failed to allocate %zu bytes of memory\n", size);
        exit (EXIT_FAILURE);
    }

    return ptr;
}

/**
 * safe realloc. instead of returning null on error, the program will exit.
 *
 * @param   ptr: the pointer to reallocate
 * @param   size: the new number of bytes
 */
void *
srealloc (void *ptr, size_t size)
{
    ptr = realloc (ptr, size);
    if (!ptr)
    {
        log_error ("failed to allocate %zu bytes of memory\n", size);
        exit (EXIT_FAILURE);
    }

    return ptr;
}
