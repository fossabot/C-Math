/* Source/Library/Differentiation Algorithms/derivNumericalAlgorithm.H
 *
 * ASL - Azadeh Scientific Library in C
 *
 * Copyright (C) 2019 Mohammad Mahdi Bgahbani Pourvahid
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
 *
 * 2. Altered source versions must be plainly marked as such, and must not be
 * misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any source distribution.
 */

#ifndef __ASL_DERIVNUMERICALALGORITHM_H__
#define __ASL_DERIVNUMERICALALGORITHM_H__

#define ASL_BACKWARD_DIFFERENCE 0
#define ASL_FORWARD_DIFFERENCE 1
#define ASL_CENTRAL_DIFFERENCE 2

#define ASL_SECOND_ORDER_ACCURACY 2
#define ASL_FOURTH_ORDER_ACCURACY 4
#define ASL_SIXTH_ORDER_ACCURACY 6
#define ASL_EIGHTH_ORDER_ACCURACY 8


double firstDerivative_1_arg(const char *expression, double x, double delta, int options);

/*
 * This function estimates a numerical derivative for a given one argument function at x
 *
 * ARGUMENTS:
 * expressions  the function expression, it must be a string array like "x^2+1"
 * x            the point where derivative must be evaluated
 * delta        the dx for getting numerical derivative
 * options      which algorithm to use {0: ASL_BACKWARD_DIFFERENCE, 1: ASL_FORWARD_DIFFERENCE, 2: ASL_CENTRAL_DIFFERENCE}
 *
 */

double centralFirstDerivative_1_arg(const char *expression, double x, double delta, int accuracy);
/*
 * This function estimates a numerical derivative for a given one argument function at point x
 * with "central" finite difference method
 *
 * ARGUMENTS:
 * expressions  the function expression, it must be a string array like "x^2+1"
 * x            the point where derivative must be evaluated
 * delta        the dx for getting numerical derivative
 * accuracy     defines the precision of algorithm, available accuracy order {2, 4, 6, 8}
 *
 * NOTE: it's good to use delta in range [1e-8, 1e-16] for this function
 * [double floating point accuracy IEEE 754-1985]
 *
 */

double centralSecondDerivative_1_arg(const char *expression, double x, double delta, int accuracy);
/*
 * accuracy     defines the precision of algorithm, available accuracy order {2, 4, 6, 8}
 *
 * NOTE: it's good to use delta in range [1e-8, 1e-16] for this function
 * [double floating point accuracy IEEE 754-1985]
 */

double centralThirdDerivative_1_arg(const char *expression, double x, double delta, int accuracy);
/*
 * NOTE: it's good to use delta in range [1e-3, 1e-5] for this function
 * [double floating point accuracy IEEE 754-1985]
 */

double centralFourthDerivative_1_arg(const char *expression, double x, double delta, int accuracy);
/*
 * accuracy     defines the precision of algorithm, available accuracy order {2, 4, 6}
 *
 * NOTE: it's good to use delta in range [1e-3, 1e-4] for this function
 * [double floating point accuracy IEEE 754-1985]
 */

double centralFifthDerivative_1_arg(const char *expression, double x, double delta, int accuracy);
/*
 * accuracy     defines the precision of algorithm, available accuracy order {2, 4, 6}
 *
 * NOTE: it's good to use delta in range [1e-1, 1e-3] for this function
 * [double floating point accuracy IEEE 754-1985]
 */

double centralSixthDerivative_1_arg(const char *expression, double x, double delta, int accuracy);
/*
 * accuracy     defines the precision of algorithm, available accuracy order {2, 4, 6}
 *
 * NOTE: it's good to use delta in range [1e-1, 1e-2] for this function
 * [double floating point accuracy IEEE 754-1985]
 */

#endif //__ASL_DERIVNUMERICALALGORITHM_H__
