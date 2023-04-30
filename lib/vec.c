#include "vec.h"

#define IMPLEMENT_FUNCTIONS(MACRO)                                            \
    MACRO(u8) MACRO(u16) MACRO(u32) MACRO(u64)                                \
    MACRO(i8) MACRO(i16) MACRO(i32) MACRO(i64)                                \
    MACRO(f32) MACRO(f64)

/**
 * vectorized addition. each element of vector `b` will be added to its
 * counterpart element in vector `a` (i.e. `a[i] += b[i]`). the result will be
 * stored in `a`.
 *
 * @param   n: number of elements to add
 * @param   a: first vector, result destination
 * @param   b: second vector
 *
 * @usage   either through `vec_add_<type> (e.g. `vec_add_u32`), or through the
 *          generic macro `vec_add`
 */
#define IMPL_VEC_ADD(TYPE)                                                    \
    void                                                                      \
    vec_add_##TYPE (usize n, TYPE a[restrict n], const TYPE b[restrict n])    \
    {                                                                         \
        usize i;                                                              \
        for (i = 0; i < n; i++)                                               \
            a[i] += b[i];                                                     \
    }

/**
 * vectorized subtraction. each element of vector `b` will be subtracted from
 * its counterpart element in vector `a` (i.e. `a[i] -= b[i]`). the result will
 * be stored in `a`.
 *
 * @param   n: number of elements to subtract
 * @param   a: first vector, result destination
 * @param   b: second vector
 *
 * @usage   either through `vec_sub_<type> (e.g. `vec_sub_u32`), or through the
 *          generic macro `vec_sub`
 */
#define IMPL_VEC_SUB(TYPE)                                                    \
    void                                                                      \
    vec_sub_##TYPE (usize n, TYPE a[restrict n], const TYPE b[restrict n])    \
    {                                                                         \
        usize i;                                                              \
        for (i = 0; i < n; i++)                                               \
            a[i] -= b[i];                                                     \
    }

/**
 * vectorized fused multiply-add. each element of vector `a` will be multiplied
 * by its counterpart element in vector `b`, then the corresponding element in
 * vector `c` will be added to a (i.e. `a[i] = a[i] * b[i] + c[i]`). the result
 * will be stored in `a`.
 *
 * @param   n: number of elements to subtract
 * @param   a: first vector, result destination
 * @param   b: second vector (for multiplication)
 * @param   c: third vector (final summand)
 *
 * @usage   either through `vec_fma_<type> (e.g. `vec_fma_u32`), or through the
 *          generic macro `vec_fma`
 */
#define IMPL_VEC_FMA(TYPE)                                                    \
    void                                                                      \
    vec_fma_##TYPE (usize n, TYPE a[restrict n], const TYPE b[restrict n],    \
                    const TYPE c[restrict n])                                 \
    {                                                                         \
        usize i;                                                              \
        for (i = 0; i < n; i++)                                               \
            a[i] = (TYPE) (a[i] * b[i]) + c[i];                               \
    }

IMPLEMENT_FUNCTIONS(IMPL_VEC_ADD)
IMPLEMENT_FUNCTIONS(IMPL_VEC_SUB)
IMPLEMENT_FUNCTIONS(IMPL_VEC_FMA)
