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

KR_CONSTEXPR bool kr_ckd_add_imax(intmax_t *res, intmax_t a, intmax_t b)
{
    const uintmax_t aa = KR_CASTS(uintmax_t, a);
    const uintmax_t bb = KR_CASTS(uintmax_t, b);
    const uintmax_t result = aa + bb;
    *res = KR_CASTS(intmax_t, result);
    return (((a ^ b) >= 0) && ((a ^ result) < 0));
}

KR_CONSTEXPR bool kr_ckd_add_i16(int16_t *res, intmax_t a, intmax_t b)
{
    intmax_t result = 0;
    bool overflow = kr_ckd_add_imax(&result, a, b);
    overflow |= (result > INT16_MAX || result < INT16_MIN);
    *res = KR_CASTS(int16_t, result);
    return overflow;
}

KR_CONSTEXPR bool kr_ckd_add_i32(int32_t *res, intmax_t a, intmax_t b)
{
    intmax_t result = 0;
    bool overflow = kr_ckd_add_imax(&result, a, b);
    overflow |= (result > INT32_MAX || result < INT32_MIN);
    *res = KR_CASTS(int32_t, result);
    return overflow;
}

/******************************************************************************/

KR_CONSTEXPR bool kr_ckd_add_umax(uintmax_t *res, uintmax_t a, uintmax_t b)
{
    const uintmax_t result = a + b;
    *res = result;
    return result < a;
}

KR_CONSTEXPR bool kr_ckd_add_u16(uint16_t *res, uintmax_t a, uintmax_t b)
{
    uintmax_t result = 0;
    bool overflow = kr_ckd_add_umax(&result, a, b);
    overflow |= result > UINT16_MAX;
    *res = KR_CASTS(uint16_t, result);
    return overflow;
}

KR_CONSTEXPR bool kr_ckd_add_u32(uint32_t *res, uintmax_t a, uintmax_t b)
{
    uintmax_t result = 0;
    bool overflow = kr_ckd_add_umax(&result, a, b);
    overflow |= result > UINT32_MAX;
    *res = KR_CASTS(uint32_t, result);
    return overflow;
}

#endif /* !defined(KRCKDINT_H) */
