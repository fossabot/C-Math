#ifndef C_MATH_GRADIENTASCENTALGORITHM_H
#define C_MATH_GRADIENTASCENTALGORITHM_H

double gradientAscent(const char *expression, double x0, double ete, double ere, double gamma, unsigned int maxiter,
                      int verbose, int *state);

/*
 * Gradient descent is a first-order iterative optimization algorithm for finding the maximum of a function.
 * To find a local maximum of a function using gradient ascent, one takes steps proportional to the positive of
 * the gradient (or approximate gradient) of the function at the current point.
 *
 * ARGUMENTS:
 * expressions  the function expression, it must be a string array like "x^2+1"
 * x0           starting point
 * ete          estimated true error
 * ere          estimated relative error
 * gamma        step size (also known as learning rate)
 * maxiter      maximum iteration threshold
 * verbose      show process {0: no, 1: yes}
 * state        is answer found or not
 *
 */

double gradientAscentInterval(const char *expression, double a, double b, double ete, double ere, double gamma,
                              unsigned int maxiter, int verbose);
/*
 * Gradient descent is a first-order iterative optimization algorithm for finding the maximum of a function.
 * To find a local maximum of a function using gradient ascent, one takes steps proportional to the positive of
 * the gradient (or approximate gradient) of the function at the current point.
 *
 * This function searches maximum on an interval [a, b]
 *
 * ARGUMENTS:
 * expressions  the function expression, it must be a string array like "x^2+1"
 * a            starting point of interval [a, b]
 * b            ending point of interval [a, b]
 * ete          estimated true error
 * ere          estimated relative error
 * gamma        step size (also known as learning rate)
 * maxiter      maximum iteration threshold
 * verbose      show process {0: no, 1: yes}
 *
 */

#endif //C_MATH_GRADIENTASCENTALGORITHM_H
