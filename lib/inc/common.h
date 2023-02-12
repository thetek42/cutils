#ifndef CUTILS_COMMON_H_
#define CUTILS_COMMON_H_

#include <stddef.h>
#include <stdint.h>

#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

#if UINTPTR_MAX == 0xffffffffffffffff
# define next_pow_of_two(n) (((size_t) 1) << (64 - __builtin_clzll (n)))
#elif UINTPTR_MAX == 0xffffffff
# define next_pow_of_two(n) (((size_t) 1) << (64 - __builtin_clz (n)))
#else
# error unsupported architecture: size_t expected to be 64-bit or 32-bit.
#endif

void *smalloc (size_t size);
void *srealloc (void *ptr, size_t size);

#endif // CUTILS_COMMON_H_
