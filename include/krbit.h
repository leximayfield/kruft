/*
 * Copyright (c) 2024 Lexi Mayfield
 *
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

/*
 * Bit-manipulation functions, C++20's <bit> for all.
 *
 * This header is allowed to break the "no cleverness" rule, since these
 * functions generally need to be as fast as possible.  That said, the
 * individual functions should still allow for easy copy-pasting.
 */

#if !defined(KRBIT_H)
#define KRBIT_H

#include "./krconfig.h"

#include "./krbool.h"
#include "./krint.h"

/**
 * @brief Bit-reverse an 8-bit value.
 *
 * @link http://aggregate.org/MAGIC/#Bit%20Reversal
 */
KR_CONSTEXPR uint8_t kr_bitreverse8(uint8_t x);

/**
 * @brief Bit-reverse a 16-bit value.
 *
 * @link http://aggregate.org/MAGIC/#Bit%20Reversal
 */
KR_CONSTEXPR uint16_t kr_bitreverse16(uint16_t x);

/**
 * @brief Bit-reverse a 32-bit value.
 *
 * @link http://aggregate.org/MAGIC/#Bit%20Reversal
 */
KR_CONSTEXPR uint32_t kr_bitreverse32(uint32_t x);

#if defined(UINT64_MAX)

/**
 * @brief Bit-reverse a 64-bit value.
 *
 * @link http://aggregate.org/MAGIC/#Bit%20Reversal
 */
KR_CONSTEXPR uint64_t kr_bitreverse64(uint64_t x);

#endif /* defined(UINT64_MAX) */

/**
 * @brief Byteswap a 16-bit value.
 */
KR_CONSTEXPR uint16_t kr_byteswap16(uint16_t x);

/**
 * @brief Byteswap a 32-bit value.
 */
KR_CONSTEXPR uint32_t kr_byteswap32(uint32_t x);

#if defined(UINT64_MAX)

/**
 * @brief Byteswap a 64-bit value.
 */
KR_CONSTEXPR uint64_t kr_byteswap64(uint64_t x);

#endif

KR_CONSTEXPR bool kr_has_single_bit8(uint8_t x) KR_NOEXCEPT;
KR_CONSTEXPR bool kr_has_single_bit16(uint16_t x) KR_NOEXCEPT;
KR_CONSTEXPR bool kr_has_single_bit32(uint32_t x) KR_NOEXCEPT;

#if defined(UINT64_MAX)

KR_CONSTEXPR bool kr_has_single_bit64(uint64_t x) KR_NOEXCEPT;

#endif

/**
 * @brief Round up to the nearest power of two.
 *
 * @link http://graphics.stanford.edu/~seander/bithacks.html#RoundUpPowerOf2Float
 */
KR_CONSTEXPR uint8_t kr_bit_ceil8(uint8_t x) KR_NOEXCEPT;

/**
 * @brief Round up to the nearest power of two.
 *
 * @link http://graphics.stanford.edu/~seander/bithacks.html#RoundUpPowerOf2Float
 */
KR_CONSTEXPR uint16_t kr_bit_ceil16(uint16_t x) KR_NOEXCEPT;

/**
 * @brief Round up to the nearest power of two.
 *
 * @link http://graphics.stanford.edu/~seander/bithacks.html#RoundUpPowerOf2Float
 */
KR_CONSTEXPR uint32_t kr_bit_ceil32(uint32_t x) KR_NOEXCEPT;

#if defined(UINT64_MAX)

/**
 * @brief Round up to the nearest power of two.
 *
 * @link http://graphics.stanford.edu/~seander/bithacks.html#RoundUpPowerOf2Float
 */
KR_CONSTEXPR uint64_t kr_bit_ceil64(uint64_t x) KR_NOEXCEPT;

#endif

/**
 * @brief Round down to the nearest power of two.
 *
 * @link https://www.amazon.com/Hackers-Delight-2nd-Henry-Warren-dp-0321842685/dp/0321842685
 */
KR_CONSTEXPR uint8_t kr_bit_floor8(uint8_t x) KR_NOEXCEPT;

