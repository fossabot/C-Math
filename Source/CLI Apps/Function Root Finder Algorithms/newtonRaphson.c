/* Source/CLI Apps/Function Root Finder Algorithms/newtonRaphson.c
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

#include "../../Library/Function Root Finder Algorithms/newtonRaphsonAlgorithm.h"
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
    char expression[INPUT_SIZE];
    char x0_c[INPUT_SIZE], ete_c[INPUT_SIZE], ere_c[INPUT_SIZE],
            tol_c[INPUT_SIZE], maxiter_c[INPUT_SIZE], verbose_c[INPUT_SIZE], tryAgain_c[INPUT_SIZE];
    char *ptr;
    int maxiter = 0, verbose = 0, tryAgain = 0, flag = 1;
    double x0, ete, ere, tol;

    printf("\t\t\t\tRoot Finder\n"
           "\t\t\t  Newton-Raphson Method\n");

    START: //LABEL for goto
    // getting required data from user
    printf("\nEnter the equation you want to solve (example: x^2-3):\n");
    fgetsReturn = fgets(expression, sizeof(expression), stdin);

    // check input
    if (*fgetsReturn == '\n') {
        printf("Error: you must enter a function.\n");

        // a chance to correct your mistake :)
        printf("\nDo you want to try again? {0: no, 1: yes}\n");
        fgetsReturn = fgets(tryAgain_c, sizeof(tryAgain_c), stdin);

        if (*fgetsReturn == '\n') {
            Exit(EXIT_FAILURE);
        } // end of if
        tryAgain = strtol(tryAgain_c, &ptr, 10);

        if (tryAgain) {
            goto START;
        } else {
            Exit(EXIT_FAILURE);
        } // end of if goto
    } //end of interval check

    X: //LABEL for goto
    printf("Enter the starting point (x0):\n");
    fgetsReturn = fgets(x0_c, sizeof(x0_c), stdin);

    // check input
    if (*fgetsReturn == '\n') {
        printf("Error: you must enter a starting point (x0).\n");

        // a chance to correct your mistake :)
        printf("\nDo you want to try again? {0: no, 1: yes}\n");
        fgetsReturn = fgets(tryAgain_c, sizeof(tryAgain_c), stdin);

        if (*fgetsReturn == '\n') {
            Exit(EXIT_FAILURE);
        } // end of if
        tryAgain = strtol(tryAgain_c, &ptr, 10);

        if (tryAgain) {
            goto X;
        } else {
            Exit(EXIT_FAILURE);
        } // end of if goto
    } //end of interval check

    x0 = strtod(x0_c, &ptr);

    ETE: //LABEL for goto
    printf("Enter the estimated true error limit: (enter 0 if you don't want to set an ETE limit):\n");
    fgetsReturn = fgets(ete_c, sizeof(ete_c), stdin);
    ete = strtod(ete_c, &ptr);

    // check ete to be positive
    if (ete < 0 || *fgetsReturn == '\n') {
        printf("Error: estimated true error limit must be a \"POSITIVE\" number!\n");

        // a chance to correct your mistake :)
        printf("\nDo you want to try again? {0: no, 1: yes}\n");
        fgetsReturn = fgets(tryAgain_c, sizeof(tryAgain_c), stdin);

        if (*fgetsReturn == '\n') {
            Exit(EXIT_FAILURE);
        } // end of if
        tryAgain = strtol(tryAgain_c, &ptr, 10);

        if (tryAgain) {
            goto ETE;
        } else {
            Exit(EXIT_FAILURE);
        } // end of if goto
    } // end of ete check

    ERE: //LABEL for goto
    printf("Enter the estimated relative error limit (enter 0 if you don't want to set an ERE limit):\n");
    fgetsReturn = fgets(ere_c, sizeof(ere_c), stdin);
    ere = strtod(ere_c, &ptr);

    // check ere to be positive
    if (ere < 0 || *fgetsReturn == '\n') {
        printf("Error: estimated relative error limit must be a \"POSITIVE\" number!\n");

        // a chance to correct your mistake :)
        printf("\nDo you want to try again? {0: no, 1: yes}\n");
        fgetsReturn = fgets(tryAgain_c, sizeof(tryAgain_c), stdin);

        if (*fgetsReturn == '\n') {
            Exit(EXIT_FAILURE);
        } // end of if
        tryAgain = strtol(tryAgain_c, &ptr, 10);

        if (tryAgain) {
            goto ERE;
        } else {
            Exit(EXIT_FAILURE);
        } // end of if goto
    } // end of ere check

    TOL: //LABEL for goto
    printf("Enter the tolerance limit (enter 0 if you don't want to set a tolerance limit):\n");
    fgetsReturn = fgets(tol_c, sizeof(tol_c), stdin);
    tol = strtod(tol_c, &ptr);

    // check tol to be positive
    if (tol < 0 || *fgetsReturn == '\n') {
        printf("Error: estimated tolerance limit must be a \"POSITIVE\" number!\n");

        // a chance to correct your mistake :)
        printf("\nDo you want to try again? {0: no, 1: yes}\n");
        fgetsReturn = fgets(tryAgain_c, sizeof(tryAgain_c), stdin);

        if (*fgetsReturn == '\n') {
            Exit(EXIT_FAILURE);
        } // end of if
        tryAgain = strtol(tryAgain_c, &ptr, 10);

        if (tryAgain) {
            goto TOL;
        } else {
            Exit(EXIT_FAILURE);
        } // end of if goto
    } // end of ere check

    MAXITER: //LABEL for goto
    printf("Enter the maximum iteration limit (must be positive number):\n");
    fgetsReturn = fgets(maxiter_c, sizeof(maxiter_c), stdin);
    maxiter = strtol(maxiter_c, &ptr, 10);

    // check maximum iteration to be more than 0
    if (maxiter <= 0 || *fgetsReturn == '\n') {
        printf("Error: invalid value for maximum iteration limit!\n");

        // a chance to correct your mistake :)
        printf("\nDo you want to try again? {0: no, 1: yes}\n");
        fgetsReturn = fgets(tryAgain_c, sizeof(tryAgain_c), stdin);

        if (*fgetsReturn == '\n') {
            Exit(EXIT_FAILURE);
        } // end of if
        tryAgain = strtol(tryAgain_c, &ptr, 10);

        if (tryAgain) {
            goto MAXITER;
        } else {
            Exit(EXIT_FAILURE);
        } // end of if goto
    }// end of if maxiter

    VERBOSE: //LABEL for goto
    printf("Do you want to see steps? {0: no, 1: yes}:\n");
    fgetsReturn = fgets(verbose_c, sizeof(verbose_c), stdin);
    verbose = strtol(verbose_c, &ptr, 10);

    // check verbose value
    if ((verbose != 0 && verbose != 1) || *fgetsReturn == '\n') {
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
    double x = asl_newtonRaphson_root(expression, x0, ete, ere, tol, (unsigned int) maxiter, verbose, &flag);

    // if there was an answer
    if (flag) {
        printf("\nThis method solved the function %sfor x = %g .\n\n", expression, x);
    } else { // if no answer
        printf("\nThis method couldn't find the root of the function %s"
               "in the given interval the last calculated value for root is: x = %g .\n\n", expression, x);
    } // end of if flag

    // do you want to start again??
    printf("\nDo you want to start again? {0: no, 1: yes}\n");
    fgetsReturn = fgets(tryAgain_c, sizeof(tryAgain_c), stdin);

    if (*fgetsReturn == '\n') {
        Exit(EXIT_FAILURE);
    } // end of if
    tryAgain = strtol(tryAgain_c, &ptr, 10);

    if (tryAgain) {
        goto START;
    } else {
        Exit(EXIT_SUCCESS);
    } // end of if goto
    return EXIT_SUCCESS;
} // end of main
