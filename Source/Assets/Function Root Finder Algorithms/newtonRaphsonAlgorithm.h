#ifndef C_MATH_NEWTONRAPHSONALGORITHM_H
#define C_MATH_NEWTONRAPHSONALGORITHM_H

double newtonRaphson(const char *expression, double x0, double ete, double ere, double tol, unsigned int maxiter,
                     int mode, int *state);
/*
 * In numerical analysis, Newton's method (also known as the Newton–Raphson method), named after Isaac Newton and
 * Joseph Raphson, is a method for finding successively better approximations to the roots (or zeroes) of
 * a real-valued function.
 * The Newton–Raphson method in one variable is implemented as follows:
 * The method starts with a function f defined over the real numbers x, the function's derivative f ′, and an initial
 * guess x0 for a root of the function f. If the function satisfies the assumptions made in the derivation of
 * the formula and the initial guess is close, then a better approximation x1 is:
 *
 * x1 = x0 - f(x0)/f'(x0)
 *
 * Geometrically, (x1, 0) is the intersection of the x-axis and the tangent of the graph of f at (x0, f (x0)).
 * The process is repeated until a sufficiently accurate value is reached.
 *
 * ARGUMENTS:
 * expressions  the function expression, it must be a pointer to a string array like "x^2+1"
 * x0           starting point
 * ete          estimated true error
 * ere          estimated relative error
 * tol          tolerance error
 * maxiter      maximum iteration threshold
 * mode         show process {0: no, 1: yes}
 * state        is answer found or not, will set value of state to 0 if no answers been found
 *
 */

#endif //C_MATH_NEWTONRAPHSONALGORITHM_H