/**
 * @brief Round down to the nearest power of two.
 *
 * @link https://www.amazon.com/Hackers-Delight-2nd-Henry-Warren-dp-0321842685/dp/0321842685
 */
KR_CONSTEXPR uint16_t kr_bit_floor16(uint16_t x) KR_NOEXCEPT;

/**
 * @brief Round down to the nearest power of two.
 *
 * @link https://www.amazon.com/Hackers-Delight-2nd-Henry-Warren-dp-0321842685/dp/0321842685
 */
KR_CONSTEXPR uint32_t kr_bit_floor32(uint32_t x) KR_NOEXCEPT;

#if defined(UINT64_MAX)

/**
 * @brief Round down to the nearest power of two.
 *
 * @link https://www.amazon.com/Hackers-Delight-2nd-Henry-Warren-dp-0321842685/dp/0321842685
 */
KR_CONSTEXPR uint64_t kr_bit_floor64(uint64_t x) KR_NOEXCEPT;

#endif

/**
 * @brief Count minimum number of bits needed to represent value.
 */
KR_CONSTEXPR unsigned kr_bit_width8(uint8_t x) KR_NOEXCEPT;

/**
 * @brief Count minimum number of bits needed to represent value.
 */
KR_CONSTEXPR unsigned kr_bit_width16(uint16_t x) KR_NOEXCEPT;

/**
 * @brief Count minimum number of bits needed to represent value.
 */
KR_CONSTEXPR unsigned kr_bit_width32(uint32_t x) KR_NOEXCEPT;

#if defined(UINT64_MAX)

/**
 * @brief Count minimum number of bits needed to represent value.
 */
KR_CONSTEXPR unsigned kr_bit_width64(uint64_t x) KR_NOEXCEPT;

#endif

KR_CONSTEXPR uint8_t kr_rotate_left8(uint8_t x, unsigned c) KR_NOEXCEPT;
KR_CONSTEXPR uint16_t kr_rotate_left16(uint16_t x, unsigned c) KR_NOEXCEPT;
KR_CONSTEXPR uint32_t kr_rotate_left32(uint32_t x, unsigned c) KR_NOEXCEPT;
#if defined(UINT64_MAX)
KR_CONSTEXPR uint64_t kr_rotate_left64(uint64_t x, unsigned c) KR_NOEXCEPT;
#endif

KR_CONSTEXPR uint8_t kr_rotate_right8(uint8_t x, unsigned c) KR_NOEXCEPT;
KR_CONSTEXPR uint16_t kr_rotate_right16(uint16_t x, unsigned c) KR_NOEXCEPT;
KR_CONSTEXPR uint32_t kr_rotate_right32(uint32_t x, unsigned c) KR_NOEXCEPT;
#if defined(UINT64_MAX)
KR_CONSTEXPR uint64_t kr_rotate_right64(uint64_t x, unsigned c) KR_NOEXCEPT;
#endif

/**
 * @brief Count leading (starting at MSB) zero bits.
 *
 * @link http://aggregate.ee.engr.uky.edu/MAGIC/#Leading%20Zero%20Count
 */
KR_CONSTEXPR unsigned kr_leading_zeros8(uint8_t x) KR_NOEXCEPT;

/**
 * @brief Count leading (starting at MSB) zero bits.
 *
 * @link http://aggregate.ee.engr.uky.edu/MAGIC/#Leading%20Zero%20Count
 */
KR_CONSTEXPR unsigned kr_leading_zeros16(uint16_t x) KR_NOEXCEPT;

/**
 * @brief Count leading (starting at MSB) zero bits.
 *
 * @link http://aggregate.ee.engr.uky.edu/MAGIC/#Leading%20Zero%20Count
 */
KR_CONSTEXPR unsigned kr_leading_zeros32(uint32_t x) KR_NOEXCEPT;

#if defined(UINT64_MAX)

/**
 * @brief Count leading (starting at MSB) zero bits.
 *
 * @link http://aggregate.ee.engr.uky.edu/MAGIC/#Leading%20Zero%20Count
 */
