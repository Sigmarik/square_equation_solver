#include "rootsolver.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "util/dbg/debug.h"
#include "util/utils.h"

double solve_linear(const double coef_a, const double coef_b) {
    if (!doublecmp(coef_a, 0.0)) {
        return doublecmp(coef_b, 0.0) ? NAN : INFINITY;
    }
    return -coef_b / coef_a;
}

void solve_square(const double coef_a, const double coef_b, const double coef_c, double answers[4], int* error_code) {
    _LOG_FAIL_CHECK_(answers, "warning", WARNINGS, return;, error_code, NULLPTR_ERROR);

    double discriminant = coef_b * coef_b - 4 * coef_a * coef_c;
    double delta = sqrt(fabs(discriminant));

    if (!doublecmp(coef_a, 0.0)) {
        answers[0] = answers[2] = solve_linear(coef_b, coef_c);
        answers[1] = answers[3] = 0.0;
        if (!doublecmp(coef_b, 0.0))
            for (int id = 0; id < 4; id++) answers[id] = !doublecmp(coef_c, 0.0) ? INFINITY : NAN;
    } else if (!doublecmp(coef_c, 0.0)) {
        answers[0] = 0.0;
        answers[2] = solve_linear(coef_a, coef_b);

        if (answers[2] < 0.0) {
            answers[0] = answers[2];
            answers[2] = 0.0;
        }
        
        answers[1] = answers[3] = 0.0;
    } else if (discriminant > 0) {

        answers[0] = (-coef_b - delta) / (2.0f * coef_a);
        answers[1] = answers[3] = 0;
        answers[2] = (-coef_b + delta) / (2.0f * coef_a);
    
    } else {
        answers[0] = answers[2] = -coef_b / (2.0f * coef_a);
        answers[1] = -(answers[3] = delta / (2.0f * coef_a));
    }
}
