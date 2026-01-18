/*
 * zztest - A test framework for crufty compilers.
 * Copyright (c) 2024 Lexi Mayfield
 *
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#include "zztest.h"

#if defined(_MSC_VER)
#define _CRT_SECURE_NO_WARNINGS /* Say the line, Bart! */
#endif

#if defined(ZZTEST_CONFIG_PRINTF)
#define ZZT_PRINTF ZZTEST_CONFIG_PRINTF
#else
#define ZZT_PRINTF printf
#endif

#if defined(_WIN32)
#pragma comment(lib, "WinMM.Lib") /* Timer functions */
#include <Windows.h>
#elif defined(__unix__)
#include <sys/time.h> /* Timer functions. */
static struct timeval g_cTimeStart;
#endif

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#define ZZTLOG_H1 "[==========]"
#define ZZTLOG_H2 "[----------]"
#define ZZTLOG_RUN "[ RUN      ]"
#define ZZTLOG_OK "[       OK ]"
#define ZZTLOG_SKIPPED "[  SKIPPED ]"
#define ZZTLOG_FAILED "[  FAILED  ]"
#define ZZTLOG_PASSED "[  PASSED  ]"

/******************************************************************************/

struct zzt_test_state_s {
    struct zzt_test_s *test;
    int passed;
    int failed;
    int skipped;
};

static char g_scopedTrace[128];
static const char *g_cmpStrings[] = {"==", "!=", "<", "<=", ">", ">="};
static unsigned long g_testsCount;
static struct zzt_test_suite_s *g_suitesHead;
static struct zzt_test_suite_s *g_suitesTail;
static unsigned long g_suitesCount;
static struct zzt_test_s *g_testFailHead;
static struct zzt_test_s *g_testFailTail;
static struct zzt_test_s *g_testSkipHead;
static struct zzt_test_s *g_testSkipTail;

/**
 * @brief Return time point with ms resolution.
 *
 * @details This is a compatible timer, not an accurate one.  We're making
 *          a test suite, not a benchmark.
 */
static unsigned long
zzt_ms(void)
{
#if defined(_WIN32)
    return timeGetTime();
#elif defined(__unix__)
    unsigned long ms;
    struct timeval now;
    gettimeofday(&now, NULL);
    ms = (now.tv_sec - g_cTimeStart.tv_sec) * 1000 +
         (now.tv_usec - g_cTimeStart.tv_usec) / 1000;
    return ms;
#else
    return 0; /* oh well... */
#endif
}

#if defined(__GNUC__)
#define zzt_vsprintf(buf, buflen, fmt, va) vsnprintf(buf, buflen, fmt, va)
#elif defined(_MSC_VER) /* FIXME: When was this added? */
#define zzt_vsprintf(buf, buflen, fmt, va) \
    do { \
        _vsnprintf(buf, buflen, fmt, va); \
        buf[buflen - 1] = '\0'; \
    } while (0)
#else
#define zzt_vsprintf(buf, buflen, fmt, va) \
    do { \
        (void)buflen; \
        vsprintf(buf, fmt, va); \
    } while (0)
#endif

/**
 * @brief Use the safest vsprintf we have available.
 *
 * @param buf Buffer to write to.
 * @param buflen Length of buffer.
 * @param fmt Format string.
 * @param ... Format parameters.
 */
static void
zzt_sprintf(char *buf, unsigned buflen, const char *fmt, ...)
{
    va_list va;
    va_start(va, fmt);

    zzt_vsprintf(buf, buflen, fmt, va);

    va_end(va);
}

/**
 * @brief Turn a string into a typical quoted string literal.
 *
 * @param buf Buffer to write to.
 * @param buflen Length of destination buffer.
 * @param str Input string to convert.
 */