KR_CONSTEXPR unsigned kr_leading_zeros64(uint64_t x) KR_NOEXCEPT;

#endif

/**
 * @brief Count leading (starting at MSB) one bits.
 */
KR_CONSTEXPR unsigned kr_leading_ones8(uint8_t x) KR_NOEXCEPT;

/**
 * @brief Count leading (starting at MSB) one bits.
 */
KR_CONSTEXPR unsigned kr_leading_ones16(uint16_t x) KR_NOEXCEPT;

/**
 * @brief Count leading (starting at MSB) one bits.
 */
KR_CONSTEXPR unsigned kr_leading_ones32(uint32_t x) KR_NOEXCEPT;

#if defined(UINT64_MAX)

/**
 * @brief Count leading (starting at MSB) one bits.
 */
KR_CONSTEXPR unsigned kr_leading_ones64(uint64_t x) KR_NOEXCEPT;

#endif

/**
 * @brief Count trailing (starting at LSB) zero bits.
 */
KR_CONSTEXPR unsigned kr_trailing_zeros8(uint8_t x) KR_NOEXCEPT;

/**
 * @brief Count trailing (starting at LSB) zero bits.
 */
KR_CONSTEXPR unsigned kr_trailing_zeros16(uint16_t x) KR_NOEXCEPT;

/**
 * @brief Count trailing (starting at LSB) zero bits.
 */
KR_CONSTEXPR unsigned kr_trailing_zeros32(uint32_t x) KR_NOEXCEPT;

#if defined(UINT64_MAX)

/**
 * @brief Count trailing (starting at LSB) zero bits.
 */
KR_CONSTEXPR unsigned kr_trailing_zeros64(uint64_t x) KR_NOEXCEPT;

#endif

/**
 * @brief Count trailing (starting at LSB) one bits.
 */
KR_CONSTEXPR unsigned kr_trailing_ones8(uint8_t x) KR_NOEXCEPT;

/**
 * @brief Count trailing (starting at LSB) one bits.
 */
KR_CONSTEXPR unsigned kr_trailing_ones16(uint16_t x) KR_NOEXCEPT;

/**
 * @brief Count trailing (starting at LSB) one bits.
 */
KR_CONSTEXPR unsigned kr_trailing_ones32(uint32_t x) KR_NOEXCEPT;

#if defined(UINT64_MAX)

/**
 * @brief Count trailing (starting at LSB) one bits.
 */
KR_CONSTEXPR unsigned kr_trailing_ones64(uint64_t x) KR_NOEXCEPT;

#endif

/**
 * @brief Count number of set bits in an integer.
 *
 * @link https://graphics.stanford.edu/%7Eseander/bithacks.html#CountBitsSetParallel
 */
KR_CONSTEXPR unsigned kr_count_ones8(uint8_t x) KR_NOEXCEPT;

/**
 * @brief Count number of set bits in an integer.
 *
 * @link https://graphics.stanford.edu/%7Eseander/bithacks.html#CountBitsSetParallel
 */
KR_CONSTEXPR unsigned kr_count_ones16(uint16_t x) KR_NOEXCEPT;

/**
 * @brief Count number of set bits in an integer.
 *
 * @link https://graphics.stanford.edu/%7Eseander/bithacks.html#CountBitsSetParallel
 */
KR_CONSTEXPR unsigned kr_count_ones32(uint32_t x) KR_NOEXCEPT;

#if defined(UINT64_MAX)

/**
 * @brief Count number of set bits in an integer.
 *
 * @link https://graphics.stanford.edu/%7Eseander/bithacks.html#CountBitsSetParallel
 */
KR_CONSTEXPR unsigned kr_count_ones64(uint64_t x) KR_NOEXCEPT;

#endif /* defined(UINT64_MAX) */

/******************************************************************************/
#if !(KRUFT_CONFIG_USEIMPLEMENTATION) || defined(KRUFT_IMPLEMENTATION)
/******************************************************************************/

