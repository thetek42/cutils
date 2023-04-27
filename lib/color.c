#include "color.h"
#include <errno.h>
#include <math.h>

/**
 * turn a floating point rgb struct (r, g, b, a in [0.0f .. 1.0f]) into an
 * integer rgb struct (r, g, b, a in [0 .. 255]).
 *
 * @param   rgbf: the rgbf_t struct to convert
 *
 * @return  the corresponding rgb_t struct
 */
rgb_t
rgbf_to_rgb (rgbf_t rgbf)
{
    return (rgb_t) {
        .r = (u8) lroundf (rgbf.r * 255.0f),
        .g = (u8) lroundf (rgbf.g * 255.0f),
        .b = (u8) lroundf (rgbf.b * 255.0f),
        .a = (u8) lroundf (rgbf.a * 255.0f),
    };
}

/**
 * turn an integer rgb struct (r, g, b, a in [0 .. 255]) into a floating point
 * rgb struct (r, g, b, a in [0.0f .. 1.0f]).
 *
 * @param   rgb: the rgb_t struct to convert
 *
 * @return  the corresponding rgbf_t struct
 */
rgbf_t
rgb_to_rgbf (rgb_t rgb)
{
    return (rgbf_t) {
        .r = ((f32) rgb.r) / 255.0f,
        .g = ((f32) rgb.g) / 255.0f,
        .b = ((f32) rgb.b) / 255.0f,
        .a = ((f32) rgb.a) / 255.0f,
    };
}

/**
 * get the corresponding rgb color (integer) to a given hsl color. on error,
 * errno is set and a zero-initialized struct is returned.
 *
 * @param   hsl: the hsl color
 *
 * @return  the corresponding rgb color
 *
 * @errno   EINVAL: invalid hsl value passed
 */
inline rgb_t
hsl_to_rgb (hsl_t hsl)
{
    return rgbf_to_rgb (hsl_to_rgbf (hsl));
}

/**
 * get the corresponding rgb color (floating point) to a given hsl color. on
 * error, errno is set and a zero-initialized struct is returned.
 *
 * @param   hsl: the hsl color
 *
 * @return  the corresponding rgb color
 *
 * @errno   EINVAL: invalid hsl value passed
 *
 * @see     https://en.wikipedia.org/wiki/HSL_and_HSV#Color_conversion_formulae
 */
rgbf_t
hsl_to_rgbf (hsl_t hsl)
{
    f32 c, h2, m, x;
    rgbf_t rgbf;

    if (hsl.h > 360 || hsl.s < 0.0f || hsl.s > 1.0f ||
        hsl.l < 0.0f || hsl.s > 1.0f)
        return errno = EINVAL, (rgbf_t) {0};

    c = (1.0f - fabsf (2.0f * hsl.l - 1.0f)) * hsl.s;
    h2 = ((f32) hsl.h) / 60.0f;
    x = c * (1.0f - fabsf (fmodf (h2, 2.0f) - 1.0f));
    m = hsl.l - (c / 2.0f);
    x += m;
    c += m;

    if      (h2 <  1.0f) { rgbf.r = c; rgbf.g = x; rgbf.b = m; }
    else if (h2 <  2.0f) { rgbf.r = x; rgbf.g = c; rgbf.b = m; }
    else if (h2 <  3.0f) { rgbf.r = m; rgbf.g = c; rgbf.b = x; }
    else if (h2 <  4.0f) { rgbf.r = m; rgbf.g = x; rgbf.b = c; }
    else if (h2 <  5.0f) { rgbf.r = x; rgbf.g = m; rgbf.b = c; }
    else if (h2 <= 6.0f) { rgbf.r = c; rgbf.g = m; rgbf.b = x; }
    
    rgbf.a = hsl.a;

    return rgbf;
}

/**
 * get the corresponding hsl color to a given rgb color (integer).
 *
 * @param   rgb: the rgb color
 *
 * @return  the corresponding hsl color
 */
inline hsl_t
rgb_to_hsl (rgb_t rgb)
{
    return rgbf_to_hsl (rgb_to_rgbf (rgb));
}

/**
 * get the corresponding hsl color to a given rgb color (floating point). on
 * error, errno is set and a zero-initialized struct is returned.
 *
 * @param   rgbf: the rgb color
 *
 * @return  the corresponding hsl color
 *
 * @errno   EINVAL: invalid rgb value passed
 *
 * @see     https://en.wikipedia.org/wiki/HSL_and_HSV#Color_conversion_formulae
 */
hsl_t
rgbf_to_hsl (rgbf_t rgbf)
{
    f32 c, xmin, xmax;
    hsl_t hsl;

    if (rgbf.r < 0.0f || rgbf.r > 1.0f || rgbf.g < 0.0f || rgbf.g > 1.0f ||
        rgbf.b < 0.0f || rgbf.b > 1.0f)
        return errno = EINVAL, (hsl_t) {0};

    xmax = fmaxf (rgbf.r, fmaxf (rgbf.g, rgbf.b));
    xmin = fminf (rgbf.r, fminf (rgbf.g, rgbf.b));
    c = xmax - xmin;
    
    if (c == 0.0f)
        hsl.h = 0;
    else if (xmax == rgbf.r)
        hsl.h = (u8) lroundf (60.0f * fmodf (((rgbf.g - rgbf.b) / c), 6));
    else if (xmax == rgbf.g)
        hsl.h = (u8) lroundf (60.0f * (((rgbf.b - rgbf.r) / c) + 2.0f));
    else if (xmax == rgbf.b)
        hsl.h = (u8) lroundf (60.0f * (((rgbf.r - rgbf.g) / c) + 4.0f));

    hsl.a = rgbf.a;
    hsl.l = (xmax + xmin) / 2.0f;
    hsl.s = (hsl.l == 0.0f || hsl.l == 1.0f)
            ? 0.0f
            : ((xmax - hsl.l) / fminf (hsl.l, 1.0f - hsl.l));

    return hsl;
}
