#ifndef C_MATH_FALSEPOSITIONALGORITHM_H
#define C_MATH_FALSEPOSITIONALGORITHM_H

double
falsePosition(const char *expression, double a, double b, double ete, double ere, double tol, unsigned int maxiter,
              int options, int verbose, int *state);
/*
 * In mathematics, the false position method or regula falsi is a very old method for solving
 * an equation in one unknown, that, in modified form, is still in use. In simple terms,
 * the method is the trial and error technique of using test ("false") values for the variable
 * and then adjusting the test value according to the outcome. This is sometimes also referred
 * to as "guess and check". Versions of the method predate the advent of algebra and the use of equations.
 *
 * ARGUMENTS:
 * expressions   the function expression, it must be a string array like "x^2+1"
 * a             starting point of interval [a, b]
 * b             ending point of interval [a, b]
 * ete           estimated true error
 * ere           estimated relative error
 * tol           tolerance error
 * maxiter       maximum iteration threshold
 * options       use improvement algorithms  {0: no, 1: illinois, 2: anderson-bjork}
 * verbose       show process {0: no, 1: yes}
 * state         is answer found or not, will set value of state to 0 if no answers been found
 *
 */

#endif //C_MATH_FALSEPOSITIONALGORITHM_H