KR_CONSTEXPR uint8_t kr_bitreverse8(uint8_t x)
{
    x = KR_CASTS(uint8_t, (x & 0xaa) >> 1) | KR_CASTS(uint8_t, (x & 0x55) << 1);
    x = KR_CASTS(uint8_t, (x & 0xcc) >> 2) | KR_CASTS(uint8_t, (x & 0x33) << 2);
    return KR_CASTS(uint8_t, x >> 4) | KR_CASTS(uint8_t, x << 4);
}

KR_CONSTEXPR uint16_t kr_bitreverse16(uint16_t x)
{
    x = KR_CASTS(uint16_t, (x & 0xaaaa) >> 1) | KR_CASTS(uint16_t, (x & 0x5555) << 1);
    x = KR_CASTS(uint16_t, (x & 0xcccc) >> 2) | KR_CASTS(uint16_t, (x & 0x3333) << 2);
    x = KR_CASTS(uint16_t, (x & 0xf0f0) >> 4) | KR_CASTS(uint16_t, (x & 0x0f0f) << 4);
    return KR_CASTS(uint16_t, x >> 8) | KR_CASTS(uint16_t, x << 8);
}

KR_CONSTEXPR uint32_t kr_bitreverse32(uint32_t x)
{
    x = ((x & 0xaaaaaaaa) >> 1) | ((x & 0x55555555) << 1);
    x = ((x & 0xcccccccc) >> 2) | ((x & 0x33333333) << 2);
    x = ((x & 0xf0f0f0f0) >> 4) | ((x & 0x0f0f0f0f) << 4);
    x = ((x & 0xff00ff00) >> 8) | ((x & 0x00ff00ff) << 8);
    return (x >> 16) | (x << 16);
}

#if defined(UINT64_MAX)

KR_CONSTEXPR uint64_t kr_bitreverse64(uint64_t x)
{
    x = ((x & 0xaaaaaaaaaaaaaaaa) >> 1) | ((x & 0x5555555555555555u) << 1);
    x = ((x & 0xcccccccccccccccc) >> 2) | ((x & 0x3333333333333333u) << 2);
    x = ((x & 0xf0f0f0f0f0f0f0f0) >> 4) | ((x & 0x0f0f0f0f0f0f0f0fu) << 4);
    x = ((x & 0xff00ff00ff00ff00) >> 8) | ((x & 0x00ff00ff00ff00ffu) << 8);
    x = ((x & 0xffff0000ffff0000) >> 16) | ((x & 0x0000ffff0000ffffu) << 16);
    return (x >> 32) | (x << 32);
}

#endif /* defined(UINT64_MAX) */

/******************************************************************************/

KR_CONSTEXPR uint16_t kr_byteswap16(uint16_t x)
{
    return KR_CASTS(uint16_t, (x & 0xFF00) >> 8) | /**/
           KR_CASTS(uint16_t, (x & 0x00FF) << 8);  /**/
}

KR_CONSTEXPR uint32_t kr_byteswap32(uint32_t x)
{
    return ((x & 0xFF000000) >> 24) | /**/
           ((x & 0x00FF0000) >> 8) |  /**/
           ((x & 0x0000FF00) << 8) |  /**/
           ((x & 0x000000FF) << 24);  /**/
}

#if defined(UINT64_MAX)

KR_CONSTEXPR uint64_t kr_byteswap64(uint64_t x)
{
    return ((x & UINT64_C(0xFF00000000000000)) >> UINT64_C(56)) | /**/
           ((x & UINT64_C(0x00FF000000000000)) >> UINT64_C(40)) | /**/
           ((x & UINT64_C(0x0000FF0000000000)) >> UINT64_C(24)) | /**/
           ((x & UINT64_C(0x000000FF00000000)) >> UINT64_C(8)) |  /**/
           ((x & UINT64_C(0x00000000FF000000)) << UINT64_C(8)) |  /**/
           ((x & UINT64_C(0x0000000000FF0000)) << UINT64_C(24)) | /**/
           ((x & UINT64_C(0x000000000000FF00)) << UINT64_C(40)) | /**/
           ((x & UINT64_C(0x00000000000000FF)) << UINT64_C(56));  /**/
}

