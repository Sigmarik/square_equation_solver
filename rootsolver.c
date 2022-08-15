#include "rootsolver.h"

// Calculates descriminant of the equation by coefficients.
// pd_args - coefficients of the equation
static double d_discriminant(const double pd_args[3]) {
    return pd_args[1] * pd_args[1] - 4 * pd_args[0] * pd_args[2];
}

// Solves equation by given coefficients and inserts
// answers into pd_answers array as if 1-st and 4-th elements
// are rational parts of both answers and 2-nd and 3-rd elements
// are imaginary multiplyers.
// pd_args - coefficients of the equation
// pd_answers - array to put answers in
void solve(const double pd_args[3], double pd_answers[4]) {
    double d_discr = d_discriminant(pd_args);

    if (pd_args[0] == 0) {
        // In case if pd_args[1] = 0 function can insert nan,
        // which is intentional and serves as
        // a good indicator of unsolvable 
        // (or state-like) equation.
        pd_answers[0] = pd_answers[2] = -pd_args[2] / pd_args[1];
        pd_answers[1] = pd_answers[3] = 0.0 / pd_args[1];
    } else if (d_discr > 0) {
        pd_answers[0] = (-pd_args[1] - sqrt(d_discr)) / (2.0f * pd_args[0]);
        pd_answers[2] = (-pd_args[1] + sqrt(d_discr)) / (2.0f * pd_args[0]);
        pd_answers[1] = pd_answers[3] = 0;
    } else {
        pd_answers[0] = pd_answers[2] = -pd_args[1] / (2.0f * pd_args[0]);
        pd_answers[1] = -(pd_answers[3] = sqrt(-d_discr) / (2.0f * pd_args[0]));
    }
}