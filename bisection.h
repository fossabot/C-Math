#ifndef C_MATH_BISECTION_H
#define C_MATH_BISECTION_H

double function(double x);

double bisection(double a, double b, double ete, double ere, double tol, int maxiter, int mode, int *state);

#endif //C_MATH_BISECTION_H