#endif /* defined(UINT64_MAX) */

/******************************************************************************/

KR_CONSTEXPR bool kr_has_single_bit8(uint8_t x) KR_NOEXCEPT
{
    return x && !(x & (x - 1));
}

KR_CONSTEXPR bool kr_has_single_bit16(uint16_t x) KR_NOEXCEPT
{
    return x && !(x & (x - 1));
}

KR_CONSTEXPR bool kr_has_single_bit32(uint32_t x) KR_NOEXCEPT
{
    return x && !(x & (x - 1));
}

#if defined(UINT64_MAX)

KR_CONSTEXPR bool kr_has_single_bit64(uint64_t x) KR_NOEXCEPT
{
    return x && !(x & (x - 1));
}

#endif /* defined(UINT64_MAX) */

/******************************************************************************/

KR_CONSTEXPR uint8_t kr_bit_ceil8(uint8_t x) KR_NOEXCEPT
{
    if (x <= 1)
    {
        return 1;
    }

    x -= 1;
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x += 1;
    return x;
}

KR_CONSTEXPR uint16_t kr_bit_ceil16(uint16_t x) KR_NOEXCEPT
{
    if (x <= 1)
    {
        return 1;
    }

    x -= 1;
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x += 1;
    return x;
}

KR_CONSTEXPR uint32_t kr_bit_ceil32(uint32_t x) KR_NOEXCEPT
{
    if (x <= 1)
    {
        return 1;
    }

    x -= 1;
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;
    x += 1;
    return x;
}

#if defined(UINT64_MAX)

KR_CONSTEXPR uint64_t kr_bit_ceil64(uint64_t x) KR_NOEXCEPT
{
    if (x <= 1)
    {
        return 1;
    }

    x -= 1;
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;
    x |= x >> 32;
    x += 1;
    return x;
}

#endif /* defined(UINT64_MAX) */

/******************************************************************************/

KR_CONSTEXPR uint8_t kr_bit_floor8(uint8_t x) KR_NOEXCEPT
{
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    return x - (x >> 1);
}

KR_CONSTEXPR uint16_t kr_bit_floor16(uint16_t x) KR_NOEXCEPT
{
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    return x - (x >> 1);
}

KR_CONSTEXPR uint32_t kr_bit_floor32(uint32_t x) KR_NOEXCEPT
{
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;
    return x - (x >> 1);
}

#if defined(UINT64_MAX)

KR_CONSTEXPR uint64_t kr_bit_floor64(uint64_t x) KR_NOEXCEPT
{
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;
    x |= x >> 32;
    return x - (x >> 1);
}

#endif /* defined(UINT64_MAX) */

/******************************************************************************/

KR_CONSTEXPR unsigned kr_bit_width8(uint8_t x) KR_NOEXCEPT
{
    return 8 - kr_leading_zeros8(x);
}

KR_CONSTEXPR unsigned kr_bit_width16(uint16_t x) KR_NOEXCEPT
{
    return 16 - kr_leading_zeros16(x);
}

KR_CONSTEXPR unsigned kr_bit_width32(uint32_t x) KR_NOEXCEPT
{
    return 32 - kr_leading_zeros32(x);
}

#if defined(UINT64_MAX)

KR_CONSTEXPR unsigned kr_bit_width64(uint64_t x) KR_NOEXCEPT
{
    return 64 - kr_leading_zeros64(x);
}

#endif /* defined(UINT64_MAX) */

/******************************************************************************/

KR_CONSTEXPR uint8_t kr_rotate_left8(uint8_t x, unsigned c) KR_NOEXCEPT
{
    return KR_CASTS(uint8_t, x << c) | KR_CASTS(uint8_t, x >> ((0 - c) & 0x07));
}

KR_CONSTEXPR uint16_t kr_rotate_left16(uint16_t x, unsigned c) KR_NOEXCEPT
{
    return KR_CASTS(uint16_t, x << c) | KR_CASTS(uint16_t, x >> ((0 - c) & 0x0F));
}

