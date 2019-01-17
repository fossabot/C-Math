#ifndef C_MATH_FALSEPOSITION_H
#define C_MATH_FALSEPOSITION_H

double
falsePosition(const char *expression, double a, double b, double ete, double ere, double tol, int maxiter, int mode,
              int *state);

#endif //C_MATH_FALSEPOSITION_H
