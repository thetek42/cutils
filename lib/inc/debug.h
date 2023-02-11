#ifndef CUTILS_DEBUG_H_
#define CUTILS_DEBUG_H_

#include <stddef.h>
#include <stdlib.h>

#ifdef CUTILS_DEBUG_TRACE
# define malloc(size) debug_malloc (size, __FILE__, __LINE__) /* macro wrapper for debug_malloc() */
# define realloc(ptr, size) debug_realloc (ptr, size, __FILE__, __LINE__) /* macro wrapper for debug_realloc() */
# define free(ptr) debug_free (ptr, __FILE__, __LINE__) /* macro wrapper for debug_free() */
#endif

void *debug_malloc (size_t size, const char *file, size_t line); /* allocate memory using malloc() and print a fitting debug message */
void *debug_realloc (void *ptr, size_t size, const char *file, size_t line); /* reallocate memory using realloc() and print a fitting debug message */
void debug_free (void *ptr, const char *file, size_t line); /* free memory using free() and print a fitting debug message */

#endif // CUTILS_DEBUG_H_
