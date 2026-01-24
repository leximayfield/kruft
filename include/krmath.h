/*
 * Copyright (c) 2024 Lexi Mayfield
 *
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#if !defined(KRMATH_H)
#define KRMATH_H

#include "krconfig.h"

/**
 * @brief e
 */
#define KR_E 2.7182818284590452354

/**
 * @brief 1/log(2).
 */
#define KR_LOG2E 1.4426950408889634074

/**
 * @brief 1/log(10).
 */
#define KR_LOG10E 0.43429448190325182765

/**
 * @brief log(2).
 */
#define KR_LN2 0.69314718055994530942

/**
 * @brief log(10).
 */
#define KR_LN10 2.3025850929940456840

/**
 * @brief pi.
 */
#define KR_PI 3.1415926535897932385

/**
 * @brief pi/2.
 */
#define KR_PI_2 1.5707963267948966192

/**
 * @brief pi/4.
 */
#define KR_PI_4 0.78539816339744830962

/*
 * @brief 1/pi.
 */
#define KR_1_PI 0.31830988618379067154

/**
 * @brief 2/pi.
 */
#define KR_2_PI 0.63661977236758134308

/**
 * @brief 2/sqrt(pi)
 */
#define KR_2_SQRTPI 1.1283791670955125739

/**
 * @brief sqrt(2)
 */
#define KR_SQRT2 1.4142135623730950488

/**
 * @brief 1/sqrt(2)
 */
#define KR_SQRT1_2 0.70710678118654752440

/**
 * @brief Minimum of two values.
 */
#define kr_min(a, b) ((b) < (a)) ? (b) : (a)

/**
 * @brief Maximum of two values.
 */
#define kr_max(a, b) ((a) < (b)) ? (b) : (a)

/**
 * @brief Clamp value between minimum and maximum.
 *
 * @param v Value to clamp.
 * @param lo Lower bound, inclusive.
 * @param hi Upper bound, inclusive.
 */
#define kr_clamp(v, lo, hi) ((v) < (lo)) ? (lo) : ((hi) < (v)) ? (hi) : (v)

/**
 * @brief Get the sign of a number.
 *
 * @return 1 if number is positive, -1 if number is negative, 0 if zero.
 */
#define kr_signum(v) ((v > 0) - (v < 0))

#endif /* KRMATH_H */
