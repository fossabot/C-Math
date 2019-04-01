/* Source/Library/Util/Configurations/constants.h
 *
 * ASL - Azadeh Scientific Library in C
 *
 * Copyright (C) 2019 Mohammad Mahdi Bgahbani Pourvahid
 *
 * this header originally came from gsl_math.h and has been modified by me.
 * copyright notice for original source:
 *
 * Copyright (C) 1996, 1997, 1998, 1999, 2000, 2004, 2007 Gerard Jungman, Brian Gough
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 * claim that you wrote the original software. If you use this software
 * in a product, an acknowledgement in the product documentation would be
 * appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 * misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 */

#ifndef __ASL_CONSTANTS_H__
#define __ASL_CONSTANTS_H__

#ifndef ASL_EPSILON
#define ASL_EPSILON  0.0000000100000000                   /* 1e-8 epsilon */
#endif

#ifndef ASL_EPSILON4
#define ASL_EPSILON4 0.0001000000000000                   /* 1e-4 epsilon */
#endif

#ifndef ASL_EPSILON2
#define ASL_EPSILON2 0.0100000000000000                   /* 1e-2 epsilon */
#endif

#ifndef ASL_PHI
#define ASL_PHI      1.6180339887498949                   /* golden ratio */
#endif

#ifndef ASL_1_PHI
#define ASL_1_PHI    0.6180339887498949                   /* 1/(golden ratio) */
#endif

#ifndef ASL_E
#define ASL_E        2.71828182845904523536028747135      /* e */
#endif

#ifndef ASL_LOG2E
#define ASL_LOG2E    1.44269504088896340735992468100      /* log_2 (e) */
#endif

#ifndef ASL_LOG10E
#define ASL_LOG10E   0.43429448190325182765112891892      /* log_10 (e) */
#endif

#ifndef ASL_SQRT1_2
#define ASL_SQRT1_2  0.70710678118654752440084436210      /* sqrt(1/2) */
#endif

#ifndef ASL_SQRT2
#define ASL_SQRT2    1.41421356237309504880168872421      /* sqrt(2) */
#endif

#ifndef ASL_SQRT3
#define ASL_SQRT3    1.73205080756887729352744634151      /* sqrt(3) */
#endif

#ifndef ASL_SQRT5
#define ASL_SQRT5    2.23606797749979                     /* sqrt(5) */
#endif

#ifndef ASL_PI
#define ASL_PI       3.14159265358979323846264338328      /* pi */
#endif

#ifndef ASL_PI_2
#define ASL_PI_2     1.57079632679489661923132169164      /* pi/2 */
#endif

#ifndef ASL_PI_4
#define ASL_PI_4     0.78539816339744830961566084582     /* pi/4 */
#endif

#ifndef ASL_SQRTPI
#define ASL_SQRTPI   1.77245385090551602729816748334      /* sqrt(pi) */
#endif

#ifndef ASL_2_SQRTPI
#define ASL_2_SQRTPI 1.12837916709551257389615890312      /* 2/sqrt(pi) */
#endif

#ifndef ASL_1_PI
#define ASL_1_PI     0.31830988618379067153776752675      /* 1/pi */
#endif

#ifndef ASL_2_PI
#define ASL_2_PI     0.63661977236758134307553505349      /* 2/pi */
#endif

#ifndef ASL_LN10
#define ASL_LN10     2.30258509299404568401799145468      /* ln(10) */
#endif

#ifndef ASL_LN2
#define ASL_LN2      0.69314718055994530941723212146      /* ln(2) */
#endif

#ifndef ASL_LNPI
#define ASL_LNPI     1.14472988584940017414342735135      /* ln(pi) */
#endif

#ifndef ASL_EULER
#define ASL_EULER    0.57721566490153286060651209008      /* Euler constant */
#endif

#endif //__ASL_CONSTANTS_H__
