#ifndef VEC_H_
#define VEC_H_

#include "common.h"

// helper macros

#define __VEC_GET_FUNCTION_NAME(PREFIX, TYPE) _Generic((TYPE),                \
    u8*: PREFIX##_##u8, u16*: PREFIX##_##u16,                                 \
    u32*: PREFIX##_##u32, u64*: PREFIX##_##u64,                               \
    i8*: PREFIX##_##i8, i16*: PREFIX##_##i16,                                 \
    i32*: PREFIX##_##i32, i64*: PREFIX##_##i64,                               \
    f32*: PREFIX##_##f32, f64*: PREFIX##_##f64)
#define _DECLARE_FUNCTIONS(MACRO)                                             \
    MACRO(u8); MACRO(u16); MACRO(u32); MACRO(u64);                            \
    MACRO(i8); MACRO(i16); MACRO(i32); MACRO(i64);                            \
    MACRO(f32); MACRO(f64)
#define _DECLARE_VEC_ADD(TYPE) void vec_add_##TYPE (usize n, TYPE a[restrict n], const TYPE b[restrict n])
#define _DECLARE_VEC_SUB(TYPE) void vec_sub_##TYPE (usize n, TYPE a[restrict n], const TYPE b[restrict n])
#define _DECLARE_VEC_FMA(TYPE) void vec_fma_##TYPE (usize n, TYPE a[restrict n], const TYPE b[restrict n], const TYPE c[restrict n])

// exported macros

#define vec_add(n, a, b) __VEC_GET_FUNCTION_NAME(vec_add, a)(n, a, b) /* vectorized addition - void vec_add<T>(usize n, T a[restrict n], const T b[restrict n]) */
#define vec_sub(n, a, b) __VEC_GET_FUNCTION_NAME(vec_sub, a)(n, a, b) /* vectorized subtraction - void vec_sub<T>(usize n, T a[restrict n], const T b[restrict n]) */
#define vec_fma(n, a, b, c) __VEC_GET_FUNCTION_NAME(vec_fma, a)(n, a, b, c) /* vectorized fused multiply-add - void vec_fma<T>(usize n, T a[restrict n], const T b[restrict n], const T c[restrict n]) */

// function declarations

_DECLARE_FUNCTIONS(_DECLARE_VEC_ADD);
_DECLARE_FUNCTIONS(_DECLARE_VEC_SUB);
_DECLARE_FUNCTIONS(_DECLARE_VEC_FMA);

// undefine helper macros

#undef _DECLARE_FUNCTIONS
#undef _DECLARE_VEC_ADD
#undef _DECLARE_VEC_SUB
#undef _DECLARE_VEC_FMA

#endif // VEC_H_
