#ifndef C_MATH_FALSEPOSITIONALGORITHM_H
#define C_MATH_FALSEPOSITIONALGORITHM_H

double
falsePosition(const char *expression, double a, double b, double ete, double ere, double tol, unsigned int maxiter,
              int options, int mode, int *state);

#endif //C_MATH_FALSEPOSITIONALGORITHM_H