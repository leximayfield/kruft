/*
 * zztest - A test framework for crufty compilers.
 * Copyright (c) 2024 Lexi Mayfield
 *
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#if !defined(INCLUDE_ZZTEST_H)
#define INCLUDE_ZZTEST_H

#include <limits.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Boolean datatype. */
typedef int ZZT_BOOL;
#define ZZT_FALSE (0)
#define ZZT_TRUE (1)

/* Determine char signedness. */
#if CHAR_MAX == SCHAR_MAX
#define zzt_cmp_char zzt_cmp_int
#else
#define zzt_cmp_char zzt_cmp_uint
#endif

/* Determine our 64-bit data type. */
#if defined(ULLONG_MAX) /* C99 */
#if (ULLONG_MAX == 0xFFFFFFFFFFFFFFFF)
#define ZZT_HAS_LONGLONG_
#endif
#elif defined(ULONG_LONG_MAX) /* GNU */
#if (ULONG_LONG_MAX == 0xFFFFFFFFFFFFFFFF)
#define ZZT_HAS_LONGLONG_
#endif
#endif
#if defined(ZZT_HAS_LONGLONG_)
typedef long long ZZT_INTMAX;
typedef unsigned long long ZZT_UINTMAX;
#define ZZT_PRIiMAX "lld"
#define ZZT_PRIuMAX "llu"
#define ZZT_PRIxMAX "llx"
#elif defined(_UI64_MAX) /* MSVC */
typedef __int64 ZZT_INTMAX;
typedef unsigned __int64 ZZT_UINTMAX;
#define ZZT_PRIiMAX "I64d"
#define ZZT_PRIuMAX "I64u"
#define ZZT_PRIxMAX "I64x"
#else
typedef long ZZT_INTMAX;
typedef unsigned long ZZT_UINTMAX;
#define ZZT_PRIiMAX "ld"
#define ZZT_PRIuMAX "lu"
#define ZZT_PRIxMAX "lx"
#endif

enum zzt_fmt_e {
    ZZT_FMT_BOOL,
    ZZT_FMT_CHAR,
    ZZT_FMT_INT,
    ZZT_FMT_UINT,
    ZZT_FMT_XINT,
    ZZT_FMT_STR,
};

enum zzt_cmp_e {
    ZZT_CMP_EQ,
    ZZT_CMP_NE,
    ZZT_CMP_LT,
    ZZT_CMP_LE,
    ZZT_CMP_GT,
    ZZT_CMP_GE,
};

struct zzt_test_state_s;

typedef void (*zzt_testfunc)(struct zzt_test_state_s *);

typedef struct zzt_test_s {
    zzt_testfunc func;
    const char *suite_name;
    const char *test_name;
    struct zzt_test_s *next;
    struct zzt_test_s *next_skip;
    struct zzt_test_s *next_fail;
} zzt_test_s;

struct zzt_test_suite_s {
    struct zzt_test_s *head;
    struct zzt_test_s *tail;
    const char *suite_name;
    unsigned long tests_count;
    struct zzt_test_suite_s *next;
};

/**
 * @brief Function name of a test suite.
 */
#define ZZT_SUITENAME(s) s##__SUITE

/**
 * @brief Symbol name of test suite info.
 */
#define ZZT_SUITEINFO(s) s##__SINFO

/**
 * @brief Function name of a test.
 */
#define ZZT_TESTNAME(s, t) s##__##t##__TEST

/**
 * @brief Symbol name of test info.
 */
#define ZZT_TESTINFO(s, t) s##__##t##__TINFO

#define ZZT_EXPECT_BOOL(cmp, l, r) \
    zzt_cmp_uint(zzt_test_state, ZZT_FMT_BOOL, cmp, !!(l), !!(r), #l, #r, \
        __FILE__, __LINE__)
#define ZZT_EXPECT_CHAR(cmp, l, r) \
    zzt_cmp_char(zzt_test_state, ZZT_FMT_CHAR, cmp, l, r, #l, #r, __FILE__, \
        __LINE__)
#define ZZT_EXPECT_INT(cmp, l, r) \
    zzt_cmp_int(zzt_test_state, ZZT_FMT_INT, cmp, l, r, #l, #r, __FILE__, \
        __LINE__)
