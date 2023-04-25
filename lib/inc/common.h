#ifndef CUTILS_COMMON_H_
#define CUTILS_COMMON_H_

#include <stddef.h>
#include <stdint.h>

#define max(a, b) ((a) > (b) ? (a) : (b)) /* find the maximum of two numbers */
#define min(a, b) ((a) < (b) ? (a) : (b)) /* find the minimum of two numbers */

#if __STDC_VERSION__ >= 202000L // C23 or above
# include <stdbit.h>
# define next_pow_of_two(n) (((size_t) 1) << (64 - stdc_leading_zeros (n))) /* round up a size_t number to the next power of two (64-bit) */
#else
# if UINTPTR_MAX == 0xffffffffffffffff
#  define next_pow_of_two(n) (((size_t) 1) << (64 - __builtin_clzll (n))) /* round up a size_t number to the next power of two (64-bit) */
# elif UINTPTR_MAX == 0xffffffff
#  define next_pow_of_two(n) (((size_t) 1) << (64 - __builtin_clz (n))) /* round up a size_t number to the next power of two (32-bit) */
# else
#  error unsupported architecture: size_t expected to be 64-bit or 32-bit.
# endif
#endif

void *smalloc (size_t size); /* safe malloc */
void *srealloc (void *ptr, size_t size); /* safe realloc */
int rand_range (int min, int max); /* create a random number within an interval */

#endif // CUTILS_COMMON_H_