KR_CONSTEXPR uint32_t kr_rotate_left32(uint32_t x, unsigned c) KR_NOEXCEPT
{
    return (x << c) | (x >> ((0 - c) & 0x1F));
}

#if defined(UINT64_MAX)

KR_CONSTEXPR uint64_t kr_rotate_left64(uint64_t x, unsigned c) KR_NOEXCEPT
{
    return (x << c) | (x >> ((0 - c) & 0x3F));
}

#endif /* defined(UINT64_MAX) */

/******************************************************************************/

KR_CONSTEXPR uint8_t kr_rotate_right8(uint8_t x, unsigned c) KR_NOEXCEPT
{
    return KR_CASTS(uint8_t, x >> c) | KR_CASTS(uint8_t, x << ((0 - c) & 0x07));
}

KR_CONSTEXPR uint16_t kr_rotate_right16(uint16_t x, unsigned c) KR_NOEXCEPT
{
    return KR_CASTS(uint16_t, x >> c) | KR_CASTS(uint16_t, x << ((0 - c) & 0x0F));
}

KR_CONSTEXPR uint32_t kr_rotate_right32(uint32_t x, unsigned c) KR_NOEXCEPT
{
    return (x >> c) | (x << ((0 - c) & 0x1F));
}

#if defined(UINT64_MAX)

KR_CONSTEXPR uint64_t kr_rotate_right64(uint64_t x, unsigned c) KR_NOEXCEPT
{
    return (x >> c) | (x << ((0 - c) & 0x3F));
}

#endif /* defined(UINT64_MAX) */

/******************************************************************************/

KR_CONSTEXPR unsigned kr_leading_zeros8(uint8_t x) KR_NOEXCEPT
{
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    return 8 - kr_count_ones8(x);
}

KR_CONSTEXPR unsigned kr_leading_zeros16(uint16_t x) KR_NOEXCEPT
{
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    return 16 - kr_count_ones16(x);
}

KR_CONSTEXPR unsigned kr_leading_zeros32(uint32_t x) KR_NOEXCEPT
{
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;
    return 32 - kr_count_ones32(x);
}

#if defined(UINT64_MAX)

KR_CONSTEXPR unsigned kr_leading_zeros64(uint64_t x) KR_NOEXCEPT
{
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;
    x |= x >> 32;
    return 64 - kr_count_ones64(x);
}

#endif /* defined(UINT64_MAX) */

/******************************************************************************/

KR_CONSTEXPR unsigned kr_leading_ones8(uint8_t x) KR_NOEXCEPT
{
    x = ~x;
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    return 8 - kr_count_ones8(x);
}

KR_CONSTEXPR unsigned kr_leading_ones16(uint16_t x) KR_NOEXCEPT
{
    x = ~x;
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    return 16 - kr_count_ones16(x);
}

KR_CONSTEXPR unsigned kr_leading_ones32(uint32_t x) KR_NOEXCEPT
{
    x = ~x;
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;
    return 32 - kr_count_ones32(x);
}

#if defined(UINT64_MAX)

KR_CONSTEXPR unsigned kr_leading_ones64(uint64_t x) KR_NOEXCEPT
{
    x = ~x;
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;
    x |= x >> 32;
    return 64 - kr_count_ones64(x);
}

#endif /* defined(UINT64_MAX) */

/******************************************************************************/

KR_CONSTEXPR unsigned kr_trailing_zeros8(uint8_t x) KR_NOEXCEPT
{
    x |= x << 1;
    x |= x << 2;
    x |= x << 4;
    return 8 - kr_count_ones8(x);
}

KR_CONSTEXPR unsigned kr_trailing_zeros16(uint16_t x) KR_NOEXCEPT
{
    x |= x << 1;
    x |= x << 2;
    x |= x << 4;
    x |= x << 8;
    x |= x << 16;
    return 16 - kr_count_ones32(x);
}

KR_CONSTEXPR unsigned kr_trailing_zeros32(uint32_t x) KR_NOEXCEPT
{
    x |= x << 1;
    x |= x << 2;
    x |= x << 4;
    x |= x << 8;
    x |= x << 16;
    return 32 - kr_count_ones32(x);
}

