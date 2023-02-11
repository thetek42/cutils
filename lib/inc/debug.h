#ifndef CUTILS_DEBUG_H_
#define CUTILS_DEBUG_H_

#include <stddef.h>

#ifdef CUTILS_DEBUG_TRACE
# define malloc(size) debug_malloc (size, __FILE__, __LINE__);
# define realloc(ptr, size) debug_realloc (ptr, size, __FILE__, __LINE__);
# define free(ptr) debug_free (ptr, __FILE__, __LINE__);
#endif

void *debug_malloc (size_t size, const char *file, size_t line);
void *debug_realloc (void *ptr, size_t size, const char *file, size_t line);
void debug_free (void *ptr, const char *file, size_t line);

#endif // CUTILS_DEBUG_H_
