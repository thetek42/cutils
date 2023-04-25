#include "debug.h"
#include <inttypes.h>
#include <stdlib.h>
#include "common.h"
#include "log.h"

/**
 * allocate memory using malloc() and print a fitting debug message
 *
 * @param   size: the number of bytes to allocate
 * @param   file: the file in which malloc() was called
 * @param   line: the source code line where malloc() was called
 *
 * @return  the pointer to the allocated memory, or NULL in case of error
 *
 * @errno   see malloc(3)
 *
 * @usage   the header `debug.h` defines a macro `malloc(size)` that
 *          automatically inserts filename and line.
 */
void *
debug_malloc (size_t size, const char *file, size_t line)
{
    void *ptr;

    ptr = malloc (size);
    if (ptr == NULL)
        log_print_fl (LOG_LEVEL_DEBUG, file, line, "malloc of size %zu \x1b[31mreturned null\x1b[0m\n", size);
    else
        log_print_fl (LOG_LEVEL_DEBUG, file, line, "malloc of size %zu to ptr %p\n", size, ptr);

    return ptr;
}

/**
 * reallocate memory using realloc() and print a fitting debug message
 *
 * @param   ptr: the pointer to reallocate
 * @param   size: the new number of bytes
 * @param   file: the file in which realloc() was called
 * @param   line: the source code line where realloc() was called
 *
 * @return  the pointer to the reallocated memory, or NULL in case of error
 *
 * @errno   see realloc(3)
 *
 * @usage   the header `debug.h` defines a macro `realloc(ptr, size)` that
 *          automatically inserts filename and line.
 */
void *
debug_realloc (void *ptr, size_t size, const char *file, size_t line)
{
    void *new_ptr;
    uintptr_t old_ptr;

    old_ptr = (uintptr_t) ptr;
    new_ptr = realloc (ptr, size);
    if (new_ptr == NULL && size != 0)
        log_print_fl (LOG_LEVEL_DEBUG, file, line, "realloc of ptr %#" PRIxPTR " to size %zu \x1b[31mreturned null\x1b[0m\n", old_ptr, size);
    else if (new_ptr == ptr)
        log_print_fl (LOG_LEVEL_DEBUG, file, line, "realloc of ptr %p to size %zu\n", new_ptr, size);
    else
        log_print_fl (LOG_LEVEL_DEBUG, file, line, "realloc of ptr %#" PRIxPTR " to new ptr %p with size %zu\n", old_ptr, new_ptr, size);

    return new_ptr;
}

/**
 * free memory using free() and print a fitting debug message
 *
 * @param   ptr: the pointer to free
 * @param   file: the file in which free() was called
 * @param   line: the source code line where free() was called
 *
 * @usage   the header `debug.h` defines a macro `free(ptr)` that automatically
 *          inserts filename and line.
 */
void
debug_free (void *ptr, const char *file, size_t line)
{
    log_print_fl (LOG_LEVEL_DEBUG, file, line, "free ptr %p\n", ptr);
    free (ptr);
}

/**
 * allocate memory using smalloc() (see header `common.h`) and print a fitting
 * debug message
 *
 * @param   size: the number of bytes to allocate
 * @param   file: the file in which malloc() was called
 * @param   line: the source code line where malloc() was called
 *
 * @return  the pointer to the allocated memory, or NULL in case of error
 *
 * @usage   the header `debug.h` defines a macro `smalloc(size)` that
 *          automatically inserts filename and line.
 */
void *
debug_smalloc (size_t size, const char *file, size_t line)
{
    void *ptr;

    ptr = smalloc (size);
    log_print_fl (LOG_LEVEL_DEBUG, file, line, "smalloc of size %zu to ptr %p\n", size, ptr);

    return ptr;
}

/**
 * reallocate memory using srealloc() (see header `common.h`) and print a
 * fitting debug message
 *
 * @param   ptr: the pointer to reallocate
 * @param   size: the new number of bytes
 * @param   file: the file in which realloc() was called
 * @param   line: the source code line where realloc() was called
 *
 * @return  the pointer to the reallocated memory, or NULL in case of error
 *
 * @usage   the header `debug.h` defines a macro `srealloc(ptr, size)` that
 *          automatically inserts filename and line.
 */
void *
debug_srealloc (void *ptr, size_t size, const char *file, size_t line)
{
    void *new_ptr;
    uintptr_t old_ptr;

    old_ptr = (uintptr_t) ptr;
    new_ptr = srealloc (ptr, size);
    if (new_ptr == ptr)
        log_print_fl (LOG_LEVEL_DEBUG, file, line, "srealloc of ptr %p to size %zu\n", new_ptr, size);
    else
        log_print_fl (LOG_LEVEL_DEBUG, file, line, "srealloc of ptr %#" PRIxPTR " to new ptr %p with size %zu\n", old_ptr, new_ptr, size);

    return new_ptr;
}
