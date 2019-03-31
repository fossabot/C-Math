/* Source/Library/Function Root Finder Algorithms/secantAlgorithm.c
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
 * 2. Altered source versions must be plainly marked as such, and must not be
 * misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 */

#include "secantAlgorithm.h"
#include "../Util/functions.h"
#include "../Util/util.h"
#include "../Util/_configurations.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double ASL_secant_root(const char *expression, double a, double b, double ete, double ere, double tol,
                       unsigned int maxiter, int verbose, int *state) {
    /*
     * In numerical analysis, the secant method is a root-finding algorithm that uses a succession of roots
     * of secant lines to better approximate a root of a function f. The secant method can be thought of as
     * a finite-difference approximation of Newton's method. However, the method was developed independently
     * of Newton's method and predates it by over 3000 years
     *
     * PURPOSE:
     * ASL_secant_root seeks a root of a function F(X) in an interval [A, B].
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
     * 31 March 2019
     *
     * REFERENCE:
     * https://en.wikipedia.org/wiki/Newton%27s_method
     *
     * ARGUMENTS:
     * expressions  the function expression, it must be a string array like "x^2+1"
     * a            starting point of interval [a, b]
     * b            ending point of interval [a, b]
     * ete          estimated true error
     * ere          estimated relative error
     * tol          tolerance error
     * maxiter      maximum iteration threshold
     * verbose      show process {0: no, 1: yes}
     * state        is answer found or not, will set value of state to 0 if no answers been found
     *
     */

    // fix interval reverse
    if (a > b) {
        swapDouble(&a, &b);
    } // end of if

    // check interval
    if (a == b) {
        printf("\nError: improper interval!\n");
        Exit(EXIT_FAILURE);
    } //end of interval check

    // check error thresholds
    if (ere < 0 || ete < 0 || tol < 0){
        printf("\nError: ete or ere or tol argument is not valid.\n");
        Exit(EXIT_FAILURE);
    } // end of if

    // check maxiter to be more than zero
    if (maxiter <= 0) {
        printf("\nError: argument maxiter must be more than zero!\n");
        Exit(EXIT_FAILURE);
    } // end of maxiter check

    // check verbose
    if (verbose != 0 && verbose != 1) {
        printf("\nError: verbose argument is not valid.\n");
        Exit(EXIT_FAILURE);
    } // end of if

    // set state to has a root at start of program
    // it would be changed if root couldn't be found
    *state = HAS_A_ROOT;

    // initializing variables
    unsigned int iter = 1;
    double fx;
    double x = 0, ete_err = ete, ere_err = ere, tol_err = tol;

    // calculates y1 = f(a) and y2 =f(b)
    double fa = function_1_arg(expression, a);
    double fb = function_1_arg(expression, b);

    // check interval edges
    // if any of them are smaller than tolerance
    // then it's root of the function
    if (fabs(fa) <= tol) {
        if (verbose) {
            printf("Root has been found at the start of interval [a, b].\n");
        } // end if(verbose)

        return a;
    } else if (fabs(fb) <= tol) {
        if (verbose) {
            printf("Root has been found at the end of interval [a, b].\n");
        } // end if(verbose)

        return b;
    } // end of if

    while (iter <= maxiter) {

        // Termination Criterion
        // if calculated error is less than estimated true error threshold
        if (ete != 0 && ete_err < ete) {
            if (verbose) {
                printf("\nIn this iteration[#%d]: |x%d - x%d| < estimated true error [%g < %g],\n"
                       "so x is close enough to the root of function.\n\n", iter - 1, iter - 1, iter - 2, ete_err, ete);
            } // end if(verbose)

            return x;
        } // end of estimated true error check

        // if calculated error is less than estimated relative error threshold
        if (ere != 0 && ere_err < ere) {
            if (verbose) {
                printf("\nIn this iteration[#%d]: |(x%d - x%d / x%d)| < estimated relative error [%g < %g],\n"
                       "so x is close enough to the root of function.\n\n", iter - 1, iter - 1, iter - 2, iter - 1,
                       ere_err, ere);
            } // end if(verbose)

            return x;
        } // end of estimated relative error check

        // if y3 is less than tolerance error threshold
        if (tol != 0 && tol_err < tol) {
            if (verbose) {
                printf("\nIn this iteration[#%d]: |f(x%d)| < tolerance [%g < %g],\n"
                       "so x is close enough to the root of function.\n\n", iter - 1, iter - 1, tol_err, tol);
            } // end if(verbose)

            return x;
        } // end of tolerance check

        // calculate new estimate of root
        x = b - fb * (b - a) / (fb - fa);

        // evaluate the function at point x, y3 = f(x)
        fx = function_1_arg(expression, x);

        // tolerance error
        tol_err = fabs(fx);

        if (verbose) {
            printf("\nIteration number [#%d]: x%d = %g, f(x%d) = %g .\n", iter, iter, x, iter, fx);
        } // end of if verbose

        //calculate errors
        ete_err = fabs(x - b);
        //calculate relative error
        if (b != 0) {
            ere_err = fabs(ete_err / b);
        } else {
            ere_err = ere;
        } // end of zero-division guard

        // update variables for next iteration
        a = b;
        fa = fb;
        b = x;
        fb = fx;
        iter++;
    } // end of while loop

    if (verbose) {
        // if user wanted to calculate root on maximum iteration limit
        // without specifying any error, then the answer is what user wants
        if (ete == 0 && ere == 0 && tol == 0) {
            printf("\nWith maximum iteration of %d :\n", maxiter);
        } else {
            // if tolerance has been set and algorithm reached maximum iteration limit,
            // then the answer has not been found
            printf("\nThe solution does not converge or iterations are not sufficient.\n");
        } // end of if ... else

        printf("the last calculated root is x = %g .\n", x);
    } // end if(verbose)

    // error has been set but reaches to maxiter, means algorithms didn't converge to a root
    if (!(ete == 0 && ere == 0 && tol == 0)) {
        // set state to 0 (false)
        *state = HAS_NO_ROOT;
    } // end of if
    return x;
} // end of ASL_secant_root function