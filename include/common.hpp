/**
 * \file common.hpp
 * Utility macros.
 */

#ifndef COMMON_H
#define COMMON_H

#if (defined(unix) || defined(__unix__) || defined(__unix) || defined(__APPLE__) && defined(__MACH__))
/**
 * Defined if running in a sensible OS.
 */
#define SENSIBLE_OS
#endif

#endif

/**
 * Macro for minimum of a and b.
 */
#define MIN(a, b) ((a) < (b) ? (a) : (b))
/**
 * Macro for maximum of a and b.
 */
#define MAX(a, b) ((a) > (b) ? (a) : (b))
/**
 * Macro for absolute value of a.
 */
#define ABS(a) ((a) >= 0 ? (a) : (-(a)))

#endif