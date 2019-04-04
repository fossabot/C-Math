/* Source/Library/Function Root Finder Algorithms/cubicAlgorithm.c
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

#include "cubicAlgorithm.h"
#include "quadraticAlgorithm.h"
#include "../Util/util.h"
#include "../Util/Configurations/asl_configurations.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double *asl_cubic_real_root(double a, double b, double c, double d, int verbose, int *state) {
    /*
     * In algebra, a cubic function is a function of the form:
     * f ( x ) = a x 3 + b x 2 + c x + d
     * in which a is nonzero.
     *
     * Setting f(x) = 0 produces a cubic equation of the form "a x 3 + b x 2 + c x + d = 0".
     * The solutions of this equation are called roots of the polynomial f(x). If all of the coefficients a, b, c,
     * and d of the cubic equation are real numbers, then it has at least one real root (this is true for all
     * odd degree polynomials). All of the roots of the cubic equation can be found algebraically. (This is also
     * true of quadratic (second degree) or quartic (fourth degree) equations, but not of higher-degree equations,
     * by the Abel–Ruffini theorem.) The roots can also be found trigonometrically. Alternatively,
     * numerical approximations of the roots can be found using root-finding algorithms such as Newton's method.
     *
     * The coefficients do not need to be complex numbers. Much of what is covered below is valid for coefficients
     * of any field with characteristic 0 or greater than 3. The solutions of the cubic equation do not necessarily
     * belong to the same field as the coefficients. For example, some cubic equations with rational coefficients have
     * roots that are non-rational (and even non-real) complex numbers.
     *
     * PURPOSE:
     * asl_cubic_real_root finds REAL roots of a cubic function F(X) = a x^3 + b x^2 + cx + d.
     *
     * DISCUSSION:
     * nothing.
     *
     * LICENSING:
     * This code is distributed under the GNU Affero General Public License v3.0 (AGPL).
     *
     * Permissions of this strongest copyleft license are conditioned on making available complete source code
     * of licensed works and modifications, which include larger works using a licensed work, under the same license.
     * Copyright and license notices must be preserved. Contributors provide an express grant of patent rights.
     * When a modified version is used to provide a service over a network, the complete source code of
     * the modified version must be made available.
     *
     * AGPL Permissions:
     * Commercial use
     * Modification
     * Distribution
     * Patent use
     * Private use
     *
     * AGPL Limitations:
     * Liability
     * Warranty
     *
     * AGPL Conditions:
     * License and copyright notice
     * State changes
     * Disclose source
     * Network use is distribution
     * Same license
     *
     * AUTHOR(S):
     * Mohmmad Mahdi Baghbani Pourvahid
     *
     * MODIFIED:
     * 3 April 2019
     *
     * REFERENCE(S):
     * https://en.wikipedia.org/wiki/Cubic_function
     * http://mathworld.wolfram.com/CubicFormula.html
     *
     * ARGUMENTS:
     * expressions  the function expression, it must be a string array like "x^2+1"
     * a            x^3 coefficient
     * b            x^2 coefficient
     * c            x^1 coefficient
     * d            x^0 coefficient
     * verbose      show process {0: no, 1: yes}
     * state        is answer found or not, it will indicate how many roots have been found
     *              by values: ASL_HAS_NO_ROOT, ASL_HAS_A_ROOT, ASL_HAS_TWO_ROOTS, ASL_HAS_THREE_ROOTS
     *
     * RETURN:
     * pointer to an array of three elements, containing roots
     * this return must be handled with the value of "state"
     *
     */

    // check verbose
    if (verbose != ASL_SILENCE && verbose != ASL_VERBOSE) {
        printf("\nError: verbose argument is not valid.\n");
        Exit(EXIT_FAILURE);
    } // end of if

    // initializing variables
    double x1, x2, x3;
    static double result[3] = {0};

    // Handle quadratic and linear cases
    if (a == 0) {
        if (verbose == ASL_VERBOSE) {
            printf("Function is quadratic, it has two possible roots.\n");
        } // end if(verbose == ASL_VERBOSE)

        // use quadratic solver instead
        double *quadratic_result = asl_quadratic_real_root(b, c, d, verbose, state);

        result[0] = quadratic_result[0];
        result[1] = quadratic_result[1];

    } // end of if

} // end of asl_cubic_real_root