#include "mainio.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "dbg/debug.h"
#include "utils.h"

#define PRECONDITION

void read_double(const char* prefix, double* variable, int* error_code) {
    _LOG_FAIL_CHECK_(prefix && variable, "warning", WARNINGS, return;, error_code, NULLPTR_ERROR);

    printf("%s", prefix);
    while (!scanf("%lf", variable)) {

        while (getchar() != '\n') {};

        printf("Floating point argument expected.\n");
        printf("%s", prefix);
    }
}

void print_solution(const double* answers, const int show_imaginary, int* error_code) {
    _LOG_FAIL_CHECK_(answers, "error", ERROR_REPORTS, return;, error_code, NULLPTR_ERROR);

    if (isnan(answers[0])) {
        printf("Equation has no solutions.\n");
        return;
    } else if (isinf(answers[0])) {
        printf("Equation has infinite solutions.\n");
        return;
    }
    if (doublecmp(answers[1], 0.0) == 0 && !show_imaginary) {
        printf("Equation has no solutions in non-imaginary numbers.\nChange config file to see imaginary solutions.\n");
        return;
    }
    if (doublecmp(answers[0], answers[2]) == 0 && doublecmp(answers[1], answers[3]) == 0) {  // Print only one root
        printf("X = ");
        print_number(answers[0], answers[1]);
    } else {  // Print two roots
        printf("X1 = ");
        print_number(answers[0], answers[1]);
        printf("\nX2 = ");
        print_number(answers[2], answers[3]);
    }
    printf("\nChange config file to disable imaginary solutions.\n");
}
