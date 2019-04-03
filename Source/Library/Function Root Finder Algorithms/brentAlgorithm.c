/* Source/Library/Function Root Finder Algorithms/brentAlgorithm.c
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

#include "brentAlgorithm.h"
#include "../Util/functions.h"
#include "../Util/util.h"
#include "../Util/Configurations/asl_configurations.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double asl_brent_root(const char *expression, double a, double b, double tol, unsigned int maxiter, int verbose,
                      int *state) {
    /*
     * In numerical analysis, Brent's method is a root-finding algorithm combining the bisection method,
     * the secant method and inverse quadratic interpolation. It has the reliability of bisection but it can be
     * as quick as some of the less-reliable methods. The algorithm tries to use the potentially fast-converging
     * secant method or inverse quadratic interpolation if possible, but it falls back to the more robust
     * bisection method if necessary. Brent's method is due to Richard Brent and builds on an earlier algorithm
     * by Theodorus Dekker. Consequently, the method is also known as the Brent–Dekker method. 
     *
     * PURPOSE:
     * asl_brent_root seeks a root of a function F(X) in an interval [A, B].
     *
     * DISCUSSION:
     * This function assumes that F(A)*F(B) < 0.
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
     * REFERENCE(S):
     * https://en.wikipedia.org/wiki/Brent's_method
     *
     * ARGUMENTS:
     * expressions  the function expression, it must be a string array like "x^2+1"
     * a            starting point of interval [a, b]
     * b            ending point of interval [a, b]
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

    // check error threshold
    if (tol < 0) {
        printf("\nError: tol argument is not valid.\n");
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

    // set state to has a root at start of program
    // it would be changed if root couldn't be found
    *state = ASL_HAS_A_ROOT;

    // calculates y1 = f(a) and y2 =f(b)
    double fa = function_1_arg(expression, a);
    double fb = function_1_arg(expression, b);

    // check interval edges
    // if any of them are smaller than tolerance
    // then it's root of the function
    if (fabs(fa) <= tol) {
        if (verbose == ASL_VERBOSE) {
            printf("Root has been found at the start of interval [a, b].\n");
        } // end if(verbose == ASL_VERBOSE)

        return a;
    } else if (fabs(fb) <= tol) {
        if (verbose == ASL_VERBOSE) {
            printf("Root has been found at the end of interval [a, b].\n");
        } // end if(verbose == ASL_VERBOSE)

        return b;
    } else if ((fa > 0.0 && fb < 0.0) || (fa < 0.0 && fb > 0.0)) {
        // if y1 and y2 have different signs, so we can use brent method
        // because when we bracket a function in two end of an interval (a, b)
        // if and only if f(a)f(b) < 0, function should have at least 1 root in that interval,
        // assume f(a) > 0, then f(b) must be smaller than zero to hold the equation f(a)f(b) < 0
        // it's clear that the curve of function should intersect x-axis at some point between [a, b]
        // in order to move from f(a) > 0 to f(b) < 0

        // if magnitude of f(a) is less than magnitude of f(b)
        // swap a with b and fa with fb
        if (fabs(fa) < fabs(fb)) {
            swapDouble(&a, &b);
            swapDouble(&fa, &fb);
        } // end of if

        // initializing variables
        unsigned int iter = 1, flag = 1;
        double s = 0, fs = 0, c = a, fc = fa, d = 0, error = tol;

        while (iter <= maxiter) {

            // Termination Criterion
            if (tol != 0 && error < tol) {
                if (verbose == ASL_VERBOSE) {
                    printf("\nIn this iteration [#%d]: |b - a| < tolerance -> [%g < %g],\n"
                           "so x is close enough to the root of function.\n\n", iter - 1, error, tol);
                } // end if(verbose == ASL_VERBOSE)

                return s;
            } // end of tolerance check

            if (fa != fc && fb != fc) {
                if (verbose == ASL_VERBOSE) {
                    printf("In this iteration [%d]: using inverse quadratic interpolation.\n", iter);
                } // end if(verbose == ASL_VERBOSE)

                // use inverse quadratic interpolation
                // I can explain it here but ... em ... why not searching it at wikipedia?
                s = (a * fb * fc / ((fa - fb) * (fa - fc))) +
                        (b * fa * fc / ((fb - fa) * (fb - fc))) +
                        (c * fa * fb / ((fc - fa) * (fc - fb)));
            } else {
                if (verbose == ASL_VERBOSE) {
                    printf("In this iteration [%d]: using secant method.\n", iter);
                } // end if(verbose == ASL_VERBOSE)

                // secant method
                // try wikipedia for more explanations
                s = b - fb * (b - a) / (fb - fa);
            } // end of if else

            // horror movie ahead, don't freak out!
            // it's just a condition testing
            // that is required by brent method
            if (((s < (3 * a + b) * 0.25) || (s > b)) ||
                    (flag && fabs(s - b) >= fabs(b - c) * 0.5) ||
                    (!flag && fabs(s - b) >= fabs(c - d) * 0.5) ||
                    (flag && fabs(b - c) < tol) ||
                    (!flag && fabs(c - d) < tol)) {

                if (verbose == ASL_VERBOSE) {
                    printf("then using bisection method.\n");
                } // end if(verbose == ASL_VERBOSE)

                // bisection method
                // wik ... ok ok you already knew what i'm going to say
                s = (a + b) / 2;

                // set flag
                flag = 1;
            } else {
                // clear flag
                flag = 0;
            } // end of if else

            // calculate fs
            fs = function_1_arg(expression, s);

            //substitute variables for next loop
            d = c;
            c = b;
            fc = fb;

            // interval reduction
            // in this part of brent's algorithm we are trying to reduce
            // interval for next iteration, we need to locate the root's
            // position between [a, s, b], by a simple test f(a)f(s) ?< 0
            // and then re-bracket the domain
            if ((fa > 0.0 && fs < 0.0) || (fa < 0.0 && fs > 0.0)) {
                if (verbose == ASL_VERBOSE) {
                    printf("Searching interval has been reduced, 'b' has been replaced by 's'.\n");
                } // end if(verbose == ASL_VERBOSE)

                b = s;
                fb = fs;
            } else {
                if (verbose == ASL_VERBOSE) {
                    printf("Searching interval has been reduced, 'a' has been replaced by 's'.\n");
                } // end if(verbose == ASL_VERBOSE)

                a = s;
                fa = fs;
            } // end of if

            // calculate error
            error = fabs(b - a);

            if (verbose == ASL_VERBOSE) {
                printf("\nNext iteration set is:\n"
                       "[(a, b), c, d, s, flag, error] = [(%g, %g), %g, %g, %g, %d, %g].\n\n",
                       a, b, c, d, s, flag, error);
            } // end if(verbose == ASL_VERBOSE)

            iter++;
        } // end of while loop

        if (verbose == ASL_VERBOSE) {
            // if user wanted to calculate root on maximum iteration limit
            // without specifying a tolerance error then the answer is what user wants
            if (tol == 0) {
                printf("\nWith maximum iteration of %d :\n", maxiter);
            } else {
                // if tolerance has been set and algorithm reached maximum iteration limit,
                // then the answer has not been found
                printf("\nThe solution does not converge or iterations are not sufficient.\n");
            } // end of if ... else

            printf("the last calculated root is x = %g .\n", s);
        } // end if(verbose == ASL_VERBOSE)

        // error has been set but reaches to maxiter, means algorithms didn't converge to a root
        if (tol != 0) {
            // set state to 0 (false)
            *state = ASL_HAS_NO_ROOT;
        } // end of if
        return s;

    } else { // if y1 and y2 have same signs, then we can't use bisection method
        if (verbose == ASL_VERBOSE) {
            printf("Incorrect bracketing of function domain!\n"
                   "keep in mind that the inequality f(a) * f(b) < 0 must be correct\n"
                   "in order to use Brent's method.\n");
        }// end if(verbose == ASL_VERBOSE)

        *state = ASL_HAS_NO_ROOT;
        return -1;
    } // end of if ... else
} // end of asl_brent_root function