static void
zzt_stringify(char *buf, unsigned long buflen, const char *str)
{
    ZZT_BOOL partial = ZZT_FALSE;
    const char *cur = str;
    char *w = buf;
    char *end = buf + buflen;
#define REMAIN_() (end - w)
#define WRITE_(c) (*w++ = (c))

    if (buflen == 0) {
        return;
    } else if (REMAIN_() < 5) {
        /* Needs to contain at least "...\0 */
        WRITE_('\0');
        return;
    }

    WRITE_('\"');
    while (*cur != '\0') {
        if (*cur == '\t' || *cur == '\n' || *cur == '\r' || *cur == '\\') {
            if (REMAIN_() < 3) {
                partial = ZZT_TRUE;
                break;
            }

            WRITE_('\\');
            if (*cur == '\t') {
                WRITE_('t');
            } else if (*cur == '\n') {
                WRITE_('n');
            } else if (*cur == '\r') {
                WRITE_('r');
            } else if (*cur == '\\') {
                WRITE_('\\');
            }
        } else if (*cur >= ' ' && *cur <= '~') {
            if (REMAIN_() < 2) {
                partial = ZZT_TRUE;
                break;
            }
            WRITE_(*cur);
        } else {
            if (REMAIN_() < 5) {
                partial = ZZT_TRUE;
                break;
            }

            zzt_sprintf(w, 5, "\\x%02x", ((unsigned)*cur) & 0xFF);
            w += 4;
        }

        cur += 1;
    }

    if (partial) {
        w = end - 5;
        WRITE_('.');
        WRITE_('.');
        WRITE_('.');
        WRITE_('\0');
        return;
    }

    WRITE_('\"');
    WRITE_('\0');
#undef REMAIN_
#undef WRITE_
}

/**
 * @brief Print a value based on its desired format.
 *
 * @param buf Buffer to write to.
 * @param buflen Length of buffer.
 * @param fmt Format type.
 * @param v Pointer to underlying value.
 */
static void
zzt_printv(char *buf, ZZT_UINTMAX buflen, enum zzt_fmt_e fmt, const void *v)
{
    switch (fmt) {
    case ZZT_FMT_BOOL: {
        const int boolean = *((int *)v);
        if (boolean) {
            zzt_sprintf(buf, buflen, "true");
        } else {
            zzt_sprintf(buf, buflen, "false");
        }
        break;
    }
    case ZZT_FMT_CHAR: {
        const char ch = *((char *)v);
        if (ch == '\0') {
            zzt_sprintf(buf, buflen, "'\\0'", ch);
        } else if (ch == '\t') {
            zzt_sprintf(buf, buflen, "'\\t'", ch);
        } else if (ch == '\n') {
            zzt_sprintf(buf, buflen, "'\\n'", ch);
        } else if (ch == '\r') {
            zzt_sprintf(buf, buflen, "'\\r'", ch);
        } else if (ch == '\\') {
            zzt_sprintf(buf, buflen, "'\\\\'", ch);
        } else if (ch >= ' ' && ch <= '~') {
            zzt_sprintf(buf, buflen, "'%c'", ch);
        } else {
            zzt_sprintf(buf, buflen, "'\\x%02x'", ((unsigned)ch) & 0xFF);
        }
        break;
    }
    case ZZT_FMT_INT:
        zzt_sprintf(buf, buflen, "%" ZZT_PRIiMAX, *((ZZT_INTMAX *)v));
        break;
    case ZZT_FMT_UINT:
        zzt_sprintf(buf, buflen, "%" ZZT_PRIuMAX, *((ZZT_UINTMAX *)v));
        break;
    case ZZT_FMT_XINT:
        zzt_sprintf(buf, buflen, "0x%" ZZT_PRIuMAX, *((ZZT_UINTMAX *)v));
        break;
    case ZZT_FMT_STR: zzt_stringify(buf, buflen, (const char *)v); break;
    default: return;
    }
}

/**
 * @brief Print a test error message.
 *
 * @param fmt How to format the result.
 * @param cmp The comparison which was done.
 * @param l Pointer to the left-hand value.
 * @param r Pointer to the right-hand value.
 * @param ls String form of left-hand value.
 * @param rs String form of right-hand value.
 * @param file Filename where test failed.
 * @param line Line number where test failed.
 */
static void
zzt_printerr(enum zzt_fmt_e fmt, enum zzt_cmp_e cmp, const void *l,
    const void *r, const char *ls, const char *rs, const char *file,
    unsigned long line)
{
    char lbuf[64] = {0};
    char rbuf[64] = {0};

    zzt_printv(lbuf, sizeof(lbuf), fmt, l);
    zzt_printv(rbuf, sizeof(rbuf), fmt, r);
    if (fmt != ZZT_FMT_STR) {
        ZZT_PRINTF("%s(%lu): error: Expected %s %s %s, actual %s vs %s\n", file,
            line, ls, g_cmpStrings[cmp], rs, lbuf, rbuf);
    } else {
        ZZT_PRINTF("%s(%lu): error: Expected equality of these values:\n", file,
            line);
        ZZT_PRINTF("  %s\n", ls);
        if (strcmp(lbuf, ls)) {
            ZZT_PRINTF("    Which is: %s\n", lbuf);
        }

        ZZT_PRINTF("  %s\n", rs);
        if (strcmp(rbuf, rs)) {
            ZZT_PRINTF("    Which is: %s\n", rbuf);
        }
    }

    if (g_scopedTrace[0] != '\0') {
        ZZT_PRINTF("Scoped trace: %s\n\n", g_scopedTrace);
    } else {
        ZZT_PRINTF("\n");
    }
}

