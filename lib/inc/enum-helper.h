#ifndef ENUM_HELPER_H_
#define ENUM_HELPER_H_

/**
 * since C has no built-in way of converting an enum value into a string, these
 * hepler macros may come in handy. defining an enum with these macros
 * automatically generates a proper "enum_get_repr" function that returns the
 * enum literal as a string if used properly. An example for how to use this
 * and what code will be generated can be seen below.
 *
 *
 *
 * =============== USAGE ===============
 *
 * ----- (orientation.h) -----
 * #define ORIENTATION_ENUM(X) \
 *     X(Orientation_North)    \
 *     X(Orientation_East)     \
 *     X(Orientation_South)    \
 *     X(Orientation_West)
 * DECLARE_ENUM (orientation, ORIENTATION_ENUM);
 *
 * ----- (orientation.c) -----
 * #include "orientation.h"
 * IMPL_ENUM (orientation, ORIENTATION_ENUM)
 *
 *
 *
 * =============== GENERATED RESULT ===============
 *
 * ----- (orientation.h) -----
 * typedef enum {
 *     Orientation_North,
 *     Orientation_East,
 *     Orientation_South,
 *     Orientation_West,
 * } orientation_t;
 * const char *orientation_get_repr (orientation_t value);
 *
 * ----- (orientation.c) -----
 * const char *orientation_get_repr (orientation_t value)
 * {
 *     switch (value) {
 *         case Orientation_North: { return "Orientation_North"; }
 *         case Orientation_East: { return "Orientation_East"; }
 *         case Orientation_South: { return "Orientation_South"; }
 *         case Orientation_West: { return "Orientation_West"; }
 *         default: { return ""; }
 *     }
 * }
 */

#define __ENUM_VALUE(NAME) NAME,
#define __ENUM_CASE(NAME) case NAME: { return #NAME; }

#define DECLARE_ENUM(ENUM_NAME, ENUM_DEF)                                     \
    typedef enum {                                                            \
        ENUM_DEF (__ENUM_VALUE)                                               \
    } ENUM_NAME##_t;                                                          \
    const char *ENUM_NAME##_get_repr (ENUM_NAME##_t value)

#define IMPL_ENUM(ENUM_NAME, ENUM_DEF)                                        \
    const char *ENUM_NAME##_get_repr (ENUM_NAME##_t value)                    \
    {                                                                         \
        switch (value) {                                                      \
            ENUM_DEF (__ENUM_CASE)                                            \
            default: { return ""; }                                           \
        }                                                                     \
    }

#endif // ENUM_HELPER_H_
