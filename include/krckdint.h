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

KR_CONSTEXPR bool kr_ckd_add_i32(int32_t *res, intmax_t a, intmax_t b)
{
    const intmax_t sa = a >> ((sizeof(intmax_t) * CHAR_BIT) - 1);
    const intmax_t sb = b >> ((sizeof(intmax_t) * CHAR_BIT) - 1);
    if (sa == sb)
    {
        // Sign is the same, check for overflow.
        if ((!sa && a > INT32_MAX - b) || (sa && a < INT32_MIN - b))
        {
            return true;
        }
    }

    *res = KR_CASTS(int32_t, a + b);
    return false;
}

KR_CONSTEXPR bool kr_ckd_add_u32(uint32_t *res, uintmax_t a, uintmax_t b)
{
    const uintmax_t c = a + b;
    if (c > UINT32_MAX || c < a)
    {
        return true;
    }

    *res = KR_CASTS(uint32_t, c);
    return false;
}

#endif /* !defined(KRCKDINT_H) */
