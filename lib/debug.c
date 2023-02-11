#include "debug.h"
#include <inttypes.h>
#include <stdlib.h>
#include "log.h"

void *
debug_malloc (size_t size, const char *file, size_t line)
{
    void *ptr;

    ptr = malloc (size);
    if (ptr == NULL)
        log_print_fl (LOG_LEVEL_DEBUG, file, line, "malloc of size %zu \e[31mreturned null\e[0m\n", size);
    else
        log_print_fl (LOG_LEVEL_DEBUG, file, line, "malloc of size %zu to ptr %p\n", size, ptr);

    return ptr;
}

void *
debug_realloc (void *ptr, size_t size, const char *file, size_t line)
{
    void *new_ptr;
    uintptr_t old_ptr;

    old_ptr = (uintptr_t) ptr;
    new_ptr = realloc (ptr, size);
    if (new_ptr == NULL && size != 0)
        log_print_fl (LOG_LEVEL_DEBUG, file, line, "realloc of ptr %#" PRIxPTR " to size %zu \e[31mreturned null\e[0m\n", old_ptr, size);
    else if (new_ptr == ptr)
        log_print_fl (LOG_LEVEL_DEBUG, file, line, "realloc of ptr %p to size %zu\n", new_ptr, size);
    else
        log_print_fl (LOG_LEVEL_DEBUG, file, line, "realloc of ptr %#" PRIxPTR " to new ptr %p with size %zu\n", old_ptr, new_ptr, size);

    return new_ptr;
}

void
debug_free (void *ptr, const char *file, size_t line)
{
    log_print_fl (LOG_LEVEL_DEBUG, file, line, "free ptr %p\n", ptr);
    free (ptr);
}
