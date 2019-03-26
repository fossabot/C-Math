#ifndef C_MATH_GRADIENTDESCENTALGORITHM_H
#define C_MATH_GRADIENTDESCENTALGORITHM_H

double gradientDescent(const char *expression, double x0, double ete, double ere, double gamma, unsigned int maxiter,
                       int maximum, int verbose, int *state);

/*
 * Gradient descent is a first-order iterative optimization algorithm for finding the minimum of a function.
 * To find a local minimum of a function using gradient descent, one takes steps proportional to the negative of
 * the gradient (or approximate gradient) of the function at the current point.
 *
 * ARGUMENTS:
 * expressions  the function expression, it must be a string array like "x^2+1"
 * x0           starting point
 * ete          estimated true error
 * ere          estimated relative error
 * gamma        step size (also known as learning rate)
 * maxiter      maximum iteration threshold
 * maximum      this option will let user to find maximum instead of minimum {0: no, 1: yes}
 * verbose      show process {0: no, 1: yes}
 * state        is answer found or not
 *
 */

double gradientDescentInterval(const char *expression, double a, double b, double ete, double ere, double gamma,
                               unsigned int maxiter, int maximum, int verbose);
/*
 * Gradient descent is a first-order iterative optimization algorithm for finding the minimum of a function.
 * To find a local minimum of a function using gradient descent, one takes steps proportional to the negative of
 * the gradient (or approximate gradient) of the function at the current point.
 *
 * This function searches minimum/maximum on an interval [a, b]
 *
 * ARGUMENTS:
 * expressions  the function expression, it must be a string array like "x^2+1"
 * a            starting point of interval [a, b]
 * b            ending point of interval [a, b]
 * ete          estimated true error
 * ere          estimated relative error
 * gamma        step size (also known as learning rate)
 * maxiter      maximum iteration threshold
 * maximum      this option will let user to find maximum instead of minimum {0: no, 1: yes}
 * verbose      show process {0: no, 1: yes}
 *
 */

#endif //C_MATH_GRADIENTDESCENTALGORITHM_H
