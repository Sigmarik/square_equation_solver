/**
 * @file rootsolver_unitest.cpp
 * @author Ilya Kudryashov (kudriashov.it@phystech.edu)
 * @brief Unitests for mudule rootsolver.
 * @version 0.1
 * @date 2022-08-24
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdio.h>
#include <stdlib.h>

#include "debug.h"

#include "rootsolver.h"

/**
 * @brief Compares two double arrays and returns 1 if they are equal.
 * 
 * @param pd_a first array
 * @param pd_b second array
 * @param num_elements lengths of two arrays
 * @return bool pd_a == pd_b
 */
int compare_answers(const double* pd_a, const double* pd_b, const int num_elements);

/**
 * @brief Prints out the output of the function solve_square() from rootsolver module.
 * 
 * @param pd_result result of the solve_square() function
 */
void print_result(const double* pd_result);

/**
 * @brief Reads single test from stdin.
 * 
 * @param pd_a coefficient A
 * @param pd_b coefficient B
 * @param pd_c coefficient C
 * @param pd_expected expected solution
 * @return bool was readling successful
 */
int read_test(double* pd_a, double* pd_b, double* pd_c, double* pd_expected);

int main(void) {
    int exec_result = 0;

    printf("Running predefined tests:\n");

    double d_a = 0, d_b = 0, d_c = 0;
    double pd_result[4] = {};
    double pd_expected[4] = {};

    for (int test_id = 0; read_test(&d_a, &d_b, &d_c, pd_expected); test_id++) {
        solve_square(d_a, d_b, d_c, pd_result);

        if (!compare_answers(pd_result, pd_expected, 4)) {

            printf("WA: test %d failed!\n", test_id);
            printf("A = %lg, B = %lg, C = %lg\n", d_a, d_b, d_c);

            printf("Expected:\n");
            print_result(pd_expected);

            printf("Got:\n");
            print_result(pd_result);

            exec_result = EXIT_FAILURE;

        } else printf("OK: test %d passed.\n", test_id);
    }

    return exec_result;
}

int compare_answers(const double* pd_a, const double* pd_b, const int num_elements) {
    for (int id = 0; id < num_elements; id++) {
        if (i_dcmp(pd_a[id], pd_b[id])) return 0;
    }
    return 1;
}

void print_result(const double* pd_result) {
    printf("X1 = %lg + %lg i,  ", pd_result[0], pd_result[1]);
    printf("X2 = %lg + %lg i\n",  pd_result[2], pd_result[3]);
}

int read_test(double* pd_a, double* pd_b, double* pd_c, double pd_expected[4]) {
    if (!scanf("i %lf %lf %lf\n", pd_a, pd_b, pd_c)) return 0;
    if (scanf("o %lf %lf %lf %lf\n", 
        &pd_expected[0], &pd_expected[1], &pd_expected[2], &pd_expected[3]) < 4) return 0;
    return 1;
}