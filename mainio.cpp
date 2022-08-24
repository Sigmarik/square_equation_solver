#include "mainio.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "debug.h"
#include "rootsolver.h"

#define PRECONDITION

void read_double(const char* pc_prefix, double* pd_variable) {
    log_assert(pc_prefix && pd_variable, "warning", WARNINGS, return;);
    // if (!pc_prefix || !pd_variable) {
    //     errno = NULLPTR_ERROR;
    //     fprintf(stderr, "NULLPTR_ERROR: Null pointer detected in function \"read_double\". Terminating.\n");
    //     exit(EXIT_FAILURE);
    //     }
    // }

    printf("%s", pc_prefix);
    while (!scanf("%lf", pd_variable)) {

        while (getchar() != '\n') {};

        printf("Floating point argument expected.\n");
        printf("%s", pc_prefix);
    }
}

void print_solution(const double* pd_answers, const int b_show_imaginary) {
    log_assert(pd_answers, "error", ERROR_REPORTS, return;);
    // if (!pd_answers) {
    //     errno = NULLPTR_ERROR;
    //     fprintf(stderr, "NULLPTR_ERROR: pd_answers in \"print_solution\" was NULL\n");
    //     exit(EXIT_FAILURE);
    // }

    if (isnan(pd_answers[0])) {
        printf("Equation has no solutions.\n");
        return;
    } else if (isinf(pd_answers[0])) {
        printf("Equation has infinite solutions.\n");
        return;
    }
    if (i_dcmp(pd_answers[1], 0.0) == 0 && !b_show_imaginary) {
        printf("Equation has no solutions in non-imaginary numbers.\nChange config file to see imaginary solutions.\n");
        return;
    }
    if (i_dcmp(pd_answers[0], pd_answers[2]) == 0 && i_dcmp(pd_answers[1], pd_answers[3]) == 0) {  // Print only one root
        printf("X = ");
        print_number(pd_answers[0], pd_answers[1]);
    } else {  // Print two roots
        printf("X1 = ");
        print_number(pd_answers[0], pd_answers[1]);
        printf("\nX2 = ");
        print_number(pd_answers[2], pd_answers[3]);
    }
    printf("\nChange config file to disable imaginary solutions.\n");
}
