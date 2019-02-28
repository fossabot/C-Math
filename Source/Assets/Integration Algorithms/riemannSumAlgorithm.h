#ifndef C_MATH_RIEMANNSUMALGORITHM_H
#define C_MATH_RIEMANNSUMALGORITHM_H

double riemannSum(const char *expression, double a, double b, unsigned int n, int options, int verbose);
/*
 * In mathematics, a Riemann sum is a certain kind of approximation of an integral by a finite sum. It is named
 * after nineteenth century German mathematician Bernhard Riemann. One very common application is approximating
 * the area of functions or lines on a graph, but also the length of curves and other approximations.
 * The sum is calculated by dividing the region up into shapes (rectangles, trapezoids, parabolas, or cubic) that
 * together form a region that is similar to the region being measured, then calculating the area for each of these
 * shapes, and finally adding all of these small areas together. This approach can be used to find
 * a numerical approximation for a definite integral even if the fundamental theorem of calculus
 * does not make it easy to find a closed-form solution.
 *
 * ARGUMENTS:
 * expressions   the function expression, it must be a string array like "x^2+1"
 * a             starting point of interval [a, b]
 * b             ending point of interval [a, b]
 * n             number of sub-intervals to use
 * options       which point of sub-interval to use  {0: left point, 1: right point, 2: mid point}
 * verbose       show process {0: no, 1: yes}
 *
 */

#endif //C_MATH_RIEMANNSUMALGORITHM_H
