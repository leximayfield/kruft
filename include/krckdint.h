/*
 * Copyright (c) 2024 Lexi Mayfield
 *
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#if !defined(KRCKDINT_H)
#define KRCKDINT_H

#include "./krint.h"

/******************************************************************************/

#define KR_CKD_INT(fn, t, cb, min, max) \
    KR_CONSTEXPR bool fn(t *res, intmax_t a, intmax_t b) \
    { \
        intmax_t result = 0; \
        bool overflow = cb(&result, a, b); \
        overflow |= (result > max || result < min); \
        *res = KR_CASTS(t, result); \
        return overflow; \
    }

#define KR_CKD_UINT(fn, t, cb, max) \
    KR_CONSTEXPR bool fn(t *res, uintmax_t a, uintmax_t b) \
    { \
        uintmax_t result = 0; \
        bool overflow = cb(&result, a, b); \
        overflow |= result > max; \
        *res = KR_CASTS(t, result); \
        return overflow; \
    }

/******************************************************************************/

KR_CONSTEXPR bool kr_ckd_add_imax(intmax_t *res, intmax_t a, intmax_t b)
{
    const uintmax_t aa = KR_CASTS(uintmax_t, a);
    const uintmax_t bb = KR_CASTS(uintmax_t, b);
    const uintmax_t result = aa + bb;
    *res = KR_CASTS(intmax_t, result);
    return (((a ^ b) >= 0) && ((a ^ result) < 0));
}

KR_CKD_INT(kr_ckd_add_i16, int16_t, kr_ckd_add_imax, INT16_MIN, INT16_MAX)
KR_CKD_INT(kr_ckd_add_i32, int32_t, kr_ckd_add_imax, INT32_MIN, INT32_MAX)

/******************************************************************************/

KR_CONSTEXPR bool kr_ckd_add_umax(uintmax_t *res, uintmax_t a, uintmax_t b)
{
    const uintmax_t result = a + b;
    *res = result;
    return result < a;
}

KR_CKD_UINT(kr_ckd_add_u16, uint16_t, kr_ckd_add_umax, UINT16_MAX);
KR_CKD_UINT(kr_ckd_add_u32, uint32_t, kr_ckd_add_umax, UINT32_MAX);

/******************************************************************************/

KR_CONSTEXPR bool kr_ckd_sub_imax(intmax_t *res, intmax_t a, intmax_t b)
{
    const uintmax_t aa = KR_CASTS(uintmax_t, a);
    const uintmax_t bb = KR_CASTS(uintmax_t, b);
    const uintmax_t result = aa - bb;
    *res = KR_CASTS(intmax_t, result);
    return ((a ^ b) & (result ^ a)) < 0;
}

KR_CKD_INT(kr_ckd_sub_i16, int16_t, kr_ckd_sub_imax, INT16_MIN, INT16_MAX)
KR_CKD_INT(kr_ckd_sub_i32, int32_t, kr_ckd_sub_imax, INT32_MIN, INT32_MAX)

/******************************************************************************/

KR_CONSTEXPR bool kr_ckd_sub_umax(uintmax_t *res, uintmax_t a, uintmax_t b)
{
    const uintmax_t result = a - b;
    *res = result;
    return a < b;
}

KR_CKD_UINT(kr_ckd_sub_u16, uint16_t, kr_ckd_sub_umax, UINT16_MAX);
KR_CKD_UINT(kr_ckd_sub_u32, uint32_t, kr_ckd_sub_umax, UINT32_MAX);

/******************************************************************************/

KR_CONSTEXPR bool kr_ckd_mul_imax(intmax_t *res, intmax_t a, intmax_t b)
{
    const uintmax_t aa = KR_CASTS(uintmax_t, a);
    const uintmax_t bb = KR_CASTS(uintmax_t, b);
    const uintmax_t result = aa * bb;
    *res = KR_CASTS(intmax_t, result);
    return b < 0 && a == INTMAX_MIN || b && *res / b != a;
}

KR_CKD_INT(kr_ckd_mul_i16, int16_t, kr_ckd_mul_imax, INT16_MIN, INT16_MAX)
KR_CKD_INT(kr_ckd_mul_i32, int32_t, kr_ckd_mul_imax, INT32_MIN, INT32_MAX)

/******************************************************************************/

KR_CONSTEXPR bool kr_ckd_mul_umax(uintmax_t *res, uintmax_t a, uintmax_t b)
{
    const uintmax_t result = a * b;
    *res = result;
    return a && result / a != b;
}

KR_CKD_UINT(kr_ckd_mul_u16, uint16_t, kr_ckd_mul_umax, UINT16_MAX);
KR_CKD_UINT(kr_ckd_mul_u32, uint32_t, kr_ckd_mul_umax, UINT32_MAX);

/******************************************************************************/

#undef KR_CKD_INT
#undef KR_CKD_UINT

#endif /* !defined(KRCKDINT_H) */
