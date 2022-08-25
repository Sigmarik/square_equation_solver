/**
 * @file main.c
 * @author Ilya Kudryashov (kudriashov.it@phystech.edu)
 * @brief Program for reading square equation (by coefficients A, B and C) and printing the solution.
 * @version 0.1
 * @date 2022-08-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdio.h>
#include <stdlib.h>

#include "rootsolver.h"
#include "mainio.h"
#include "debug.h"
#include "argparser.h"

static const char* pc_config_name = "rootsolver.conf";
static int b_show_imaginary = 1;

/**
 * @brief Fills config file with default values.
 * 
 * @param pf_config file to fill
 * 
 * @note Function does not check if pf_config is NULL.
 */
void fill_config(FILE* pf_config);

static const int NUMBER_OF_TAGS = 2;

/**
 * @brief Sets integer value (first pointer) to parsed value of argument.
 * 
 * @param argc number of arguments
 * @param argv pointers to arguments (1-st element should be int*)
 * @param argument argument as string
 */
void edit_int(const int argc, void** argv, const char* argument);

/**
 * @brief Prints poem about owls.
 * 
 * @param argc unimportant
 * @param argv unimportant
 * @param argument unimportant
 */
void print_owl(const int argc, void** argv, const char* argument);

/**
 * @brief Main function of the program. Reads 3 doubles from stdio and prints the solution of the equation.
 * 
 * @return exit status (0 if successful)
 */
int main(const int argc, const char** argv) {
    atexit(end_program);

    int i_log_thold = 1;
    void* log_thold_link_array[1] = {&i_log_thold};
    const struct ActionTag LINE_TAGS[NUMBER_OF_TAGS] = {
        {'O', "owl", {}, 0, print_owl, "prints 10 owls on the screen."},
        {'I', "importance", log_thold_link_array, 1, edit_int, "(in the form of -I[int]) sets log\n"
                                                               "    threshold to specified number.\n" 
                                                               "    Does not check if integer is specified."},
    };

    parse_args(argc, argv, NUMBER_OF_TAGS, LINE_TAGS);
    log_init("program_log.log", i_log_thold, &errno);

    printf("Square equation solver by Ilya Kudryashov.\n");
    printf("Program solves square equations in the form of A*x*x + B*x + C = 0\n");
    printf("Build from\n%s %s\n", __DATE__, __TIME__);

    _LOG_PRINTF_(ABSOLUTE_IMPORTANCE, "start", "Program started. Build from %s %s.\n", __DATE__, __TIME__);

    // Config file parsing.
    log_write("status", "Reading config file...", STATUS_REPORTS, &errno);

    FILE* pf_config = fopen(pc_config_name, "r");
    if (!pf_config || !fscanf(pf_config, "imaginary = %d", &b_show_imaginary)) {
        printf("No config file detected or it was corrupt, creating new file.\n");
        log_write("action", "config file corrupt/missing, creating new file.", AUTOMATIC_CORRECTIONS, &errno);

        if (pf_config) fclose(pf_config);
        FILE* pf_new_config = fopen(pc_config_name, "w");

        if (pf_new_config) {
            fill_config(pf_new_config);
        } else {
            log_write("ERROR", "failed to create config file.", ERROR_REPORTS, &errno);
        }
        
        fclose(pf_new_config);

        pf_config = fopen(pc_config_name, "r");
    }

    if (fclose(pf_config) == EOF) {
        log_write("ERROR", "failed to close config file.", ERROR_REPORTS, &errno);
    }

    log_write("status", "config file processing finished.", STATUS_REPORTS, &errno);
    log_write("status", "reading data from user...", STATUS_REPORTS, &errno);

    double d_a = 0, d_b = 0, d_c = 0;  // equation coefficients

    // Receive data from the user.
    read_double("A = ", &d_a);
    read_double("B = ", &d_b);
    read_double("C = ", &d_c);

    log_write("status", "finished reading data.", STATUS_REPORTS, &errno);
    _LOG_PRINTF_(STATUS_REPORTS + 1, "status", "user entered coefficients A = %lg, B = %lg, C = %lg.\n", d_a, d_b, d_c);
    log_write("status", "processing started.", STATUS_REPORTS, &errno);

    double pd_answers[4] = {};  // equation roots

    // Display equation to the user before major computations.
    printf("Equation:\n%gx2 + %gx + %g = 0\n", d_a, d_b, d_c);
    solve_square(d_a, d_b, d_c, pd_answers);

    _LOG_PRINTF_(STATUS_REPORTS + 1, "status", "estimated solution: X1 = %lg + %lg i, X2 = %lg + %lg i.\n", 
            pd_answers[0], pd_answers[1], pd_answers[2], pd_answers[3]);

    log_write("status", "printing solution...", STATUS_REPORTS, &errno);

    printf("Solution:\n");

    // Print solution(s) on the screen.
    print_solution(pd_answers, b_show_imaginary);

    return 0;
}

void fill_config(FILE* pf_config)  {
    fprintf(pf_config, "imaginary = %d", b_show_imaginary);
}

void edit_int(const int argc, void** argv, const char* argument) {
    *(int*)argv[0] = 0;
    *(int*)argv[0] = atoi(argument);
}

void print_owl(const int argc, void** argv, const char* argument) {
    printf("-Owl argument detected, dropping emergency supply of owls.\n");
    for (int i = 0; i < 10; i++) {
        printf(" A_____A\n");
        printf("((O)V(O))\n");
        printf(" \\ | | /\n");
    }
}