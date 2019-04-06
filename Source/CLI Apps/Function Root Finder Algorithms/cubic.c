/* Source/CLI Apps/Function Root Finder Algorithms/cubic.c
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

#include "../../Library/Function Root Finder Algorithms/cubicAlgorithm.h"
#include "../../Library/Util/util.h"
#include "../../Library/Util/Configurations/asl_configurations.h"

#include <stdio.h>
#include <stdlib.h>

int main() {
    /*
     * Interface of program, this interface will get necessary information from user.
     */

    // initializing variables
    char *fgetsReturn;
    char a_c[ASL_INPUT_SIZE], b_c[ASL_INPUT_SIZE], c_c[ASL_INPUT_SIZE], d_c[ASL_INPUT_SIZE], verbose_c[ASL_INPUT_SIZE],
            tryAgain_c[ASL_INPUT_SIZE];
    char *ptr;
    int verbose = 0, tryAgain = 0, flag = 1;
    double a, b, c, d;

    printf("\t\t\t\tRoot Finder\n"
           "\t\t\t  Cubic polynomial solver\n");

    COEFFICIENTS: //LABEL for goto
    printf("Enter coefficients a, b, c of function \"F(X) = a*x^3 + b*x^2 + cx + d\":\n");

    A: //LABEL for goto
    printf("Enter a:\n");
    fgetsReturn = fgets(a_c, sizeof(a_c), stdin);

    // check input
    if (*fgetsReturn == '\n') {
        printf("Error: you must enter a value for 'a'.\n");

        // a chance to correct your mistake :)
        printf("\nDo you want to try again? {0: no, 1: yes}\n");
        fgetsReturn = fgets(tryAgain_c, sizeof(tryAgain_c), stdin);

        if (*fgetsReturn == '\n') {
            Exit(EXIT_FAILURE);
        } // end of if
        tryAgain = strtol(tryAgain_c, &ptr, 10);

        if (tryAgain) {
            goto A;
        } else {
            Exit(EXIT_FAILURE);
        } // end of if goto
    } //end of input check

    a = strtod(a_c, &ptr);

    B: //LABEL for goto
    printf("Enter b:\n");
    fgetsReturn = fgets(b_c, sizeof(b_c), stdin);

    // check input
    if (*fgetsReturn == '\n') {
        printf("Error: you must enter a value for 'b'.\n");

        // a chance to correct your mistake :)
        printf("\nDo you want to try again? {0: no, 1: yes}\n");
        fgetsReturn = fgets(tryAgain_c, sizeof(tryAgain_c), stdin);

        if (*fgetsReturn == '\n') {
            Exit(EXIT_FAILURE);
        } // end of if
        tryAgain = strtol(tryAgain_c, &ptr, 10);

        if (tryAgain) {
            goto B;
        } else {
            Exit(EXIT_FAILURE);
        } // end of if goto
    } //end of input check

    b = strtod(b_c, &ptr);

    C: //LABEL for goto
    printf("Enter c:\n");
    fgetsReturn = fgets(c_c, sizeof(c_c), stdin);

    // check input
    if (*fgetsReturn == '\n') {
        printf("Error: you must enter a value for 'c'.\n");

        // a chance to correct your mistake :)
        printf("\nDo you want to try again? {0: no, 1: yes}\n");
        fgetsReturn = fgets(tryAgain_c, sizeof(tryAgain_c), stdin);

        if (*fgetsReturn == '\n') {
            Exit(EXIT_FAILURE);
        } // end of if
        tryAgain = strtol(tryAgain_c, &ptr, 10);

        if (tryAgain) {
            goto C;
        } else {
            Exit(EXIT_FAILURE);
        } // end of if goto
    } //end of input check

    c = strtod(c_c, &ptr);

    D: //LABEL for goto
    printf("Enter d:\n");
    fgetsReturn = fgets(d_c, sizeof(d_c), stdin);

    // check input
    if (*fgetsReturn == '\n') {
        printf("Error: you must enter a value for 'd'.\n");

        // a chance to correct your mistake :)
        printf("\nDo you want to try again? {0: no, 1: yes}\n");
        fgetsReturn = fgets(tryAgain_c, sizeof(tryAgain_c), stdin);

        if (*fgetsReturn == '\n') {
            Exit(EXIT_FAILURE);
        } // end of if
        tryAgain = strtol(tryAgain_c, &ptr, 10);

        if (tryAgain) {
            goto D;
        } else {
            Exit(EXIT_FAILURE);
        } // end of if goto
    } //end of input check

    d = strtod(d_c, &ptr);

    VERBOSE: //LABEL for goto
    printf("Do you want to see steps? {0: no, 1: yes}:\n");
    fgetsReturn = fgets(verbose_c, sizeof(verbose_c), stdin);
    verbose = strtol(verbose_c, &ptr, 10);

    // check verbose value
    if ((verbose != ASL_SILENCE && verbose != ASL_VERBOSE) || *fgetsReturn == '\n') {
        printf("Error: invalid value for verbose!\n");

        // a chance to correct your mistake :)
        printf("\nDo you want to try again? {0: no, 1: yes}\n");
        fgetsReturn = fgets(tryAgain_c, sizeof(tryAgain_c), stdin);

        if (*fgetsReturn == '\n') {
            Exit(EXIT_FAILURE);
        } // end of if
        tryAgain = strtol(tryAgain_c, &ptr, 10);

        if (tryAgain) {
            goto VERBOSE;
        } else {
            Exit(EXIT_FAILURE);
        } // end of if goto
    } // end of if verbose

    // calculation
    double *result = asl_cubic_real_root(a, b, c, d, verbose, &flag);

    // if there was an answer
    if (flag == ASL_HAS_A_ROOT) {
        printf("\nThe function F(X) = %g * x^3 %+g * x^2 %+g * x %+g , has one root at point: x(1) = %g .\n",
               a, b, c, d, result[0]);
    } else if (flag == ASL_HAS_DOUBLE_ROOTS) { // if no answer
        printf("\nThe function F(X) = %g * x^3 %+g * x^2 %+g * x %+g , has double root at point: x(1, 2) = %g .\n",
               a, b, c, d, result[0]);
    } else if (flag == ASL_HAS_TWO_ROOTS) {
        printf("\nThe function F(X) = %g * x^3 %+g * x^2 %+g * x %+g ,"
               "has two roots at points: x(1) = %g , x(2) = %g .\n", a, b, c, d, result[0], result[1]);
    } else if (flag == ASL_HAS_DOUBLE_SIMPLE_ROOTS) {
        printf("\nThe function F(X) = %g * x^3 %+g * x^2 %+g * x %+g , has a double root and a simple root\n"
               "at points: x(1, 2) = %g , x(3) = %g .\n",
               a, b, c, d,
               (result[0] == result[1]) ? result[0] : result[2],
               (result[0] == result[1]) ? result[2] : result[0]);
    } else if (flag == ASL_HAS_TRIPLE_ROOTS) {
        printf("\nThe function F(X) = %g * x^3 %+g * x^2 %+g * x %+g , has triple root at point: x(1, 2, 3) = %g .",
               a, b, c, d, result[0]);
    } else if (flag == ASL_HAS_THREE_ROOTS) {
        printf("\nThe function F(X) = %g * x^3 %+g * x^2 %+g * x %+g , has three roots\n"
               "at points: x(1) = %g , x(2) = %g , x(3) = %g .\n",
               a, b, c, d, result[0], result[1], result[2]);
    } else {
        printf("\nThe function %g * x^3 %+g * x^2 %+g * x %+g , doesn't have any roots .\n", a, b, c, d);
    } //end of if else

    // do you want to start again??
    printf("\nDo you want to start again? {0: no, 1: yes}\n");
    fgetsReturn = fgets(tryAgain_c, sizeof(tryAgain_c), stdin);

    if (*fgetsReturn == '\n') {
        Exit(EXIT_FAILURE);
    } // end of if
    tryAgain = strtol(tryAgain_c, &ptr, 10);

    if (tryAgain) {
        goto COEFFICIENTS;
    } else {
        Exit(EXIT_SUCCESS);
    } // end of if goto
    return EXIT_SUCCESS;
} // end of main
