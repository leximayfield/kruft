/*
 * Copyright (c) 2024 Lexi Mayfield
 *
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#include "zztest.h"

#include "krmath.h"

TEST(math, kr_min_MACRO)
{
    EXPECT_INTEQ(1, kr_min(1, 2));
    EXPECT_INTEQ(1, kr_min(2, 1));
}

TEST(math, kr_max_MACRO)
{
    EXPECT_INTEQ(2, kr_max(1, 2));
    EXPECT_INTEQ(2, kr_max(2, 1));
}

TEST(math, kr_clamp_MACRO)
{
    EXPECT_INTEQ(2, kr_clamp(4, -1, 2));
    EXPECT_INTEQ(-1, kr_clamp(-4, -1, 2));
    EXPECT_INTEQ(-1, kr_clamp(-1, -1, 2));
    EXPECT_INTEQ(2, kr_clamp(2, -1, 2));
    EXPECT_INTEQ(0, kr_clamp(0, -1, 2));
}

TEST(math, kr_signum_MACRO)
{
    EXPECT_INTEQ(1, kr_signum(1));
    EXPECT_INTEQ(1, kr_signum(INT_MAX));
    EXPECT_UINTEQ(1, kr_signum(UINT_MAX));
    EXPECT_INTEQ(0, kr_signum(0));
    EXPECT_INTEQ(0, kr_signum(-0));
    EXPECT_INTEQ(-1, kr_signum(-1));
    EXPECT_INTEQ(-1, kr_signum(INT_MIN));
}

SUITE(math)
{
    SUITE_TEST(math, kr_min_MACRO);
    SUITE_TEST(math, kr_max_MACRO);
    SUITE_TEST(math, kr_clamp_MACRO);
    SUITE_TEST(math, kr_signum_MACRO);
}
