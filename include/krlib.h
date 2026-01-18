/*
 * Copyright (c) 2024 Lexi Mayfield
 *
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#if !defined(KRLIB_H)
#define KRLIB_H

#include "./krconfig.h"

#if (!KR_CONFIG_NOINCLUDE)
#include <stddef.h>
#include <stdlib.h>
#endif

#define KR_COUNTOF(a) sizeof(a) / sizeof(a[0])

KR_NODISCARD KR_INLINE void *kr_reallocarray(void *ptr, size_t nmemb, size_t size);

/******************************************************************************/
#if !(KRUFT_CONFIG_USEIMPLEMENTATION) || defined(KRUFT_IMPLEMENTATION)
/******************************************************************************/

KR_NODISCARD KR_INLINE void *kr_reallocarray(void *ptr, size_t nmemb, size_t size)
{
    const size_t x = nmemb * size;
    if (nmemb != 0 && x / nmemb != size)
    {
        return NULL;
    }
    return KR_REALLOC(ptr, nmemb * size);
}

#endif /* !(KRUFT_CONFIG_USEIMPLEMENTATION) || defined(KRUFT_IMPLEMENTATION) */

#endif /* !defined(KRLIB_H) */
