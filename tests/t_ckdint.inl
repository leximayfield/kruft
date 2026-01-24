/*
 * Copyright (c) 2024 Lexi Mayfield
 *
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#include <stdlib.h>

#include "zztest.h"

#include "krckdint.h"

#include "krlib.h"

/******************************************************************************/

static struct
{
    int32_t res;
    intmax_t a;
    intmax_t b;
} g_add_s32_tests[] = {
    {-1, 1, -2},                          //
    {3, 1, 2},                            //
    {-3, -1, -2},                         //
    {1, 1, 0},                            //
    {-2, 0, -2},                          //
    {0xDEAD, INT32_MAX, 1},               //
    {0xDEAD, INT32_MAX, INT32_MAX},       //
    {0xDEAD, INT32_MIN, -1},              //
    {0xDEAD, INT32_MIN, INT32_MIN},       //
    {2147483646, 1073741823, 1073741823}, //
    {0xDEAD, 1073741824, 1073741824},     //
};

TEST(ckdint, kr_ckd_add_i32)
{
    int32_t res = 0;
    bool overflow = false;
    size_t i = 0;

    for (i = 0; i < KR_COUNTOF(g_add_s32_tests); i++)
    {
        SCOPED_TRACE("a:%ld, b:%ld", (long)g_add_s32_tests[i].a, (long)g_add_s32_tests[i].b);

        overflow = kr_ckd_add_i32(&res, g_add_s32_tests[i].a, g_add_s32_tests[i].b);
        if (!overflow)
        {
            EXPECT_INTEQ(res, g_add_s32_tests[i].res);
        }
        else
        {
            EXPECT_INTEQ(0xDEAD, g_add_s32_tests[i].res);
        }
    }
}

/******************************************************************************/

static struct
{
    uint32_t res;
    uintmax_t a;
    uintmax_t b;
} g_add_u32_tests[] = {
    {3, 1, 2},                            //
    {1, 1, 0},                            //
    {2, 0, 2},                            //
    {0xDEAD, UINT32_MAX, 1},              //
    {0xDEAD, 1, UINT32_MAX},              //
    {0xDEAD, UINT32_MAX, UINT32_MAX},     //
    {4294967294, 2147483647, 2147483647}, //
    {0xDEAD, 2147483648, 2147483648},     //
};

TEST(ckdint, kr_ckd_add_u32)
{
    uint32_t res = 0;
    bool overflow = false;
    size_t i = 0;

    for (i = 0; i < KR_COUNTOF(g_add_u32_tests); i++)
    {
        SCOPED_TRACE("a:%lu, b:%lu", (unsigned long)g_add_u32_tests[i].a, (unsigned long)g_add_u32_tests[i].b);

        overflow = kr_ckd_add_u32(&res, g_add_u32_tests[i].a, g_add_u32_tests[i].b);
        if (!overflow)
        {
            EXPECT_INTEQ(res, g_add_u32_tests[i].res);
        }
        else
        {
            EXPECT_INTEQ(0xDEAD, g_add_u32_tests[i].res);
        }
    }
}

SUITE(ckdint)
{
    SUITE_TEST(ckdint, kr_ckd_add_i32);
    SUITE_TEST(ckdint, kr_ckd_add_u32);
}
