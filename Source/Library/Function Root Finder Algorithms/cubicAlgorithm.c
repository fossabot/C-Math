/* Source/Library/Function Root Finder Algorithms/cubicAlgorithm.c
 *
 * ASL - Azadeh Scientific Library in C
 *
 * Copyright (C) 2019 Mohammad Mahdi Baghbani Pourvahid
 *
 * this module originally came from gsl/poly/solve_cubic.c and has been modified by me.
 * copyright notice for original source:
 *
 * Copyright (C) 1996, 1997, 1998, 1999, 2000, 2007, 2009 Brian Gough
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
     * Mohammad Mahdi Baghbani Pourvahid
     *
     * MODIFIED:
     * 5 April 2019
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
            printf("Function could be quadratic because a = 0, it might have two possible roots.\n");
        } // end if(verbose == ASL_VERBOSE)

        // use quadratic solver instead
        double *quadratic_result = asl_quadratic_real_root(b, c, d, verbose, state);

        result[0] = quadratic_result[0];
        result[1] = quadratic_result[1];

        return result;
    } else {
        // if a is non-zero, normalize the function to
        // the standard form "x^3 + b x^2 + c x + d = 0"
        // by dividing all the constants by a.
        b /= a;
        c /= a;
        d /= a;
    } // end of if else

    // q = delta0, r = delta1
    double q = (b * b - 3 * c);
    double r = (2 * b * b * b - 9 * b * c + 27 * d);

    if (verbose == ASL_VERBOSE) {
        printf("\nFirst, we calculate delta0 and delta1: delta0 = %g, delta1 = %g .\n"
               "we define delta with this equality: delta1^2 - 4*delta0^2 = -27*delta.\n", q, r);
    } // end if(verbose == ASL_VERBOSE)

    double Q = q / 9;
    double R = r / 54;

    if (verbose == ASL_VERBOSE) {
        printf("Then, we define the intermediate variables: Q = delta0/9 = %g, R = delta1/54 = %g .\n"
               "The general cubic equation then becomes: x^3 - 3Qx + 2R = 0 .\n", Q, R);
    } // end if(verbose == ASL_VERBOSE)

    double Q3 = Q * Q * Q;
    double R2 = R * R;

    // these variables are basically Q3 and R2 but written
    // in a form suitable for exact computation with integers
    double CQ3 = 2916 * q * q * q;
    double CR2 = 729 * r * r;

    if (q == 0 && r == 0) {
        if (verbose == ASL_VERBOSE) {
            printf("delta = 0 and delta0 = 0, then the equation has a single 'real' root (which is a triple root).\n");
        } // end if(verbose == ASL_VERBOSE)

        *state = ASL_HAS_TRIPLE_ROOTS;

        x1 = -b / 3;
        result[0] = x1;
        result[1] = x1;
        result[2] = x1;

        return result;
    } else if (CR2 == CQ3) {
        /*
         * this test is actually R2 == Q3, written in a form suitable
         * for exact computation with integers
         *
         * Due to finite precision some double roots may be missed, and
         * considered to be a pair of complex roots z = x +/- epsilon i
         * close to the real axis.
         *
         */

        if (verbose == ASL_VERBOSE) {
            printf("delta = 0 and delta0 != 0, then there are both a double 'real' root, and a simple 'real' root.\n");
        } // end if(verbose == ASL_VERBOSE)

        double sqrtQ = sqrt(Q);

        if (R > 0) {
            x1 = -2 * sqrtQ - b / 3;
            x2 = sqrtQ - b / 3;
            result[0] = x1;
            result[1] = x2;
            result[2] = x2;
        } else {
            x1 = -sqrtQ - b / 3;
            x2 = 2 * sqrtQ - b / 3;
            result[0] = x2;
            result[1] = x2;
            result[2] = x1;
        } // end of if

        *state = ASL_HAS_DOUBLE_SIMPLE_ROOTS;

        return result;
    } else if (R2 < Q3) {
        /*
         * Trigonometric solution for three real roots
         *
         * When a cubic equation has three real roots, the formulas expressing these roots in terms of radicals
         * involve complex numbers. It has been proved that when none of the three real roots is rational
         * —the casus irreducibilis— one cannot express the roots in terms of real radicals. Nevertheless,
         * purely real expressions of the solutions may be obtained using hypergeometric functions, or
         * more elementarily in terms of trigonometric functions, specifically in terms of the cosine and arccosine
         * functions.
         *
         * The formulas which follow, due to François Viète, are true in general (except when p = 0), and
         * are purely real when the equation has three real roots, but involve complex cosines and arccosines
         * when there is only one real root.
         *
         * define:
         * x = t - b/3
         * p = (3ac − b^2) / (3 * a^2)
         * q = (2*b^3 − 9abc + 27*a^2*d) / (27*a^3)
         *
         * the roots are:
         * t(k) = 2*sqrt( −p/3 ) * cos( [arccos( 3q/2p − sqrt(-3/p) ) − (2 π k)] / 3 ) for k = 0 , 1 , 2 .
         *
         * calculation in this program is done by below equivalents:
         * 2*sqrt( −p/3 ) = -2 * sqrt(Q) ==> norm
         * 3q/2p − sqrt(-3/p) = sgnR * sqrt(R2 / Q3) ==> ratio
         * arccos( 3q/2p − sqrt(-3/p) ) = acos(ratio) ==> theta
         *
         */

        if (verbose == ASL_VERBOSE) {
            printf("delta > 0, then there are three distinct 'real' roots.\n");
        } // end if(verbose == ASL_VERBOSE)

        double sgnR = (R >= 0 ? 1 : -1);
        double ratio = sgnR * sqrt(R2 / Q3);
        double theta = acos(ratio);
        double norm = -2 * sqrt(Q);

        x1 = norm * cos(theta / 3) - b / 3;
        x2 = norm * cos((theta + 2.0 * ASL_PI) / 3) - b / 3;
        x3 = norm * cos((theta - 2.0 * ASL_PI) / 3) - b / 3;

        // Sort x1, x2, x3 into increasing order

        if (x1 > x2) {
            swapDouble(&x1, &x2);
        } // end of if

        if (x2 > x3) {
            swapDouble(&x2, &x3);

            if (x1 > x2) {
                swapDouble(&x1, &x2);
            } // end of if
        } // end of if

        *state = ASL_HAS_THREE_ROOTS;

        result[0] = x1;
        result[1] = x2;
        result[2] = x3;

        return result;
    } else {
        /*
         *  Defining:
         *  D	=	R^2 - Q^3
         *  S	=	cubeRoot(R + sqrt(D))
         *  T	=	cubeRoot(R - sqrt(D))
         *
         *  where D is the polynomial discriminant (which is defined slightly differently,
         *  including the opposite sign, by Birkhoff and Mac Lane 1996) then gives
         *  very simple expressions for A and B, namely
         *
         *  A	=	S-T
         *  B	=	S+T
         *
         *  Therefore, at last, the roots of the original equation "x^3 + b*x^2 + cx + d = 0"
         *  in z are then given by:
         *  z1	=	-b/3 + (S+T)                            "real root"
         *  z2	=	-b/3 - [(S+T) + i*sqrt(3)(S-T)] / 2     "complex root"
         *  z3	=	-b/3 - [(S+T) - i*sqrt(3)(S-T)] / 2     "complex root"
         *
         *  in this function we are only seeking the real root, x = -b/3 + (S+T)
         *
         *  calculation in this program is done by below equivalents:
         *  S = cubeRoot(R + sqrt(D)) = -sgnR * pow(fabs(R) + sqrt(R2 - Q3), 1.0 / 3.0) ==> S
         *  T =	cubeRoot(R - sqrt(D)) = T = Q / S ==> T
         *
         */

        if (verbose == ASL_VERBOSE) {
            printf("delta < 0, then there are one 'real' root and two complex roots.\n"
                   "however this function only computes real root, and not the complex ones.\n");
        } // end if(verbose == ASL_VERBOSE)

        double sgnR = (R >= 0 ? 1 : -1);
        double S = -sgnR * pow(fabs(R) + sqrt(R2 - Q3), 1.0 / 3.0);
        double T = Q / S;

        x1 = S + T - b / 3;

        *state = ASL_HAS_A_ROOT;

        result[0] = x1;

        return result;
    } // end of if else
} // end of asl_cubic_real_root