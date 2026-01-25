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

/**
 * @brief Count the number of array items.
 */
#define kr_countof(a) (sizeof(a) / sizeof(a[0]))

/**
 * @brief Equivalent to realloc(ptr, nmemb * size), except returns NULL if
 *        nmemb * size would overflow.
 *
 * @param ptr Pointer to memory block to be resized, or NULL if a new allocation
 *            is desired.
 * @param nmemb Number of elements in desired allocation.
 * @param size Size of each element in desired allocation.
 * @return Pointer to reallocated memory, or NULL if realloc failed or overflow
 *         was detected.
 */
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