#if defined(UINT64_MAX)

KR_CONSTEXPR unsigned kr_trailing_zeros64(uint64_t x) KR_NOEXCEPT
{
    x |= x << 1;
    x |= x << 2;
    x |= x << 4;
    x |= x << 8;
    x |= x << 16;
    x |= x << 32;
    return 64 - kr_count_ones64(x);
}

#endif /* defined(UINT64_MAX) */

/******************************************************************************/

KR_CONSTEXPR unsigned kr_trailing_ones8(uint8_t x) KR_NOEXCEPT
{
    x = ~x;
    x |= x << 1;
    x |= x << 2;
    x |= x << 4;
    return 8 - kr_count_ones8(x);
}

KR_CONSTEXPR unsigned kr_trailing_ones16(uint16_t x) KR_NOEXCEPT
{
    x = ~x;
    x |= x << 1;
    x |= x << 2;
    x |= x << 4;
    x |= x << 8;
    return 16 - kr_count_ones16(x);
}

KR_CONSTEXPR unsigned kr_trailing_ones32(uint32_t x) KR_NOEXCEPT
{
    x = ~x;
    x |= x << 1;
    x |= x << 2;
    x |= x << 4;
    x |= x << 8;
    x |= x << 16;
    return 32 - kr_count_ones32(x);
}

#if defined(UINT64_MAX)

KR_CONSTEXPR unsigned kr_trailing_ones64(uint64_t x) KR_NOEXCEPT
{
    x = ~x;
    x |= x << 1;
    x |= x << 2;
    x |= x << 4;
    x |= x << 8;
    x |= x << 16;
    x |= x << 32;
    return 64 - kr_count_ones64(x);
}

#endif /* defined(UINT64_MAX) */

/******************************************************************************/

KR_CONSTEXPR unsigned kr_count_ones8(uint8_t x) KR_NOEXCEPT
{
    x = x - ((x >> 1) & UINT8_C(0x55));
    x = (x & UINT8_C(0x33)) + ((x >> 2) & UINT8_C(0x33));
    x = (x + (x >> 4)) & UINT8_C(0x0f);
    return KR_CASTS(uint8_t, x *UINT8_C(0x01));
}

KR_CONSTEXPR unsigned kr_count_ones16(uint16_t x) KR_NOEXCEPT
{
    x = x - ((x >> 1) & UINT16_C(0x5555));
    x = (x & UINT16_C(0x3333)) + ((x >> 2) & UINT16_C(0x3333));
    x = (x + (x >> 4)) & UINT16_C(0x0f0f);
    return KR_CASTS(uint16_t, x *UINT16_C(0x0101)) >> 8;
}

KR_CONSTEXPR unsigned kr_count_ones32(uint32_t x) KR_NOEXCEPT
{
    x = x - ((x >> 1) & UINT32_C(0x55555555));
    x = (x & UINT32_C(0x33333333)) + ((x >> 2) & UINT32_C(0x33333333));
    x = (x + (x >> 4)) & UINT32_C(0x0f0f0f0f);
    return KR_CASTS(uint32_t, x *UINT32_C(0x01010101)) >> 24;
}

#if defined(UINT64_MAX)

KR_CONSTEXPR unsigned kr_count_ones64(uint64_t x) KR_NOEXCEPT
{
    x = x - ((x >> 1) & UINT64_C(0x5555555555555555));
    x = (x & UINT64_C(0x3333333333333333)) + ((x >> 2) & UINT64_C(0x3333333333333333));
    x = (x + (x >> 4)) & UINT64_C(0x0f0f0f0f0f0f0f0f);
    return KR_CASTS(uint64_t, x *UINT64_C(0x0101010101010101)) >> 56;
}

#endif /* defined(UINT64_MAX) */

#endif /* !(KRUFT_CONFIG_USEIMPLEMENTATION) || defined(KRUFT_IMPLEMENTATION) */

#endif /* !defined(KRBIT_H) */
