#ifndef CUTILS_DEBUG_H_
#define CUTILS_DEBUG_H_

#include <stdlib.h>
#include "common.h"

#ifdef CUTILS_DEBUG_TRACE
# define malloc(size) debug_malloc (size, __FILE__, __LINE__) /* macro wrapper for debug_malloc() */
# define realloc(ptr, size) debug_realloc (ptr, size, __FILE__, __LINE__) /* macro wrapper for debug_realloc() */
# define free(ptr) debug_free (ptr, __FILE__, __LINE__) /* macro wrapper for debug_free() */
# define smalloc(size) debug_smalloc (size, __FILE__, __LINE__) /* macro wrapper for debug_malloc() */
# define srealloc(ptr, size) debug_srealloc (ptr, size, __FILE__, __LINE__) /* macro wrapper for debug_realloc() */
#endif

void *debug_malloc (size_t size, const char *file, usize line); /* allocate memory using malloc() and print a fitting debug message */
void *debug_realloc (void *ptr, usize size, const char *file, usize line); /* reallocate memory using realloc() and print a fitting debug message */
void debug_free (void *ptr, const char *file, usize line); /* free memory using free() and print a fitting debug message */
void *debug_smalloc (usize size, const char *file, usize line); /* allocate memory using smalloc() and print a fitting debug message */
void *debug_srealloc (void *ptr, usize size, const char *file, usize line); /* reallocate memory using srealloc() and print a fitting debug message */

#endif // CUTILS_DEBUG_H_
