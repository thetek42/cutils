#ifndef CUTILS_COMMON_H_
#define CUTILS_COMMON_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <sys/types.h>

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

/* integer abbreviations */
typedef signed char schar;
typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;
typedef unsigned long long ullong;
typedef long long llong;
/* fixed-size integers */
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;
/* sizes */
typedef size_t usize;
typedef ssize_t isize;
/* floating point types */
typedef float f32;
typedef double f64;
/* fixed-size booleans */
typedef uint8_t b8;
typedef uint16_t b16;
typedef uint32_t b32;
typedef uint64_t b64;

/* nullptr from C23 */
#if __STDC_VERSION__ < 202000L
# define nullptr NULL
typedef void *nullptr_t;
#endif

void *smalloc (size_t size); /* safe malloc */
void *srealloc (void *ptr, size_t size); /* safe realloc */
int rand_range (int min, int max); /* create a random number within an interval */

#endif // CUTILS_COMMON_H_
