/* Source/Library/Function Root Finder Algorithms/steffensenAlgorithm.c
 *
 * ASL - Azadeh Scientific Library in C
 *
 * Copyright (C) 2019 Mohammad Mahdi Baghbani Pourvahid
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

#include "../Util/functions.h"
#include "../Differentiation Algorithms/derivNumericalAlgorithm.h"
#include "../Util/functions.h"
#include "../Util/util.h"
#include "../Util/Configurations/asl_configurations.h"

#include <stdio.h>
#include <math.h>

double asl_steffenson_root(const char *expression, double x, double ete, double ere, double tol, unsigned int maxiter,
                           int verbose, int *state) {
    /*
     * In numerical analysis, Steffensen's method is a root-finding technique similar to Newton's method,
     * named after Johan Frederik Steffensen. Steffensen's method also achieves quadratic convergence,
     * but without using derivatives as Newton's method does.
     *
     * PURPOSE:
     * asl_steffensen_root a root of a function F(X).
     *
     * DISCUSSION:
     * Nothing.
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
     * Mohammad Mahdi Baghbani Pourvahid
     *
     * MODIFIED:
     * 9 April 2019
     *
     * REFERENCE(S):
     * https://en.wikipedia.org/wiki/Steffensen%27s_method
     *
     * ARGUMENTS:
     * expressions  the function expression, it must be a string array like "x^2+1"
     * x            starting point
     * ete          estimated true error
     * ere          estimated relative error
     * tol          tolerance error
     * maxiter      maximum iteration threshold
     * verbose      show process {0: no, 1: yes}
     * state        is answer found or not, will set value of state to 0 if no answers been found
     *
     */

    // check error thresholds
    if (ere < 0 || ete < 0 || tol < 0) {
        printf("\nError: ete or ere or tol argument is not valid.\n");
        Exit(EXIT_FAILURE);
    } // end of if

    // check maxiter to be more than zero
    if (maxiter <= 0) {
        printf("\nError: argument maxiter must be more than zero!\n");
        Exit(EXIT_FAILURE);
    } // end of maxiter check

    // check verbose
    if (verbose != ASL_SILENCE && verbose != ASL_VERBOSE) {
        printf("\nError: verbose argument is not valid.\n");
        Exit(EXIT_FAILURE);
    } // end of if

    // calculates y = f(x) at initial point
    double fx = function_1_arg(expression, x);

    // first guess check
    if (fabs(fx) <= tol) {
        if (verbose == ASL_VERBOSE) {
            printf("Root has been found at the initial point x.\n");
        } // end if(verbose == ASL_VERBOSE)

        return x;
    } // end of if

    // initializing variables
    unsigned int iter = 1, dfx_counter = 2;
    double x_new, fx_new, dfx, u, v;
    double ete_err = ete, ere_err = ere, tol_err = tol, x_past = 0;

    while (iter <= maxiter) {

        // Termination Criterion
        // if calculated error is less than estimated true error threshold
        if (ete != 0 && ete_err < ete) {
            if (verbose == ASL_VERBOSE) {
                printf("\nIn this iteration[#%d]: |x%d - x%d| < estimated true error [%g < %g],\n"
                       "so x is close enough to the root of function.\n\n", iter - 1, iter - 1, iter - 2, ete_err,
                       ete);
            } // end if(verbose == ASL_VERBOSE)

            return x;
        } // end of estimated true error check

        // if calculated error is less than estimated relative error threshold
        if (ere != 0 && ere_err < ere) {
            if (verbose == ASL_VERBOSE) {
                printf("\nIn this iteration[#%d]: |(x%d - x%d / x%d)| < estimated relative error [%g < %g],\n"
                       "so x is close enough to the root of function.\n\n", iter - 1, iter - 1, iter - 2, iter - 1,
                       ere_err, ere);
            } // end if(verbose == ASL_VERBOSE)

            return x;
        } // end of estimated relative error check

        // if y3 is less than tolerance error threshold
        if (tol != 0 && tol_err < tol) {
            if (verbose == ASL_VERBOSE) {
                printf("\nIn this iteration[#%d]: |f(x%d)| < tolerance [%g < %g],\n"
                       "so x is close enough to the root of function.\n\n", iter - 1, iter - 1, tol_err, tol);
            } // end if(verbose == ASL_VERBOSE)

            return x;
        } // end of tolerance check

        // calculate derivative of function in the given point
        dfx = firstDerivative_1_arg(expression, x, ASL_EPSILON, ASL_CENTRAL_DIFFERENCE);

        DFX_LABEL: // LABEL for go to
        // if derivative isn't equal to zero
        if (dfx) {

            // calculate new x by subtracting the derivative from x
            x_new = x - fx / dfx;

            // calculate new y at new root estimate x
            fx_new = function_1_arg(expression, x_new);

            if (verbose == ASL_VERBOSE) {
                printf("\nIteration number [#%d]: f(x%d) = %g, f'(x%d) = %g, delta(x%d) = f(x%d) / f'(x%d) = %g\n"
                       "x%d = x%d - delta(x%d) = %g , f(x%d) = %g.\n", iter, iter - 1, fx, iter - 1, dfx, iter - 1,
                       iter - 1, iter - 1, fx / dfx, iter, iter - 1, iter - 1, x_new, iter, fx_new);
            } // end of if verbose == ASL_VERBOSE

            /*
             * This is Newton's method with an Aitken "delta-squared"
             * acceleration of the iterates. This can improve the convergence on
             * multiple roots where the ordinary Newton algorithm is slow.
             * x[i+1] = x[i] - f(x[i]) / f'(x[i])
             *
             * x_accelerated[i] = x[i] - (x[i+1] - x[i])**2 / (x[i+2] - 2*x[i+1] + x[i])
             * We can only use the accelerated estimate after three iterations,
             * and use the unaccelerated value until then.
             */

            if (iter > 3) {
                u = (x - x_past);
                v = (x_new - 2 * x + x_past);

                // avoid division by zero
                if (v != 0) {
                    /* accelerated value */
                    x_new = x_past - u * u / v;
                    fx_new = function_1_arg(expression, x_new);
                    if (verbose == ASL_VERBOSE) {
                        printf("Using Aitken \"delta-squared\" acceleration. (x, fx) = (%g, %g) .\n", x_new, fx_new);
                    } // end of if verbose == ASL_VERBOSE
                } // end of if else
            } // end of if

            // calculate errors
            ete_err = fabs(x_new - x);

            if (x != 0) {
                ere_err = fabs(ete_err / x);
            } else {
                ere_err = ere;
            } // end of zero-division guard

            tol_err = fabs(fx_new);

            // substitute variables for next iteration
            x_past = x;
            x = x_new;
            fx = fx_new;
            iter++;

        } else { // if derivative is equal to zero

            if (verbose == ASL_VERBOSE) {
                if (dfx_counter == 2) {
                    printf("f'(x) = 0, trying another differentiation algorithm.\n");
                } else if (dfx_counter > 8) {
                    printf("f'(x) = 0, this algorithm cannot find a root.\n");
                } else {
                    printf("using central derivation algorithm with %d order accuracy, still failed.\n",
                           dfx_counter - 2);
                } // end of if
            } // end if(verbose == ASL_VERBOSE)

            // try to get more precise derivative [up to eight order accuracy]
            if (dfx_counter <= 8) {

                // calculate new f'(x)
                dfx = centralFirstDerivative_1_arg(expression, x, ASL_EPSILON, dfx_counter);
                dfx_counter += 2;

                // go back and check value
                goto DFX_LABEL;
            } else {
                if (verbose == ASL_VERBOSE) {
                    printf("Steffensen method can't solve f(x) = 0 if f'(x0) = 0 !\n"
                           "check your function and if you think it has derivative\n"
                           "then try to choose a better starting point x0 .\n");
                } // end if(verbose == ASL_VERBOSE)
                // go out of while loop
                break;
            } // end of if else
        } // end of if(dfx)
    } // end of while loop

    if (verbose == ASL_VERBOSE) {
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
    } // end if(verbose == ASL_VERBOSE)

    // error has been set but reaches to maxiter, means algorithms didn't converge to a root
    if (!(ete == 0 && ere == 0 && tol == 0)) {
        // set state to 0 (false)
        *state = ASL_HAS_NO_ROOT;
    } // end of if
    return x;
} // end of asl_steffensen_root