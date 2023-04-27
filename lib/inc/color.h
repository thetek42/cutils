#ifndef COLOR_H_
#define COLOR_H_

#include "common.h"

/* integer rgb struct, fields accept [0 .. 255] */
typedef struct {
    u8 r, g, b, a;
} rgb_t;

/* floating point rgb struct, fields accept [0.0f .. 1.0f] */
typedef struct {
    f32 r, g, b, a;
} rgbf_t;

/* hsl struct, h accepts [0 .. 360]; s, l, a accept [0.0f .. 1.0f] */
typedef struct {
    u16 h;
    f32 s, l, a;
} hsl_t;

rgb_t rgbf_to_rgb (rgbf_t rgbf); /* turn a floating point rgb struct into an integer rbg struct */
rgbf_t rgb_to_rgbf (rgb_t rgb); /* turn an integer rgb struct into a floating point rbg struct */
rgb_t hsl_to_rgb (hsl_t hsl); /* get the corresponding rgb color (integer) to a given hsl color */
rgbf_t hsl_to_rgbf (hsl_t hsl); /* get the corresponding rgb color (floating point) to a given hsl color */
hsl_t rgb_to_hsl (rgb_t rgb); /* get the corresponding hsl color to a given rgb color (integer) */
hsl_t rgbf_to_hsl (rgbf_t rgbf); /* get the corresponding hsl color to a given rgb color (floating point) */

#endif // COLOR_H_