/**
 * @brief Add a test to our list of failed tests.
 */
static void
zzt_add_fail(struct zzt_test_s *test)
{
    if (g_testFailHead == NULL) {
        g_testFailHead = test;
        g_testFailTail = test;
    } else {
        g_testFailTail->next_fail = test;
        g_testFailTail = test;
    }
}

/**
 * @brief Add a test to our list of skipped tests.
 */
static void
zzt_add_skip(struct zzt_test_s *test)
{
    if (g_testSkipHead == NULL) {
        g_testSkipHead = test;
        g_testSkipTail = test;
    } else {
        g_testSkipTail->next_skip = test;
        g_testSkipTail = test;
    }
}

/******************************************************************************/

void
zzt_pass(struct zzt_test_state_s *state)
{
    state->passed += 1;
}

/******************************************************************************/

void
zzt_skip(struct zzt_test_state_s *state)
{
    state->skipped += 1;
}

/******************************************************************************/

void
zzt_fail(struct zzt_test_state_s *state, const char *file, unsigned long line,
    const char *msgstr)
{
    ZZT_PRINTF("%s(%lu): error: %s\n", file, line, msgstr);
    if (g_scopedTrace[0] != '\0') {
        ZZT_PRINTF("Scoped trace: %s\n\n", g_scopedTrace);
    } else {
        ZZT_PRINTF("\n");
    }

    state->failed += 1;
}

/******************************************************************************/

ZZT_BOOL
zzt_cmp_int(struct zzt_test_state_s *state, enum zzt_fmt_e fmt,
    enum zzt_cmp_e cmp, ZZT_INTMAX l, ZZT_INTMAX r, const char *ls,
    const char *rs, const char *file, unsigned long line)
{
    ZZT_BOOL isEqual = ZZT_FALSE;

    switch (cmp) {
    case ZZT_CMP_EQ: isEqual = l == r; break;
    case ZZT_CMP_NE: isEqual = l != r; break;
    case ZZT_CMP_LT: isEqual = l < r; break;
    case ZZT_CMP_LE: isEqual = l <= r; break;
    case ZZT_CMP_GT: isEqual = l > r; break;
    case ZZT_CMP_GE: isEqual = l >= r; break;
    }

    if (isEqual) {
        state->passed += 1;
        return ZZT_TRUE;
    }

    state->failed += 1;
    zzt_printerr(fmt, cmp, &l, &r, ls, rs, file, line);
    return ZZT_FALSE;
}

/******************************************************************************/

ZZT_BOOL
zzt_cmp_uint(struct zzt_test_state_s *state, enum zzt_fmt_e fmt,
    enum zzt_cmp_e cmp, ZZT_UINTMAX l, ZZT_UINTMAX r, const char *ls,
    const char *rs, const char *file, unsigned long line)
{
    ZZT_BOOL isEqual = ZZT_FALSE;

    switch (cmp) {
    case ZZT_CMP_EQ: isEqual = l == r; break;
    case ZZT_CMP_NE: isEqual = l != r; break;
    case ZZT_CMP_LT: isEqual = l < r; break;
    case ZZT_CMP_LE: isEqual = l <= r; break;
    case ZZT_CMP_GT: isEqual = l > r; break;
    case ZZT_CMP_GE: isEqual = l >= r; break;
    }

    if (isEqual) {
        state->passed += 1;
        return ZZT_TRUE;
    }

    state->failed += 1;
    zzt_printerr(fmt, cmp, &l, &r, ls, rs, file, line);
    return ZZT_FALSE;
}

/******************************************************************************/

ZZT_BOOL
zzt_cmp_str(struct zzt_test_state_s *state, enum zzt_fmt_e fmt,
    enum zzt_cmp_e cmp, const char *l, const char *r, const char *ls,
    const char *rs, const char *file, unsigned long line)
{
    ZZT_BOOL isEqual = ZZT_FALSE;

    switch (cmp) {
    case ZZT_CMP_EQ: isEqual = 0 == strcmp(l, r); break;
    case ZZT_CMP_NE: isEqual = 0 != strcmp(l, r); break;
    }

    if (isEqual) {
        state->passed += 1;
        return ZZT_TRUE;
    }

    state->failed += 1;
    zzt_printerr(fmt, cmp, l, r, ls, rs, file, line);
    return ZZT_FALSE;
}

