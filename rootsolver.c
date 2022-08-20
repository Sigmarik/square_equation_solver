/*
rootsolver.c - module for solving square equations using descriminant method.
*/

// Utility
#include <stdio.h>
#include <stdlib.h>

// Headers
#include "rootsolver.h"

// Compares two doubles and returns sign(a - b)
// d_a - first component
// d_b - second component
// eps (optional) - max error in which numbers are considered to be equal.
int i_dcmp(const double d_a, const double d_b) {
    if (fabs(d_a - d_b) < 1e-10) return 0;
    if (d_a > d_b) return 1;
    else return -1;
}

// Solves equation by given coefficients and inserts
// answers into pd_answers array as if 1-st and 3-rd elements
// are rational parts of both answers and 2-nd and 4-th elements
// are imaginary multiplyers.
// d_a - A coefficient
// d_b - B coefficient
// d_c - C coefficient
// pd_answers - array to put answers in
void solve(const double d_a, const double d_b, const double d_c, double pd_answers[4]) {
    assert(pd_answers);
    if (!pd_answers) {
        errno = NULLPTR_ERROR;
        fprintf(stderr, "NULLPTR_ERROR: pd_answers in \"solve\" was NULL\n");
        exit(EXIT_FAILURE);
    }

    double d_discr = d_b * d_b - 4 * d_a * d_c;
    double d_delta = sqrt(fabs(d_discr));

    int b_valid_equation = d_a || d_b;

    if (!b_valid_equation) {
        errno = INPUT_ERROR;
        fprintf(stderr, "Wrong equation arguments. Equation has infinite / zero roots.\n");
        exit(EXIT_FAILURE);
    }

    if (!i_dcmp(d_a, 0.0)) {
        // In case if pd_args[1] = 0 function can insert nan,
        // which is intentional and serves as
        // a good indicator of unsolvable 
        // (or state-like) equation.
        pd_answers[0] = pd_answers[2] = -d_c / d_b;
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

// Prints complex numbers containing both normal and imaginary part.
// d_whole - "normal" part of the number
// d_imaginary - imaginary part of the number
void print_number(const double d_whole, const double d_imaginary) {
    printf("%g", d_whole);
    if (i_dcmp(d_imaginary, 0.0)) {
        printf(d_imaginary >= 0 ? " + " : " - ");
        printf("%gi", fabs(d_imaginary));
    }
}