#define ZZT_EXPECT_UINT(cmp, l, r) \
    zzt_cmp_uint(zzt_test_state, ZZT_FMT_UINT, cmp, l, r, #l, #r, __FILE__, \
        __LINE__)
#define ZZT_EXPECT_XINT(cmp, l, r) \
    zzt_cmp_uint(zzt_test_state, ZZT_FMT_XINT, cmp, l, r, #l, #r, __FILE__, \
        __LINE__)
#define ZZT_EXPECT_STR(cmp, l, r) \
    zzt_cmp_str(zzt_test_state, ZZT_FMT_STR, cmp, l, r, #l, #r, __FILE__, \
        __LINE__)

/**
 * @brief Define a test suite.  Creates a function definition, which must
 *        be followed by a {} block containing SUITE_TESTs.
 *
 * @param s Test suite.  Must be valid identifier.
 */
#define SUITE(s) \
    static struct zzt_test_suite_s ZZT_SUITEINFO(s); \
    void ZZT_SUITENAME(s)(void)

/**
 * @brief Define a test.  Creates a function definition accepting a single
 *        parameter containing test state, which must be followed by a {}
 *        block containing your expects and assertions.
 *
 * @param s Test suite.  Must be valid identifier.
 * @param t Test name.  Must be valid identifier.
 */