/******************************************************************************/

void
zzt_scoped_trace(const char *fmt, ...)
{
    va_list va;
    va_start(va, fmt);

    zzt_vsprintf(g_scopedTrace, sizeof(g_scopedTrace), fmt, va);

    va_end(va);
}

/******************************************************************************/

void
zzt_add_test_suite(struct zzt_test_suite_s *suite)
{
    if (g_suitesHead == NULL) {
        g_testsCount = suite->tests_count;
        g_suitesHead = suite;
        g_suitesTail = g_suitesHead;
        g_suitesCount = 1;
    } else {
        g_testsCount += suite->tests_count;
        g_suitesTail->next = suite;
        g_suitesTail = g_suitesTail->next;
        g_suitesCount += 1;
    }
}

/******************************************************************************/

int
zzt_run_all(void)
{
    unsigned long passed = 0, failed = 0, skipped = 0;
    unsigned long startAllMs = 0, allMs = 0;
    struct zzt_test_suite_s *suite = g_suitesHead;
    struct zzt_test_s *test = NULL;

#if defined(_WIN32)
    /* Set timer resolution to 1ms. */
    timeBeginPeriod(1);
#endif

    ZZT_PRINTF(ZZTLOG_H1 " Running %lu tests from %lu test suites.\n",
        g_testsCount, g_suitesCount);
    startAllMs = zzt_ms();

    for (; suite; suite = suite->next) {
        unsigned long startSuiteMs = 0, suiteMs = 0;

        ZZT_PRINTF(ZZTLOG_H2 " %lu tests from %s\n", suite->tests_count,
            suite->suite_name);
        startSuiteMs = zzt_ms();

        test = suite->head;
        for (; test; test = test->next) {
            const char *result = "";
            unsigned long startTestMs = 0, testMs = 0;
            struct zzt_test_state_s state;

            ZZT_PRINTF(ZZTLOG_RUN " %s\n", test->test_name);
            state.test = test;
            state.passed = 0;
            state.failed = 0;
            state.skipped = 0;
            g_scopedTrace[0] = '\0';

            startTestMs = zzt_ms();
            test->func(&state);
            testMs = zzt_ms() - startTestMs;

            if (state.failed != 0) {
                result = ZZTLOG_FAILED;
                zzt_add_fail(test);
                failed += 1;
            } else if (state.skipped != 0) {
                result = ZZTLOG_SKIPPED;
                zzt_add_skip(test);
                skipped += 1;
            } else {
                result = ZZTLOG_OK;
                passed += 1;
            }

            if (testMs) {
                ZZT_PRINTF("%s %s (%lu ms)\n", result, test->test_name, testMs);
            } else {
                ZZT_PRINTF("%s %s\n", result, test->test_name);
            }
        }

        suiteMs = zzt_ms() - startSuiteMs;
        if (suiteMs) {
            ZZT_PRINTF(ZZTLOG_H2 " %lu tests from %s (%lu ms total)\n\n",
                suite->tests_count, suite->suite_name, suiteMs);
        } else {
            ZZT_PRINTF(ZZTLOG_H2 " %lu tests from %s\n\n", suite->tests_count,
                suite->suite_name);
        }
    }

    allMs = zzt_ms() - startAllMs;
    if (allMs) {
        ZZT_PRINTF(ZZTLOG_H1
            " %lu tests from %lu test suites ran. (%lu ms total)\n",
            g_testsCount, g_suitesCount, allMs);
    } else {
        ZZT_PRINTF(ZZTLOG_H1 " %lu tests from %lu test suites ran.\n",
            g_testsCount, g_suitesCount);
    }

    ZZT_PRINTF(ZZTLOG_PASSED " %lu tests.\n", passed);

    if (skipped != 0) {
        ZZT_PRINTF(ZZTLOG_SKIPPED " %lu tests, listed below:\n", skipped);

        test = g_testSkipHead;
        for (; test; test = test->next_skip) {
            ZZT_PRINTF(ZZTLOG_SKIPPED " %s\n", test->test_name);
        }
    }

    if (failed != 0) {
        ZZT_PRINTF(ZZTLOG_FAILED " %lu tests, listed below:\n", failed);

        test = g_testFailHead;
        for (; test; test = test->next_fail) {
            ZZT_PRINTF(ZZTLOG_FAILED " %s\n", test->test_name);
        }
    }

    return failed != 0;
}
