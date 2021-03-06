// -*- mode: c; tab-width: 8; indent-tabs-mode: 1; st-rulers: [70] -*-
// vim: ts=8 sw=8 ft=c noet
/**
 * @file decaf/common.h
 * @author Mike Hamburg
 *
 * @copyright
 *   Copyright (c) 2015 Cryptography Research, Inc.  \n
 *   Released under the MIT License.  See LICENSE.txt for license information.
 *
 * @brief Common utility headers for Decaf library.
 */

/**
 * The MIT License (MIT)
 * 
 * Copyright (c) 2011 Stanford University.
 * Copyright (c) 2014 Cryptography Research, Inc.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef __DECAF_COMMON_H__
#define __DECAF_COMMON_H__ 1

#include <stdint.h>
#include <sys/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Goldilocks' build flags default to hidden and stripping executables. */
/** @cond internal */
#if defined(DOXYGEN) && !defined(__attribute__)
#define __attribute__((x))
#endif
#define API_VIS __attribute__((visibility("default")))
#define NOINLINE  __attribute__((noinline))
#define WARN_UNUSED __attribute__((warn_unused_result))
#define NONNULL1 __attribute__((nonnull(1)))
#define NONNULL2 __attribute__((nonnull(1,2)))
#define NONNULL3 __attribute__((nonnull(1,2,3)))
#define NONNULL13 __attribute__((nonnull(1,3)))
#define NONNULL134 __attribute__((nonnull(1,3,4)))
#define NONNULL4 __attribute__((nonnull(1,2,3,4)))
#define NONNULL5 __attribute__((nonnull(1,2,3,4,5)))
#define INLINE inline __attribute__((always_inline))
#define UNUSED __attribute__((unused))
/** @endcond */

/* Internal word types.
 *
 * Somewhat tricky.  This could be decided separately per platform.  However,
 * the structs do need to be all the same size and alignment on a given
 * platform to support dynamic linking, since even if you header was built
 * with eg arch_neon, you might end up linking a library built with arch_arm32.
 */
#if (defined(__ILP64__) || defined(__amd64__) || defined(__x86_64__) || (((__UINT_FAST32_MAX__)>>30)>>30)) \
	 && !defined(DECAF_FORCE_32_BIT)
#define DECAF_WORD_BITS 64         /**< The number of bits in a word */
typedef uint64_t decaf_word_t;     /**< Word size for internal computations */
typedef int64_t decaf_sword_t;      /**< Signed word size for internal computations */
typedef uint64_t decaf_bool_t;     /**< "Boolean" type, will be set to all-zero or all-one (i.e. -1u) */
typedef __uint128_t decaf_dword_t; /**< Double-word size for internal computations */
typedef __int128_t decaf_dsword_t; /**< Signed double-word size for internal computations */
#else
#define DECAF_WORD_BITS 32          /**< The number of bits in a word */
typedef uint32_t decaf_word_t;      /**< Word size for internal computations */
typedef int32_t decaf_sword_t;      /**< Signed word size for internal computations */
typedef uint32_t decaf_bool_t;      /**< "Boolean" type, will be set to all-zero or all-one (i.e. -1u) */
typedef uint64_t decaf_dword_t;     /**< Double-word size for internal computations */
typedef uint64_t decaf_dsword_t;     /**< Signed double-word size for internal computations */
#endif
	
/** DECAF_TRUE = -1 so that DECAF_TRUE & x = x */
static const decaf_bool_t DECAF_TRUE = -(decaf_bool_t)1;

/** DECAF_FALSE = 0 so that DECAF_FALSE & x = 0 */
static const decaf_bool_t DECAF_FALSE = 0;

/** Another boolean type used to indicate success or failure. */
typedef enum {
	DECAF_SUCCESS = -1, /**< The operation succeeded. */
	DECAF_FAILURE = 0   /**< The operation failed. */
} decaf_error_t;


/** Return success if x is true */
static __inline__ __attribute__((unused,always_inline))
decaf_error_t
decaf_succeed_if(decaf_bool_t x) {
	return (decaf_error_t)x;
}

/** Return DECAF_TRUE iff x == DECAF_SUCCESS */
static __inline__ __attribute__((unused,always_inline))
decaf_bool_t
decaf_successful(decaf_error_t e) {
	decaf_dword_t w = ((decaf_word_t)e) ^  ((decaf_word_t)DECAF_SUCCESS);
	return (w-1)>>DECAF_WORD_BITS;
}
	
/** Overwrite data with zeros.  Uses memset_s if available. */
void decaf_bzero (
	void *data,
	size_t size
) NONNULL1 API_VIS;

/** Compare two buffers, returning DECAF_TRUE if they are equal. */
decaf_bool_t decaf_memeq (
	const void *data1,
	const void *data2,
	size_t size
) NONNULL2 WARN_UNUSED API_VIS;
	
#ifdef __cplusplus
} /* extern "C" */
#endif
	
#endif /* __DECAF_COMMON_H__ */
