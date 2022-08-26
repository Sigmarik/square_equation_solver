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
#include <ctype.h>

#include "lib/util/dbg/debug.h"

#include "lib/rootsolver.h"
#include "lib/util/utils.h"

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

enum TEST_READING_RESULTS {
    READ_SUCCESSFUL,
    READ_EOF,
    READ_CORRUPTION,
};

/**
 * @brief Reads single test from stdin.
 * 
 * @param pd_a coefficient A
 * @param pd_b coefficient B
 * @param pd_c coefficient C
 * @param pd_expected expected solution
 * @return int READ_EOF, READ_CORRYPTION or READ_SUCCESSFUL.
 */
int read_test(double* pd_a, double* pd_b, double* pd_c, double* pd_expected);

/**
 * @brief Detects unexpected characters.
 * 
 * @return int 0 if everything is fine and 1 othervise
 */
int check_input();

/**
 * @brief Skips one line of input, prints specific warning in log files and updates status.
 * 
 * @param status 
 * @param case 
 */
int skip_line(int* status);

/**
 * @brief Prints out IO of the test.
 * 
 * @param d_a A coefficient
 * @param d_b B coefficient
 * @param d_c C coefficient
 * @param pd_expected expected answer
 * @param pd_result received answer
 */
void print_test_info(const double d_a, const double d_b, const double d_c, 
                     const double * const pd_expected, const double * const pd_result);

enum TEST_RESULTS {
    TEST_SUCCESS,
    TEST_FAIL,
};

int main(void) {
    atexit(log_end_program);
    log_init("rootsolver_tester.log", AUTOMATIC_CORRECTIONS);

    int exec_result = TEST_SUCCESS;

    printf("Running predefined tests:\n");

    double d_a = 0, d_b = 0, d_c = 0, pd_result[4] = {}, pd_expected[4] = {};

    log_printf(STATUS_REPORTS, "status", "reading file with tests...\n");

    int read_result = 0;
    for (int test_id = 0; 
        (read_result = read_test(&d_a, &d_b, &d_c, pd_expected)) != READ_EOF;
        test_id++) {
        
        if (read_result) {
            printf("SK: Test %d was skipped due to corruption.\n", test_id);
            exec_result = TEST_FAIL;
            continue;
        }

        log_printf(STATUS_REPORTS + 1, "status", "Test %d detected. Processing...\n", test_id);

        int err_code = 0;
        solve_square(d_a, d_b, d_c, pd_result, &err_code);

        log_printf(STATUS_REPORTS + 1, "status", "Test %d detected. Verifying...\n", test_id);

        if (err_code || !compare_answers(pd_result, pd_expected, 4)) {
            printf(err_code ? "RE" : "WA");
            printf(": Test %d failed!\n", test_id);
            print_test_info(d_a, d_b, d_c, pd_expected, pd_result);
            exec_result = TEST_FAIL;
        } else {
            printf("OK: Test %d passed.\n", test_id);
            log_printf(STATUS_REPORTS + 1, "status", "Test successful.\n");
        }
    }
    log_printf(STATUS_REPORTS, "status", "EOF detected. Reading and testing was terminated.\n");

    return exec_result;
}

int compare_answers(const double* pd_a, const double* pd_b, const int num_elements) {
    for (int id = 0; id < num_elements; id++) {
        if (doublecmp(pd_a[id], pd_b[id])) return 0;
    }
    return 1;
}

void print_result(const double* pd_result) {
    printf("X1 = %lg + %lg i,  ", pd_result[0], pd_result[1]);
    printf("X2 = %lg + %lg i\n",  pd_result[2], pd_result[3]);
}

int read_test(double* pd_a, double* pd_b, double* pd_c, double pd_expected[4]) {
    int status = READ_SUCCESSFUL;
    scanf("i %lf %lf %lf\n", pd_a, pd_b, pd_c);
    if (scanf("o %lf %lf %lf %lf\n", 
        &pd_expected[0], &pd_expected[1], &pd_expected[2], &pd_expected[3]) < 4) {
        
        if (skip_line(&status)) return READ_EOF;
    }
    return status;
}

int check_input() {
    char next_symb = getchar();
    ungetc(next_symb, stdin);
    if (next_symb == EOF) {
        return 0;
    }
    return 1;
}

int skip_line(int* status) {
    if (check_input() == 1) {
        while (getchar() != '\n');
        log_printf(WARNINGS, "warning", "Unexpected character detected. Skipping to the next line.\n");
        *status = READ_CORRUPTION;
        return 0;
    } return 1;
}

void print_test_info(const double d_a, const double d_b, const double d_c, 
                       const double * const pd_expected, const double * const pd_result) {
    
    log_printf(STATUS_REPORTS + 1, "status", "Test failed.\n");

    printf("  A = %lg, B = %lg, C = %lg\n", d_a, d_b, d_c);

    printf("  Expected:\n  ");
    print_result(pd_expected);

    printf("  Got:\n  ");
    print_result(pd_result);
}