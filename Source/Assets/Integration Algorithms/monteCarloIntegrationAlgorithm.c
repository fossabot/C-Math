#include "monteCarloIntegrationAlgorithm.h"
#include "../Optimization Algorithms/simpleMaxMinFinderAlgorithm.h"
#include "../Util/randomGenerator.h"
#include "../Util/functions.h"
#include "../Util/util.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double monteCarloIntegration(const char *expression, double a, double b, unsigned int n, unsigned int options){
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
     *
     */

    // check mode and options value
    if (options != 0 && options != 1){
        printf("\nError: arguments option or mode are not valid\n");
        Exit();
        exit(EXIT_FAILURE);
    } // end of if

    // check n to be more than zero
    // this is implemented to prevent divide by zero error
    if (n <= 0) {
        printf("Error: argument n must be more than zero!\n");
        Exit();
        exit(EXIT_FAILURE);
    } // end of ete check

    // use requested type of monte carlo integration
    switch (options){
        case 0:
            return monteCarloPointIntegration(expression, a, b, n);
        case 1:
            return monteCarloRectangleIntegration(expression, a, b, n);
    } // end of switch
} // end of function monteCarloIntegration

double monteCarloPointIntegration(const char *expression, double a, double b, unsigned int n) {
    /*
     * In this method we use random points and then calculate the area under function based on
     * proportional relation between points under the curve of function and all points to the area
     * of rectangle which surrounds whole function
     *
     * ARGUMENTS:
     * expressions  the function expression, it must be a string array like "x^2+1"
     * a             starting point of interval [a, b]
     * b             ending point of interval [a, b]
     * n             number of sub-intervals to use
     *
     */

    // check n to be more than zero
    // this is implemented to prevent divide by zero error
    if (n <= 0) {
        printf("Error: argument n must be more than zero!\n");
        Exit();
        exit(EXIT_FAILURE);
    } // end of ete check

    // find maximum and minimum of function
    double *extremum = simpleMaxMinFinder(expression, a, b, n);
    double max = extremum[0], min = extremum[1];

    // initializing variables
    double area, rectangleArea, x, y, h, fx;
    int correctPoints = 0;

    // calculate rectangle area
    if (max * min > 0) { // if function is either entirely above x axis or below it
        if (max > 0) {
            // if it's above x axis then the upper bound of rectangle is
            // the maximum of the function and lower bound in x = 0
            h = max;
        } else {
            // if it's below x axis then the upper bound of rectangle is
            // x = 0 and lower bound is the minimum of the function
            h = min;
        }
        // the area of the rectangle in this case is the distance between
        // a and b multiplied by distance between lower and upper bound which is always h
        rectangleArea = (b - a) * h;
    } else { // if function has both positive and negative f(x) values on interval [a, b]
        // then the rectangle area should be calculated like this
        rectangleArea = (b - a) * (max - min);
    } // end of if

    // set the seed for random number generator
    seed();

    for (unsigned int i = 0; i <= n; ++i) {

        // generate random coefficients
        double xRandomCoefficient = zeroToOneUniformRandom();
        double yRandomCoefficient = zeroToOneUniformRandom();

        // calculate random x and random f(x)
        x = a + (b - a) * xRandomCoefficient;
        fx = function_1_arg(expression, x);

        if (max * min > 0) { // if function is either entirely above x axis or below it
            // in this case one of boundaries is 0 so to find new y, just multiply h to coefficient
            y = h * yRandomCoefficient;
        } else { // if function has both positive and negative f(x) values on interval [a, b]
            // normal procedure to find new y
            y = min + (max - min) * yRandomCoefficient;
        }

        if (fabs(y) <= fabs(fx)) { // if |y| is lower than |f(x)|
            if (fx > 0 && y > 0) {
                // if it's above above x axis then add 1 to correct points
                correctPoints++;
            } else if (fx < 0 && y < 0) {
                // if it's below above x axis then subtract 1 to correct points
                correctPoints--;
            } // end of if (fx > 0 && y > 0) else if (fx < 0 && y < 0)
        } // end of if (fabs(y) <= fabs(fx))
    } // end of for loop

    // calculate the estimated area under function
    area = fabs(rectangleArea) * (double) correctPoints / n;
    return area;
} //end of function monteCarloPointIntegration

double monteCarloRectangleIntegration(const char *expression, double a, double b, unsigned int n){
    /*
     * In this method we use the same approach as riemann sum rule
     * but the difference is we use random rectangles
     *
     * ARGUMENTS:
     * expressions  the function expression, it must be a string array like "x^2+1"
     * a             starting point of interval [a, b]
     * b             ending point of interval [a, b]
     * n             number of sub-intervals to use
     *
     */


    // check n to be more than zero
    // this is implemented to prevent divide by zero error
    if (n <= 0) {
        printf("Error: argument n must be more than zero!\n");
        Exit();
        exit(EXIT_FAILURE);
    } // end of ete check

    // initializing variables
    double area = 0, x , y;
    double coefficient = b - a;
    double width = coefficient / n;

    // set the seed for random number generator
    seed();

    for (unsigned int i = 0; i <= n ; ++i) {
        // find a random x
        x =  a + coefficient * zeroToOneUniformRandom();
        // find it's height
        y = function_1_arg(expression, x);
        // sum all heights
        area += y ;
    } // end of for loop

    // multiply al heights to width of all rectangles to get total sum
    area *= width;
    return area;
} // end of function monteCarloRectangleIntegration