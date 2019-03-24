#include "monteCarloIntegrationAlgorithm.h"
#include "../Optimization Algorithms/simpleMaxMinFinderAlgorithm.h"
#include "../Util/randomGenerator.h"
#include "../Util/functions.h"
#include "../Util/util.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double monteCarloIntegration(const char *expression, double a, double b, unsigned int n, unsigned int options,
                             int verbose) {
    /*
     * In mathematics, Monte Carlo integration is a technique for numerical integration using random numbers.
     * It is a particular Monte Carlo method that numerically computes a definite integral. While other algorithms
     * usually evaluate the integrand at a regular grid, Monte Carlo randomly choose points at which
     * the integrand is evaluated. This method is particularly useful for higher-dimensional integrals.
     *
     * ARGUMENTS:
     * expressions  the function expression, it must be a string array like "x^2+1"
     * a             starting point of interval [a, b]
     * b             ending point of interval [a, b]
     * n             number of sub-intervals to use
     * options       type of monte carlo to be used {0: random points ,  1: random rectangles}
     * verbose       show process {0: no, 1: yes}
     *
     */

    // fix interval reverse
    if (a > b){
        double temp = a;
        a = b;
        b = temp;
    } // end of if

    // check interval
    if (a == b) {
        printf("\nError: improper interval!\n");
        Exit(EXIT_FAILURE);
    } //end of interval check

    // check n to be more than zero
    // this is implemented to prevent divide by zero error
    if (n <= 0) {
        printf("\nError: argument n must be more than zero!\n");
        Exit(EXIT_FAILURE);
    } // end of n check

    // check mode and options value
    if (options != 0 && options != 1){
        printf("\nError: arguments option or mode are not valid.\n");
        Exit(EXIT_FAILURE);
    } // end of if

    // check verbose
    if (verbose != 0 && verbose != 1) {
        printf("\nError: verbose argument is not valid.\n");
        Exit(EXIT_FAILURE);
    } // end of if

    // use requested type of monte carlo integration
    switch (options){
        case 0:
            return monteCarloPointIntegration(expression, a, b, n, verbose);
        case 1:
            return monteCarloRectangleIntegration(expression, a, b, n, verbose);
    } // end of switch

    // it shouldn't reach this part, however I wrote a return block
    // to avoid "Control reaches end of non-void function" error
    return 0;
} // end of function monteCarloIntegration

