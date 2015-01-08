/**
 * \file common.hpp
 * Utility macros.
 */

#ifndef COMMON_H
#define COMMON_H

#include <stdexcept>

/**
 * Defining will use alternative rendering and enables exceptions.
 */
//#define DEBUG

#if (defined(unix) || defined(__unix__) || defined(__unix) || \
        defined(__APPLE__) && defined(__MACH__))
/**
 * Defined if running in a sensible OS.
 */
#define SENSIBLE_OS
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
/**
 * Macro for the sign of a, 1 if >= +0, -1 if <= -0.
 */
#define SIGN(a) ((a) >= +0 ? 1 : -1)

#endif
