#ifndef C_MATH_GRADIENTDESCENT_H
#define C_MATH_GRADIENTDESCENT_H
#define INPUT_SIZE 16

double gradientDescent(const char *expression, double x0, double error, double gamma, int maxiter, int mode, int *state);

#endif //C_MATH_GRADIENTDESCENT_H