double monteCarloPointIntegration(const char *expression, double a, double b, unsigned int n, int verbose) {
    /*
     * In this method we use random points and then calculate the area under function based on
     * proportional relation between points under the curve of function and all points to the area
     * of rectangle which surrounds whole function curve
     *
     * ARGUMENTS:
     * expressions  the function expression, it must be a string array like "x^2+1"
     * a             starting point of interval [a, b]
     * b             ending point of interval [a, b]
     * n             number of sub-intervals to use
     * verbose       show process {0: no, 1: yes}
     *
     */

    // fix interval reverse
    if (a > b){
        double temp = a;
        a = b;
        b = temp;
    } // end of if

    // check interval
    if (a == b) {
        printf("\nError: improper interval!\n");
        Exit(EXIT_FAILURE);
    } //end of interval check

    // check n to be more than zero
    // this is implemented to prevent divide by zero error
    if (n <= 0) {
        printf("\nError: argument n must be more than zero!\n");
        Exit(EXIT_FAILURE);
    } // end of n check

    // check verbose
    if (verbose != 0 && verbose != 1) {
        printf("\nError: verbose argument is not valid.\n");
        Exit(EXIT_FAILURE);
    } // end of if

    // find maximum and minimum of function
    double *extremum = simpleMaxMinFinder(expression, a, b, n);
    // get values of maximum and minimum
    double max = function_1_arg(expression, extremum[0]), min = function_1_arg(expression, extremum[1]);

    if (verbose) {
        printf("\nFinding maximum and minimum of this function.\n");
        printf("Maximum of this function happens at point x = %lf ", extremum[0]);
        printf("and has value = %lf .\n", max);
        printf("Minimum of this function happens at point x = %lf ", extremum[1]);
        printf("and has value = %lf .\n", min);
    } // end if(verbose)

    // initializing variables
    double area, rectangleArea, x, y, fx;
    double xRandomCoefficient, yRandomCoefficient;
    double width = (b - a), state = max * min, height = (max - min);
    int correctPoints = 0;

    if (verbose) {
        printf("\nCalculating rectangle Area.\n");
    } // end if(verbose)

    // calculate rectangle area
    if (state >= 0) { // if function is either entirely above x axis or below it
        if (max > 0) {
            // if it's above x axis then the upper bound of rectangle is
            // the maximum of the function and lower bound in x = 0
            height = max;

            if (verbose) {
                printf("Rectangle is entirely above x axis, ");
            } // end if(verbose)
        } else {
            // if it's below x axis then the upper bound of rectangle is
            // x = 0 and lower bound is the minimum of the function
            height = min;

            if (verbose) {
                printf("Rectangle is entirely below x axis, ");
            } // end if(verbose)
        }

        if (verbose) {
            printf("and it's height is %lf .\n", height);
        } // end if(verbose)

        // the area of the rectangle in this case is the width of rectangle (b - a)
        // multiplied by distance between lower and upper bound which is always height
        rectangleArea = width * height;

        if (verbose) {
            printf("Area of the rectangle is %lf .\n", fabs(rectangleArea));
        } // end if(verbose)

    } else { // if function has both positive and negative f(x) values on interval [a, b]
        // then the rectangle area should be calculated like this
        rectangleArea = width * height;

        if (verbose) {
            printf("Rectangle has points on both positive and negative side of y axis, and it's height is %lf .\n",
                   height);
            printf("Area of the rectangle is %lf .\n", fabs(rectangleArea));
        } // end if(verbose)
    } // end of if

    // set the seed for random number generator
    seed();

    for (unsigned int i = 1; i <= n; ++i) {

        // generate random coefficients
        xRandomCoefficient = zeroToOneUniformRandom();
        yRandomCoefficient = zeroToOneUniformRandom();

        // calculate random x and random f(x)
        x = a + width * xRandomCoefficient;
        fx = function_1_arg(expression, x);

        if (state > 0) { // if function is either entirely above x axis or below it
            // in this case one of boundaries is 0 so to find new y, just multiply height to coefficient
            y = height * yRandomCoefficient;
        } else { // if function has both positive and negative f(x) values on interval [a, b]
            // normal procedure to find new y
            y = min + height * yRandomCoefficient;
        }

        if (verbose) {
            printf("\nPoint No. [#%d]: (x, y) = (%lf, %lf) , f(x) = %lf .\n",
                   i, x, y, fx);
        } // end if(verbose)

        if (fabs(y) <= fabs(fx)) { // if |y| is lower than |f(x)|

            if (verbose) {
                printf("|y| is lower than |f(x)|, so this point is valid, ");
            } // end if(verbose)

            if (fx > 0 && y > 0) {
                // if it's above above x axis then add 1 to correct points
                correctPoints++;

                if (verbose) {
                    printf("and is placed on positive side of y.\n+1 for total valid points. total points = %d .\n",
                           correctPoints);
                } // end if(verbose)

            } else if (fx < 0 && y < 0) {
                // if it's below above x axis then subtract 1 to correct points
                correctPoints--;

                if (verbose) {
                    printf("and is placed on negative side of y.\n-1 for total valid points. total points = %d .\n",
                           correctPoints);
                } // end if(verbose)

            } // end of if (fx > 0 && y > 0) else if (fx < 0 && y < 0)
        } else { // if |y| is bigger than |f(x)|

            if (verbose) {
                printf("|y| is bigger than |f(x)|, so this point is not valid.\n");
            } // end if(verbose)

        }// end of if (fabs(y) <= fabs(fx))
    } // end of for loop

    if (verbose) {
        printf("\nTotal points = %d .\n", correctPoints);
        printf("Area = rectangle area *  total valid points / all points, area = %lf * %lf / %d .\n",
               fabs(rectangleArea), (double) correctPoints, n);
    } // end if(verbose)

    // calculate the estimated area under function
    area = fabs(rectangleArea) * (double) correctPoints / n;
    return area;
} //end of function monteCarloPointIntegration

double monteCarloRectangleIntegration(const char *expression, double a, double b, unsigned int n, int verbose) {
    /*
     * In this method we use the same approach as riemann sum rule
     * but the difference is we use random rectangles
     *
     * ARGUMENTS:
     * expressions  the function expression, it must be a string array like "x^2+1"
     * a             starting point of interval [a, b]
     * b             ending point of interval [a, b]
     * n             number of sub-intervals to use
     * verbose       show process {0: no, 1: yes}
     *
     */

    // fix interval reverse
    if (a > b){
        double temp = a;
        a = b;
        b = temp;
    } // end of if

    // check interval
    if (a == b) {
        printf("\nError: improper interval!\n");
        Exit(EXIT_FAILURE);
    } //end of interval check

    // check n to be more than zero
    // this is implemented to prevent divide by zero error
    if (n <= 0) {
        printf("\nError: argument n must be more than zero!\n");
        Exit(EXIT_FAILURE);
    } // end of n check

    // check verbose
    if (verbose != 0 && verbose != 1) {
        printf("\nError: verbose argument is not valid.\n");
        Exit(EXIT_FAILURE);
    } // end of if

    // initializing variables
    double area = 0, x , y;
    double coefficient = b - a;
    double width = coefficient / n;

    if (verbose) {
        printf("\nWidth of every rectangle is %lf .\n\n", width);
    } // end if(verbose)

    // set the seed for random number generator
    seed();

    for (unsigned int i = 1; i <= n; ++i) {
        // find a random x
        x =  a + coefficient * zeroToOneUniformRandom();
        // find it's height
        y = function_1_arg(expression, x);
        // sum all heights
        area += y ;

        if (verbose) {
            printf("Rectangle No. [#%d]: (x, height) = (%lf, %lf) , Total heights = %lf .\n", i, x, y, area);
        } // end if(verbose)

    } // end of for loop

    if (verbose) {
        printf("\nArea = Total heights * width , Area = %lf * %lf\n", area, width);
    } // end if(verbose)

    // multiply all heights to width of all rectangles to get area
    area *= width;
    return area;
} // end of function monteCarloRectangleIntegration