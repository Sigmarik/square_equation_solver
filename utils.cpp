#include "utils.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int doublecmp(const double d_a, const double d_b) {
    if (fabs(d_a - d_b) < 1e-10) return 0;
    if (d_a > d_b) return 1;
    else return -1;
}


void print_number(const double d_whole, const double d_imaginary) {
    printf("%g", d_whole);
    if (doublecmp(d_imaginary, 0.0)) {
        printf(d_imaginary >= 0 ? " + " : " - ");
        printf("%gi", fabs(d_imaginary));
    }
}