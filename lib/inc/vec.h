#ifndef VEC_H_
#define VEC_H_

#include "common.h"

// helper macros

#define GET_FUNCTION_NAME(PREFIX, TYPE) _Generic((TYPE),                      \
    u8*: PREFIX##_##u8, u16*: PREFIX##_##u16,                                 \
    u32*: PREFIX##_##u32, u64*: PREFIX##_##u64,                               \
    i8*: PREFIX##_##i8, i16*: PREFIX##_##i16,                                 \
    i32*: PREFIX##_##i32, i64*: PREFIX##_##i64,                               \
    f32*: PREFIX##_##f32, f64*: PREFIX##_##f64)
#define DECLARE_FUNCTIONS(MACRO)                                              \
    MACRO(u8); MACRO(u16); MACRO(u32); MACRO(u64);                            \
    MACRO(i8); MACRO(i16); MACRO(i32); MACRO(i64);                            \
    MACRO(f32); MACRO(f64)
#define DECLARE_VEC_ADD(TYPE) void vec_add_##TYPE (usize n, TYPE a[restrict n], const TYPE b[restrict n])
#define DECLARE_VEC_SUB(TYPE) void vec_sub_##TYPE (usize n, TYPE a[restrict n], const TYPE b[restrict n])

// exported macros

#define vec_add(n, a, b) GET_FUNCTION_NAME(vec_add, a)(n, a, b) /* vectorized addition - void vec_add<T>(usize n, T a[restrict n], const T b[restrict n]) */
#define vec_sub(n, a, b) GET_FUNCTION_NAME(vec_sub, a)(n, a, b) /* vectorized subtraction - void vec_sub<T>(usize n, T a[restrict n], const T b[restrict n]) */

// function declarations

DECLARE_FUNCTIONS(DECLARE_VEC_ADD);
DECLARE_FUNCTIONS(DECLARE_VEC_SUB);

// undefine helper macros

#undef __GET_FUNCTION_NAME
#undef __DECLARE_FUNCTIONS
#undef __DECLARE_VEC_ADD
#undef __DECLARE_VEC_SUB

#endif // VEC_H_
