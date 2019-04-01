/* Source/Library/Function Root Finder Algorithms/quadraticAlgorithm.c
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

#include "quadraticAlgorithm.h"
#include "../Util/util.h"
#include "../Util/configurations/asl_configurations.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double *asl_quadratic_real_root(double a, double b, double c, int verbose, int *state) {
    /*
     * In elementary algebra, the quadratic formula is the solution of the quadratic equation. There are other ways
     * to solve the quadratic equation instead of using the quadratic formula, such as factoring, completing the square,
     * or graphing. Using the quadratic formula is often the most convenient way.
     * The general quadratic equation is a x^2 + b x + c = 0
     *
     * Here x represents an unknown, while a, b, and c are constants with a not equal to 0. One can verify that
     * the quadratic formula satisfies the quadratic equation by inserting the former into the latter. With the above
     * parameterization, the quadratic formula is: x = (− b ± sqrt(b^2 − 4 a c) ) / (2a)
     *
     * Each of the solutions given by the quadratic formula is called a root of the quadratic equation.
     * Geometrically, these roots represent the x values at which any parabola, explicitly given as y = ax^2 + bx + c,
     * crosses the x-axis. As well as being a formula that will yield the zeros of any parabola, the quadratic formula
     * will give the axis of symmetry of the parabola, and it can be used to immediately determine how many real zeros
     * the quadratic equation has.
     *
     * PURPOSE:
     * asl_quadratic_real_root finds REAL roots of a quadratic function F(X) = a x^2 + b x + c.
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
     * 1 April 2019
     *
     * REFERENCE:
     * https://en.wikipedia.org/wiki/Quadratic_formula
     *
     * ARGUMENTS:
     * expressions  the function expression, it must be a string array like "x^2+1"
     * a            starting point
     * b            estimated true error
     * c            estimated relative error
     * verbose      show process {0: no, 1: yes}
     * state        is answer found or not, it will indicate how many roots have been found
     *              by values: ASL_HAS_NO_ROOT, ASL_HAS_A_ROOT, ASL_HAS_TWO_ROOTS
     *
     * RETURN:
     * pointer to an array of two elements, containing roots
     * this return must be handled with the value of "state"
     *
     */

    // check verbose
    if (verbose != ASL_SILENCE && verbose != ASL_VERBOSE) {
        printf("\nError: verbose argument is not valid.\n");
        Exit(EXIT_FAILURE);
    } // end of if

    double x1, x2;
    static double result[2] = {0};

    // Handle linear case
    if (a == 0) {
        if (verbose == ASL_VERBOSE) {
            printf("Function is linear, it has one possible root.\n");
        } // end if(verbose == ASL_VERBOSE)

        if (b == 0) {
            if (verbose == ASL_VERBOSE) {
                printf("b = 0, it's impossible to solve c = 0, function doesn't have any roots.\n");
            } // end if(verbose == ASL_VERBOSE)

            *state = ASL_HAS_NO_ROOT;

            return result;
        } else {
            if (verbose == ASL_VERBOSE) {
                printf("root of this function can be obtained from root = -c/b.\n");
            } // end if(verbose == ASL_VERBOSE)

            *state = ASL_HAS_A_ROOT;

            x1 = -c / b;
            result[0] = x1;
            result[1] = x1;

            return result;
        } // end of if else
    } // end of if


    double delta = b * b - 4 * a * c;

    if (verbose == ASL_VERBOSE) {
        printf("Calculating delta for this function -> delta = b^2 - 4ac = %g\n", delta);
    } // end if(verbose == ASL_VERBOSE)

    if (delta > 0) {
        if (verbose == ASL_VERBOSE) {
            printf("delta > 0, the function has two 'real' roots.\n");
        } // end if(verbose == ASL_VERBOSE)

        if (b == 0) {
            if (verbose == ASL_VERBOSE) {
                printf("b = 0, function has two identical 'real' roots.\n");
            } // end if(verbose == ASL_VERBOSE)

            double r = sqrt(-c / a);
            x1 = -r;
            x2 = r;

        } else {
            if (verbose == ASL_VERBOSE) {
                printf("b != 0, function has two different 'real' roots.\n");
            } // end if(verbose == ASL_VERBOSE)

            double sgnb = (b > 0 ? 1 : -1);
            double temp = -0.5 * (b + sgnb * sqrt(delta));
            double r1 = temp / a;
            double r2 = c / temp;

            if (r1 < r2) {
                x1 = r1;
                x2 = r2;
            } else {
                x1 = r2;
                x2 = r1;
            }// end of if else
        } // end of if else

        *state = ASL_HAS_TWO_ROOTS;

        result[0] = x1;
        result[1] = x2;

        return result;
    } else if (delta == 0) {
        if (verbose == ASL_VERBOSE) {
            printf("delta = 0, function has two identical 'real' roots.\n");
        } // end if(verbose == ASL_VERBOSE)

        *state = ASL_HAS_A_ROOT;

        x1 = -0.5 * b / a;

        result[0] = x1;
        result[1] = x1;

        return result;
    } else {
        if (verbose == ASL_VERBOSE) {
            printf("delta < 0, function doesn't have 'real' roots.\n");
        } // end if(verbose == ASL_VERBOSE)

        *state = ASL_HAS_NO_ROOT;

        return result;
    } // end of if else
} // end of asl_quadratic_real_root