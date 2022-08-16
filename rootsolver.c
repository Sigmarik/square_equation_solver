/*
rootsolver.c - module for solving square equations using descriminant method.
*/

#include "rootsolver.h"

static const double EPS = 1e-10;  // double comparison accuracy

// Solves equation by given coefficients and inserts
// answers into pd_answers array as if 1-st and 3-rd elements
// are rational parts of both answers and 2-nd and 4-th elements
// are imaginary multiplyers.
// d_a - A coefficient
// d_b - B coefficient
// d_c - C coefficient
// pd_answers - array to put answers in
void solve(const double d_a, const double d_b, const double d_c, double pd_answers[4]) {
    double d_discr = d_b * d_b - 4 * d_a * d_c;
    double d_delta = sqrt(fabs(d_discr));

    if (fabs(d_a) < EPS) {
        // In case if pd_args[1] = 0 function can insert nan,
        // which is intentional and serves as
        // a good indicator of unsolvable 
        // (or state-like) equation.
        pd_answers[0] = pd_answers[2] = d_c / d_b;
        pd_answers[1] = pd_answers[3] = 0.0 / d_b;
    } else if (d_discr > 0) {
        pd_answers[0] = (-d_b - d_delta) / (2.0f * d_a);
        pd_answers[2] = (-d_b + d_delta) / (2.0f * d_a);
        pd_answers[1] = pd_answers[3] = 0;
    } else {
        pd_answers[0] = pd_answers[2] = -d_b / (2.0f * d_a);
        pd_answers[1] = -(pd_answers[3] = d_delta / (2.0f * d_a));
    }
}