#define TEST(s, t) \
    void ZZT_TESTNAME(s, t)(struct zzt_test_state_s * zzt_test_state); \
    static struct zzt_test_s ZZT_TESTINFO(s, t) = { \
        ZZT_TESTNAME(s, t), #s, #s "." #t, NULL, NULL, NULL}; \
    void ZZT_TESTNAME(s, t)(struct zzt_test_state_s * zzt_test_state)

/**
 * @brief Add a test to a test suite.  Must be placed inside SUITE block.
 */
#define SUITE_TEST(s, t) \
    do { \
        struct zzt_test_suite_s *suite = &ZZT_SUITEINFO(s); \
        if (suite->head == NULL) { \
            suite->suite_name = #s; \
            suite->head = &ZZT_TESTINFO(s, t); \
            suite->tail = suite->head; \
            suite->tests_count = 1; \
        } else { \
            suite->tail->next = &ZZT_TESTINFO(s, t); \
            suite->tail = suite->tail->next; \
            suite->tests_count += 1; \
        } \
    } while (0)

/**
 * Expect expression t evaluates to non-zero or true value.
 */
#define EXPECT_TRUE(t) \
    do { \
        if (!(t)) { \
            zzt_fail(zzt_test_state, __FILE__, __LINE__, \
                "Value of: " #t "\n  Actual: false\nExpected: true"); \
        } else { \
            zzt_pass(zzt_test_state); \
        } \
    } while (0)

/**
 * Assert expression t evaluates to non-zero or true value, exit early if
 * failed.
 */
#define ASSERT_TRUE(t) \
    do { \
        if (!(t)) { \
            zzt_fail(zzt_test_state, __FILE__, __LINE__, \
                "Value of: " #t "\n  Actual: false\nExpected: true"); \
            return; \
        } else { \
            zzt_pass(zzt_test_state); \
        } \
    } while (0)

/**
 * Expect expression t evaluates to zero or false.
 */
#define EXPECT_FALSE(t) \
    do { \
        if ((t)) { \
            zzt_fail(zzt_test_state, __FILE__, __LINE__, \
                "Value of: " #t "\n  Actual: true\nExpected: false"); \
        } else { \
            zzt_pass(zzt_test_state); \
        } \
    } while (0)

/**
 * Assert expression t evaluates to zero or false, exit early if failed.
 */
#define ASSERT_FALSE(t) \
    do { \
        if ((t)) { \
            zzt_fail(zzt_test_state, __FILE__, __LINE__, \
                "Value of: " #t "\n  Actual: true\nExpected: false"); \
            return; \
        } else { \
            zzt_pass(zzt_test_state); \
        } \
    } while (0)

/**
 * @brief Expect l == r as a boolean.
 */
#define EXPECT_BOOLEQ(l, r) \
    do { \
        ZZT_EXPECT_BOOL(ZZT_CMP_EQ, l, r); \
    } while (0)

/**
 * @brief Assert l == r as a boolean, exit early if failed.
 */
#define ASSERT_BOOLEQ(l, r) \
    do { \
        if (!ZZT_EXPECT_BOOL(ZZT_CMP_EQ, l, r)) { \
            return; \
        } \
    } while (0)

/**
 * @brief Expect l != r as a boolean.
 */
#define EXPECT_BOOLNE(l, r) \
    do { \
        ZZT_EXPECT_BOOL(ZZT_CMP_NE, l, r); \
    } while (0)

/**
 * @brief Assert l != r as a boolean, exit early if failed.
 */
#define ASSERT_BOOLNE(l, r) \
    do { \
        if (!ZZT_EXPECT_BOOL(ZZT_CMP_NE, l, r)) { \
            return; \
        } \
    } while (0)

/**
 * @brief Expect l == r as a char.
 */
#define EXPECT_CHAREQ(l, r) \
    do { \
        ZZT_EXPECT_CHAR(ZZT_CMP_EQ, l, r); \
    } while (0)

/**
 * @brief Assert l == r as a char, exit early if failed.
 */
#define ASSERT_CHAREQ(l, r) \
    do { \
        if (!ZZT_EXPECT_CHAR(ZZT_CMP_EQ, l, r)) { \
            return; \
        } \
    } while (0)

/**
 * @brief Expect l != r as a char.
 */
#define EXPECT_CHARNE(l, r) \
    do { \
        ZZT_EXPECT_CHAR(ZZT_CMP_NE, l, r); \
    } while (0)

/**
 * @brief Assert l != r as a char, exit early if failed.
 */
#define ASSERT_CHARNE(l, r) \
    do { \
        if (!ZZT_EXPECT_CHAR(ZZT_CMP_NE, l, r)) { \
            return; \
        } \
    } while (0)

/**
 * @brief Expect l < r as a char.
 */
#define EXPECT_CHARLT(l, r) \
    do { \
        ZZT_EXPECT_CHAR(ZZT_CMP_LT, l, r); \
    } while (0)

/**
 * @brief Assert l < r as a char, exit early if failed.
 */
#define ASSERT_CHARLT(l, r) \
    do { \
        if (!ZZT_EXPECT_CHAR(ZZT_CMP_LT, l, r)) { \
            return; \
        } \
    } while (0)

/**
 * @brief Expect l <= r as a char.
 */
#define EXPECT_CHARLE(l, r) \
    do { \
        ZZT_EXPECT_CHAR(ZZT_CMP_LE, l, r); \
    } while (0)

/**
 * @brief Assert l <= r as a char, exit early if failed.
 */
#define ASSERT_CHARLE(l, r) \
    do { \
        if (!ZZT_EXPECT_CHAR(ZZT_CMP_LE, l, r)) { \
            return; \
        } \
    } while (0)

/**
 * @brief Expect l > r as a char.
 */
#define EXPECT_CHARGT(l, r) \
    do { \
        ZZT_EXPECT_CHAR(ZZT_CMP_GT, l, r); \
    } while (0)

/**
 * @brief Assert l > r as a char, exit early if failed.
 */
#define ASSERT_CHARGT(l, r) \
    do { \
        if (!ZZT_EXPECT_CHAR(ZZT_CMP_GT, l, r)) { \
            return; \
        } \
    } while (0)

/**
 * @brief Expect l >= r as a char.
 */
#define EXPECT_CHARGE(l, r) \
    do { \
        ZZT_EXPECT_CHAR(ZZT_CMP_GE, l, r); \
    } while (0)

/**
 * @brief Assert l >= r as a char, exit early if failed.
 */
#define ASSERT_CHARGE(l, r) \
    do { \
        if (!ZZT_EXPECT_CHAR(ZZT_CMP_GE, l, r)) { \
            return; \
        } \
    } while (0)

/**
 * @brief Expect l == r as any signed integral type.
 */
#define EXPECT_INTEQ(l, r) \
    do { \
        ZZT_EXPECT_INT(ZZT_CMP_EQ, l, r); \
    } while (0)

/**
 * @brief Assert l == r as any signed integral type, exit early if failed.
 */
#define ASSERT_INTEQ(l, r) \
    do { \
        if (!ZZT_EXPECT_INT(ZZT_CMP_EQ, l, r)) { \
            return; \
        } \
    } while (0)

/**
 * @brief Expect l != r as any signed integral type.
 */
#define EXPECT_INTNE(l, r) \
    do { \
        ZZT_EXPECT_INT(ZZT_CMP_NE, l, r); \
    } while (0)

/**
 * @brief Assert l != r as any signed integral type, exit early if failed.
 */
#define ASSERT_INTNE(l, r) \
    do { \
        if (!ZZT_EXPECT_INT(ZZT_CMP_NE, l, r)) { \
            return; \
        } \
    } while (0)

/**
 * @brief Expect l < r as any signed integral type.
 */
#define EXPECT_INTLT(l, r) \
    do { \
        ZZT_EXPECT_INT(ZZT_CMP_LT, l, r); \
    } while (0)

/**
 * @brief Assert l < r as any signed integral type, exit early if failed.
 */
#define ASSERT_INTLT(l, r) \
    do { \
        if (!ZZT_EXPECT_INT(ZZT_CMP_LT, l, r)) { \
            return; \
        } \
    } while (0)

/**
 * @brief Expect l <= r as any signed integral type.
 */
#define EXPECT_INTLE(l, r) \
    do { \
        ZZT_EXPECT_INT(ZZT_CMP_LE, l, r); \
    } while (0)

/**
 * @brief Assert l <= r as any signed integral type, exit early if failed.
 */
#define ASSERT_INTLE(l, r) \
    do { \
        if (!ZZT_EXPECT_INT(ZZT_CMP_LE, l, r)) { \
            return; \
        } \
    } while (0)

/**
 * @brief Expect l > r as any signed integral type.
 */
#define EXPECT_INTGT(l, r) \
    do { \
        ZZT_EXPECT_INT(ZZT_CMP_GT, l, r); \
    } while (0)

/**
 * @brief Assert l > r as any signed integral type, exit early if failed.
 */
#define ASSERT_INTGT(l, r) \
    do { \
        if (!ZZT_EXPECT_INT(ZZT_CMP_GT, l, r)) { \
            return; \
        } \
    } while (0)

/**
 * @brief Expect l >= r as any signed integral type.
 */
#define EXPECT_INTGE(l, r) \
    do { \
        ZZT_EXPECT_INT(ZZT_CMP_GE, l, r); \
    } while (0)

/**
 * @brief Assert l >= r as any signed integral type, exit early if failed.
 */
#define ASSERT_INTGE(l, r) \
    do { \
        if (!ZZT_EXPECT_INT(ZZT_CMP_GE, l, r)) { \
            return; \
        } \
    } while (0)

/**
 * @brief Expect l == r as any unsigned integral type.
 */
#define EXPECT_UINTEQ(l, r) \
    do { \
        ZZT_EXPECT_UINT(ZZT_CMP_EQ, l, r); \
    } while (0)

/**
 * @brief Assert l == r as any unsigned integral type, exit early if failed.
 */
#define ASSERT_UINTEQ(l, r) \
    do { \
        if (!ZZT_EXPECT_UINT(ZZT_CMP_EQ, l, r)) { \
            return; \
        } \
    } while (0)

/**
 * @brief Expect l != r as any unsigned integral type.
 */
#define EXPECT_UINTNE(l, r) \
    do { \
        ZZT_EXPECT_UINT(ZZT_CMP_NE, l, r); \
    } while (0)

/**
 * @brief Assert l != r as any unsigned integral type, exit early if failed.
 */
#define ASSERT_UINTNE(l, r) \
    do { \
        if (!ZZT_EXPECT_UINT(ZZT_CMP_NE, l, r)) { \
            return; \
        } \
    } while (0)

/**
 * @brief Expect l < r as any unsigned integral type.
 */
#define EXPECT_UINTLT(l, r) \
    do { \
        ZZT_EXPECT_UINT(ZZT_CMP_LT, l, r); \
    } while (0)

/**
 * @brief Assert l < r as any unsigned integral type, exit early if failed.
 */
#define ASSERT_UINTLT(l, r) \
    do { \
        if (!ZZT_EXPECT_UINT(ZZT_CMP_LT, l, r)) { \
            return; \
        } \
    } while (0)

/**
 * @brief Expect l <= r as any unsigned integral type.
 */
#define EXPECT_UINTLE(l, r) \
    do { \
        ZZT_EXPECT_UINT(ZZT_CMP_LE, l, r); \
    } while (0)

/**
 * @brief Assert l <= r as any unsigned integral type, exit early if failed.
 */
#define ASSERT_UINTLE(l, r) \
    do { \
        if (!ZZT_EXPECT_UINT(ZZT_CMP_LE, l, r)) { \
            return; \
        } \
    } while (0)

/**
 * @brief Expect l > r as any unsigned integral type.
 */
#define EXPECT_UINTGT(l, r) \
    do { \
        ZZT_EXPECT_UINT(ZZT_CMP_GT, l, r); \
    } while (0)

/**
 * @brief Assert l > r as any unsigned integral type, exit early if failed.
 */
#define ASSERT_UINTGT(l, r) \
    do { \
        if (!ZZT_EXPECT_UINT(ZZT_CMP_GT, l, r)) { \
            return; \
        } \
    } while (0)

/**
 * @brief Expect l >= r as any unsigned integral type.
 */
#define EXPECT_UINTGE(l, r) \
    do { \
        ZZT_EXPECT_UINT(ZZT_CMP_GE, l, r); \
    } while (0)

/**
 * @brief Assert l >= r as any unsigned integral type, exit early if failed.
 */
#define ASSERT_UINTGE(l, r) \
    do { \
        if (!ZZT_EXPECT_UINT(ZZT_CMP_GE, l, r)) { \
            return; \
        } \
    } while (0)

/**
 * @brief Expect l == r as any unsigned integral type, hex output.
 */
#define EXPECT_XINTEQ(l, r) \
    do { \
        ZZT_EXPECT_XINT(ZZT_CMP_EQ, l, r); \
    } while (0)

/**
 * @brief Assert l == r as any unsigned integral type, hex output, exit early
 *        if failed.
 */
#define ASSERT_XINTEQ(l, r) \
    do { \
        if (!ZZT_EXPECT_XINT(ZZT_CMP_EQ, l, r)) { \
            return; \
        } \
    } while (0)

/**
 * @brief Expect l != r as any unsigned integral type, hex output.
 */
#define EXPECT_XINTNE(l, r) \
    do { \
        ZZT_EXPECT_XINT(ZZT_CMP_NE, l, r); \
    } while (0)

/**
 * @brief Assert l != r as any unsigned integral type, hex output, exit early
 *        if failed.
 */
#define ASSERT_XINTNE(l, r) \
    do { \
        if (!ZZT_EXPECT_XINT(ZZT_CMP_NE, l, r)) { \
            return; \
        } \
    } while (0)

/**
 * @brief Expect l < r as any unsigned integral type, hex output.
 */
#define EXPECT_XINTLT(l, r) \
    do { \
        ZZT_EXPECT_XINT(ZZT_CMP_LT, l, r); \
    } while (0)

/**
 * @brief Assert l < r as any unsigned integral type, hex output, exit early
 *        if failed.
 */
#define ASSERT_XINTLT(l, r) \
    do { \
        if (!ZZT_EXPECT_XINT(ZZT_CMP_LT, l, r)) { \
            return; \
        } \
    } while (0)

/**
 * @brief Expect l <= r as any unsigned integral type, hex output.
 */
#define EXPECT_XINTLE(l, r) \
    do { \
        ZZT_EXPECT_XINT(ZZT_CMP_LE, l, r); \
    } while (0)

/**
 * @brief Assert l <= r as any unsigned integral type, hex output, exit early
 *        if failed.
 */
#define ASSERT_XINTLE(l, r) \
    do { \
        if (!ZZT_EXPECT_XINT(ZZT_CMP_LE, l, r)) { \
            return; \
        } \
    } while (0)

/**
 * @brief Expect l > r as any unsigned integral type, hex output.
 */
#define EXPECT_XINTGT(l, r) \
    do { \
        ZZT_EXPECT_XINT(ZZT_CMP_GT, l, r); \
    } while (0)

/**
 * @brief Assert l > r as any unsigned integral type, hex output, exit early
 *        if failed.
 */
#define ASSERT_XINTGT(l, r) \
    do { \
        if (!ZZT_EXPECT_XINT(ZZT_CMP_GT, l, r)) { \
            return; \
        } \
    } while (0)

/**
 * @brief Expect l >= r as any unsigned integral type, hex output.
 */
#define EXPECT_XINTGE(l, r) \
    do { \
        ZZT_EXPECT_XINT(ZZT_CMP_GE, l, r); \
    } while (0)

/**
 * @brief Assert l >= r as any unsigned integral type, hex output, exit early
 *        if failed.
 */
#define ASSERT_XINTGE(l, r) \
    do { \
        if (!ZZT_EXPECT_XINT(ZZT_CMP_GE, l, r)) { \
            return; \
        } \
    } while (0)

/**
 * @brief Expect l and r are identical C strings.
 */
#define EXPECT_STREQ(l, r) \
    do { \
        ZZT_EXPECT_STR(ZZT_CMP_EQ, l, r); \
    } while (0)

/**
 * @brief Assert l and r are identical C strings, exit early if failed.
 */
#define ASSERT_STREQ(l, r) \
    do { \
        if (!ZZT_EXPECT_STR(ZZT_CMP_EQ, l, r)) { \
            return; \
        } \
    } while (0)

/**
 * @brief Expect l and r are different C strings.
 */
#define EXPECT_STRNE(l, r) \
    do { \
        ZZT_EXPECT_STR(ZZT_CMP_NE, l, r); \
    } while (0)

/**
 * @brief Assert l and r are different C strings, exit early if failed.
 */
#define ASSERT_STRNE(l, r) \
    do { \
        if (!ZZT_EXPECT_STR(ZZT_CMP_NE, l, r)) { \
            return; \
        } \
    } while (0)

/**
 * @brief Add a failure, without a return.
 */
#define ADD_FAILURE() \
    do { \
        zzt_fail(zzt_test_state, __FILE__, __LINE__, "Failure"); \
    } while (0)

/**
 * @brief Signal failure.
 */
#define FAIL() \
    do { \
        zzt_fail(zzt_test_state, __FILE__, __LINE__, "Failure"); \
        return; \
    } while (0)

/**
 * @brief Signal skip.
 */
#define SKIP() \
    do { \
        zzt_skip(zzt_test_state); \
        return; \
    } while (0)

/**
 * @brief Add suite of tests to be run when RUN_TESTS is called.
 */
#define ADD_TEST_SUITE(s) \
    do { \
        ZZT_SUITENAME(s)(); \
        zzt_add_test_suite(&ZZT_SUITEINFO(s)); \
    } while (0)

/**
 * @brief Run all tests and return code which can be returned from main().
 */
#define RUN_TESTS() (zzt_run_all())

void
zzt_pass(struct zzt_test_state_s *state);

void
zzt_skip(struct zzt_test_state_s *state);

void
zzt_fail(struct zzt_test_state_s *state, const char *file, unsigned long line,
    const char *msgstr);

ZZT_BOOL
zzt_cmp_int(struct zzt_test_state_s *state, enum zzt_fmt_e fmt,
    enum zzt_cmp_e cmp, ZZT_INTMAX l, ZZT_INTMAX r, const char *ls,
    const char *rs, const char *file, unsigned long line);

ZZT_BOOL
zzt_cmp_uint(struct zzt_test_state_s *state, enum zzt_fmt_e fmt,
    enum zzt_cmp_e cmp, ZZT_UINTMAX l, ZZT_UINTMAX r, const char *ls,
    const char *rs, const char *file, unsigned long line);

ZZT_BOOL
zzt_cmp_str(struct zzt_test_state_s *state, enum zzt_fmt_e fmt,
    enum zzt_cmp_e cmp, const char *l, const char *r, const char *ls,
    const char *rs, const char *file, unsigned long line);

void
zzt_add_test_suite(struct zzt_test_suite_s *suite);

int
zzt_run_all(void);

#ifdef __cplusplus
}
#endif

#endif /* !defined(INCLUDE_ZZTEST_H) */
