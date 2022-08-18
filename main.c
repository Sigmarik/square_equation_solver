/* 
main.c receves 3 floating point parameters (A, B and C) and prints
solution of the equation x * x * A + x * B + x * C = 0.
*/

#include <stdio.h>
#include <stdlib.h>

#include "rootsolver.h"

static int b_imaginary = 1;  // should program print imaginary solutions or not

void read_double(const char* pc_prefix, double* pd_variable);
void print_solution(const double* pd_answers);

// Tries to read 3 doubles corresponding to A, B and C equation coefficients.
// argc - argument count (including program name)
// argv - pointers to arguments
int main(int argc, char **argv) {
    double d_a = 0, d_b = 0, d_c = 0;  // equation coefficients
    double pd_answers[4] = {};  // equation roots
    FILE* pf_config = fopen("rootsolver.conf", "r");  // pointer to the rootsolver.conf file

    // Config file parsing.
    if (!pf_config || !fscanf(pf_config, "imaginary = %d", &b_imaginary)) {
        printf("No config file detected or it was corrupt, terminating.\n");
        return 1;
    }

    fclose(pf_config);

    // Receive data from the user.
    read_double("A = ", &d_a);
    read_double("B = ", &d_b);
    read_double("C = ", &d_c);

    // Display equation to the user before major computations.
    printf("Equation:\n%gx2 + %gx + %g = 0\n", d_a, d_b, d_c);
    solve(d_a, d_b, d_c, pd_answers);

    printf("Solution:\n");

    // Print solution(s) on the screen.
    print_solution(pd_answers);

    return 0;
}

// Prints pc_prefix and tries to read double until succeeds.
// pc_prefix - prefix to print before each request
// pd_variable - pointer to the variable to push the result
void read_double(const char* pc_prefix, double* pd_variable) {
    printf("%s", pc_prefix);
    while (!scanf("%lf", pd_variable)) {
        while (getchar() != '\n') /*pass*/;
        printf("Floating point argument expected.\n");
        printf("%s", pc_prefix);
    }
}

// Prints out the solution of the square equation in the fancy way.
// pd_answers - pointer to the array of at least 4 doubles with answers 
//              in the shape specified in rootsolver.c/void solve
//* Function has no protection from arrays smaller than required, so
//* it is possible for function to crash with segfault.
//* It is still intentional, though, as it may be usefull to
//* print values from the middle of some bigger array.
void print_solution(const double* pd_answers) {
    if (isnan(pd_answers[1])) {
        printf("Equation has no reperesentable solutions.\n");
        return;
    }
    if (i_dcmp(pd_answers[1], 0.0) == 0 && !b_imaginary) {
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