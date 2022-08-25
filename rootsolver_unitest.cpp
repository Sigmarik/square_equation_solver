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
 * @return int 1 in case of EOF, 2 in case of corruption and 0 if reading was successful.
 */
int read_test(double* pd_a, double* pd_b, double* pd_c, double* pd_expected);

/**
 * @brief Detects if file is corrupt.
 * 
 * @param expectation next character expected to be in input
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

int main(void) {
    atexit(end_programm);

    log_init("rootsolver_tester.log", AUTOMATIC_CORRECTIONS);

    int exec_result = 0;

    printf("Running predefined tests:\n");

    double d_a = 0, d_b = 0, d_c = 0;
    double pd_result[4] = {};
    double pd_expected[4] = {};

    log_write("status", "reading file with tests...", STATUS_REPORTS, &errno);

    int test_count = 0;
    int read_result = 0;
    for (int test_id = 0; 
        ((read_result = read_test(&d_a, &d_b, &d_c, pd_expected)) & 1) == 0; /*if in {0, 2}*/ 
        test_id++, test_count++) {
        
        if (read_result) {
            printf("SK: Test %d was skipped due to corruption.\n", test_id);
            exec_result = 1;
            continue;
        }

        if (log_file()) {
            log_prefix("status", STATUS_REPORTS + 1);
            fprintf(log_file(STATUS_REPORTS + 1), "Test %d detected. Processing...\n", test_id);
        }

        int err_code = 0;
        solve_square(d_a, d_b, d_c, pd_result, &err_code);

        if (log_file()) {
            log_prefix("status", STATUS_REPORTS + 1);
            fprintf(log_file(STATUS_REPORTS + 1), "Test %d processed. Verifying...\n", test_id);
        }

        if (err_code || !compare_answers(pd_result, pd_expected, 4)) {

            log_write("status", "Test failed.", STATUS_REPORTS + 1, &errno);
            
            if (err_code) {
                printf("RE");  // Runtime Error
            } else {
                printf("WA");  // Wrong Answer
            }

            printf(": Test %d failed!\n", test_id);
            printf("  A = %lg, B = %lg, C = %lg\n", d_a, d_b, d_c);

            printf("  Expected:\n  ");
            print_result(pd_expected);

            printf("  Got:\n  ");
            print_result(pd_result);

            exec_result = EXIT_FAILURE;

        } else {
            printf("OK: Test %d passed.\n", test_id);
            log_write("status", "Test successful.", STATUS_REPORTS + 1, &errno);
        }
    }
    log_write("status", "EOF detected. Reading and testing was terminated.", STATUS_REPORTS, &errno);

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
    int status = 0;
    if (!scanf("i %lf %lf %lf\n", pd_a, pd_b, pd_c)) {
        //if (skip_line(&status)) return 1;
        //return 1;
    }
    if (scanf("o %lf %lf %lf %lf\n", 
        &pd_expected[0], &pd_expected[1], &pd_expected[2], &pd_expected[3]) < 4) {
        
        if (skip_line(&status)) return 1;
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
        log_write("warning", "Wrong character detected. Skipping to the next line.", WARNINGS, &errno);
        *status = 2;
        return 0;
    } return 1;
}