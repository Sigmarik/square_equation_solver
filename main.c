/* 
main.c receves 3 floating point parameters (A, B and C) and prints
solution of the equation x * x * A + x * B + x * C = 0.
*/

#include <stdio.h>
#include <stdlib.h>

#include "rootsolver.h"

static const double EPS = 1e-10;  // double comparison accuracy

static int b_imaginary = 1;  // should program print imaginary solutions or not

void read_double(const char* pc_prefix, double* pd_variable);
void print_solution(const double* pd_answers);
void print_imaginary(const double d_whole, const double d_imaginary);

// Tries to read 3 doubles corresponding to A, B and C equation coefficients.
// argc - argument count (including program name)
// argv - pointers to arguments
int main(int argc, char **argv) {
    double d_a = 0, d_b = 0, d_c = 0;  // equation coefficients
    double pd_answers[4] = {};  // equation roots
    int i_argument_iterator = -1;  // iterator
    int b_wrong_input = 0;  // was wrong input detected
    FILE* pf_config = fopen("rootsolver.conf", "r");  // pointer to the rootsolver.conf file

    // Config file parsing.
    if (!pf_config || !fscanf(pf_config, "imaginary = %d", &b_imaginary)) {
        printf("No config file detected or it was corrupt, terminating.\n");
        return 1;
    }

    // Receive data from the user.
    read_double("A = ", &d_a);
    read_double("B = ", &d_b);
    read_double("C = ", &d_c);

    // Display equation to the user before major computations.
    printf("Equation:\n%gx2 + %gx + %g = 0\n", d_a, d_b, d_c);
    solve(d_a, d_b, d_c, pd_answers);

    printf("Solution:\n");

    // Check if equation has representable solutions.
    if (isnan(pd_answers[1])) {
        if (d_c == 0) {
            printf("Equation is always true.\n");
        } else {
            printf("Equation has no roots.\n");
        }
        return 0;
    }

    // Print solution(s) on the screen.
    print_solution(pd_answers);

    return 0;
}

// Prints pc_prefix and tries to read double until succeeds.
// pc_prefix - prefix to print before each request
// pd_variable - pointer to the variable to push the result
void read_double(const char* pc_prefix, double* pd_variable) {
    int b_success = 0;

    printf("%s", pc_prefix);
    while (b_success = !scanf("%lf", pd_variable)) {
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
    if (fabs(pd_answers[1]) > EPS && !b_imaginary) {
        printf("Solution contains imaginary numbers.\nChange config file to see them.\n");
        return;
    }
    if (pd_answers[0] == pd_answers[2] && pd_answers[1] == pd_answers[3]) {
        printf("X = ");
        print_imaginary(pd_answers[0], pd_answers[1]);
    } else {
        printf("X1 = ");
        print_imaginary(pd_answers[0], pd_answers[1]);
        printf("\nX2 = ");
        print_imaginary(pd_answers[2], pd_answers[3]);
    }
    printf("\nChange config file to disable imaginary solutions.\n");
}

// Prints complex numbers containing both normal and imaginary part.
// d_whole - "normal" part of the number
// d_imaginary - imaginary part of the number
void print_imaginary(const double d_whole, const double d_imaginary) {
    printf("%g", d_whole);
    if (b_imaginary && fabs(d_imaginary) > EPS) {
        printf(d_imaginary >= 0 ? " + " : " - ");
        printf("%gi", fabs(d_imaginary));
    }
}