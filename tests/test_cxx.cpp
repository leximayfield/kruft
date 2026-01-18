/*
 * Copyright (c) 2024 Lexi Mayfield
 *
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#include "zztest.h"

#include "t_bit.inl"
#include "t_bltin.inl"
#include "t_ckdint.inl"
#include "t_ctype.inl"
#include "t_int.inl"
#include "t_lib.inl"
#include "t_limits.inl"
#include "t_math.inl"
#include "t_rand.inl"
#include "t_serial.inl"
#include "t_str.inl"

int main()
{
    ADD_TEST_SUITE(bit);
    ADD_TEST_SUITE(bltin);
    ADD_TEST_SUITE(ckdint);
    ADD_TEST_SUITE(ctype);
    ADD_TEST_SUITE(int);
    ADD_TEST_SUITE(lib);
    ADD_TEST_SUITE(limits);
    ADD_TEST_SUITE(math);
    ADD_TEST_SUITE(rand);
    ADD_TEST_SUITE(serial);
    ADD_TEST_SUITE(str);
    return RUN_TESTS();
}
