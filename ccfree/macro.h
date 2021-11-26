/**
 * @file macro.h
 * @brief 常用宏的封装
 * @author ccfree.yin
 * @email 564628276@qq.com
 * @date 2019-06-01
 * @copyright Copyright (c) 2019年 ccfree.yin All rights reserved (www.ccfree.top)
 */
#ifndef __CCFREE_MACRO_H__
#define __CCFREE_MACRO_H__

#include <string.h>
#include <assert.h>
#include "log.h"
#include "util.h"

#if defined __GNUC__ || defined __llvm__
/// LIKCLY 宏的封装, 告诉编译器优化,条件大概率成立
#   define CCFREE_LIKELY(x)       __builtin_expect(!!(x), 1)
/// LIKCLY 宏的封装, 告诉编译器优化,条件大概率不成立
#   define CCFREE_UNLIKELY(x)     __builtin_expect(!!(x), 0)
#else
#   define CCFREE_LIKELY(x)      (x)
#   define CCFREE_UNLIKELY(x)      (x)
#endif

/// 断言宏封装
#define CCFREE_ASSERT(x) \
    if(CCFREE_UNLIKELY(!(x))) { \
        CCFREE_LOG_ERROR(CCFREE_LOG_ROOT()) << "ASSERTION: " #x \
            << "\nbacktrace:\n" \
            << ccfree::BacktraceToString(100, 2, "    "); \
        assert(x); \
    }

/// 断言宏封装
#define CCFREE_ASSERT2(x, w) \
    if(CCFREE_UNLIKELY(!(x))) { \
        CCFREE_LOG_ERROR(CCFREE_LOG_ROOT()) << "ASSERTION: " #x \
            << "\n" << w \
            << "\nbacktrace:\n" \
            << ccfree::BacktraceToString(100, 2, "    "); \
        assert(x); \
    }

#endif
