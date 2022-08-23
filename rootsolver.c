#include "rootsolver.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "debug.h"

int i_dcmp(const double d_a, const double d_b) {
    if (fabs(d_a - d_b) < 1e-10) return 0;
    if (d_a > d_b) return 1;
    else return -1;
}

double d_solve_linear(const double d_a, const double d_b) {
    if (!i_dcmp(d_a, 0.0)) {
        return i_dcmp(d_b, 0.0) ? NAN : INFINITY;
    }
    return -d_b / d_a;
}

void solve_square(const double d_a, const double d_b, const double d_c, double pd_answers[4]) {
    assert(pd_answers);
    if (!pd_answers) {
        errno = NULLPTR_ERROR;
        fprintf(stderr, "NULLPTR_ERROR: pd_answers in \"solve\" was NULL\n");
        exit(EXIT_FAILURE);
    }

    double d_discr = d_b * d_b - 4 * d_a * d_c;
    double d_delta = sqrt(fabs(d_discr));

    if (!i_dcmp(d_a, 0.0)) {
        pd_answers[0] = pd_answers[2] = d_solve_linear(d_b, d_c);
        pd_answers[1] = pd_answers[3] = 0.0;
        if (!i_dcmp(d_b, 0.0))
            for (int id = 0; id < 4; id++) pd_answers[id] = !i_dcmp(d_c, 0.0) ? INFINITY : NAN;
    } else if (!i_dcmp(d_c, 0.0)) {
        pd_answers[0] = 0.0;
        pd_answers[2] = d_solve_linear(d_a, d_b);
        pd_answers[1] = pd_answers[3] = 0.0;
    } else if (d_discr > 0) {
        pd_answers[0] = (-d_b - d_delta) / (2.0f * d_a);
        pd_answers[2] = (-d_b + d_delta) / (2.0f * d_a);
        pd_answers[1] = pd_answers[3] = 0;
    } else {
        pd_answers[0] = pd_answers[2] = -d_b / (2.0f * d_a);
        pd_answers[1] = -(pd_answers[3] = d_delta / (2.0f * d_a));
    }
}

void print_number(const double d_whole, const double d_imaginary) {
    printf("%g", d_whole);
    if (i_dcmp(d_imaginary, 0.0)) {
        printf(d_imaginary >= 0 ? " + " : " - ");
        printf("%gi", fabs(d_imaginary));
    }
}