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
static int show_imaginary = 1;

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
 * @brief Prints poem about owls.
 * 
 * @param argc unimportant
 * @param argv unimportant
 * @param argument unimportant
 */
void print_owl(const int argc, void** argv, const char* argument);

/**
 * @brief Prints program label and build date/time to console.
 * 
 */
void print_label();

/**
 * @brief Reads config file and applies it.
 * 
 */
void read_config();

/**
 * @brief Read 3 coefficients from the console.
 * 
 * @param[out] a coefficient A
 * @param[out] b coefficient B
 * @param[out] c coefficient C
 */
void read_coefficients(double* a, double* b, double* c);

static int log_threshold = 1;
static void* __log_threshold_array[1] = {&log_threshold};

static const struct ActionTag LINE_TAGS[NUMBER_OF_TAGS] = {
    {
        .name = {'O', "owl"}, 
        .parameters = {}, 
        .parameters_length = 0, 
        .action = print_owl, 
        .description = "prints 10 owls on the screen."
    },
    {
        .name = {'I', "importance"}, 
        .parameters = __log_threshold_array,
        .parameters_length = 1, 
        .action = edit_int, 
        .description = "(in the form of -I[int]) sets log\n"
                        "    threshold to specified number.\n" 
                        "    Does not check if integer is specified."
    },
};

/**
 * @brief Main function of the program. Reads 3 doubles from stdio and prints the solution of the equation.
 * 
 * @return exit status (0 if successful)
 */
int main(const int argc, const char** argv) {
    atexit(end_program);

    parse_args(argc, argv, NUMBER_OF_TAGS, LINE_TAGS);
    log_init("program_log.log", log_threshold, &errno);
    print_label();
    read_config();

    double coef_a = 0, coef_b = 0, coef_c = 0;
    read_coefficients(&coef_a, &coef_b, &coef_c);

    log_printf(STATUS_REPORTS, "status", "processing started.\n");
    double answers[4] = {};
    printf("Equation:\n%gx2 + %gx + %g = 0\n", coef_a, coef_b, coef_c);
    solve_square(coef_a, coef_b, coef_c, answers);

    log_printf(STATUS_REPORTS + 1, "status", "estimated solution: X1 = %lg + %lg i, X2 = %lg + %lg i.\n", 
            answers[0], answers[1], answers[2], answers[3]);
    log_printf(STATUS_REPORTS, "status", "printing solution...\n");

    printf("Solution:\n");
    print_solution(answers, show_imaginary);

    return 0;
}

void fill_config(FILE* pf_config)  {
    fprintf(pf_config, "imaginary = %d", show_imaginary);
}

// Офигенно, ничего не менять
// Дополнил сову, сорри.
void print_owl(const int argc, void** argv, const char* argument) {
    printf("-Owl argument detected, dropping emergency supply of owls.\n");
    for (int i = 0; i < 10; i++) {
        printf("  A_,,,_A           \n");
        printf(" ((O)V(O))          \n");
        printf("(\"\\\"|\"|\"/\")   \n");
        printf(" \\\"|\"|\"|\"/     \n");
        printf("   \"| |\"          \n");
        printf("    ^ ^             \n");
    }
}

void print_label() {
    printf("Square equation solver by Ilya Kudryashov.\n");
    printf("Program solves square equations in the form of A*x*x + B*x + C = 0\n");
    printf("Build from\n%s %s\n", __DATE__, __TIME__);
    log_printf(ABSOLUTE_IMPORTANCE, "build info", "Build from %s %s.\n", __DATE__, __TIME__);
}

void read_config() {
    log_printf(STATUS_REPORTS, "status", "Reading config file...\n");

    FILE* pf_config = fopen(pc_config_name, "r");
    if (!pf_config || !fscanf(pf_config, "imaginary = %d", &show_imaginary)) {
        printf("No config file detected or it was corrupt, creating new file.\n");
        log_printf(AUTOMATIC_CORRECTIONS, "action", "config file corrupt/missing, creating new file.\n");

        if (pf_config) fclose(pf_config);
        FILE* pf_new_config = fopen(pc_config_name, "w");

        if (pf_new_config) {
            fill_config(pf_new_config);
        } else {
            log_printf(ERROR_REPORTS, "error", "failed to create config file.\n");
        }
        
        fclose(pf_new_config);

        pf_config = fopen(pc_config_name, "r");
    }

    if (fclose(pf_config) == EOF) {
        log_printf(ERROR_REPORTS, "error", "failed to close config file.\n");
    }

    log_printf(STATUS_REPORTS, "status", "config file processing finished.\n");
}

void read_coefficients(double* coef_a, double* coef_b, double* coef_c){
    log_printf(STATUS_REPORTS, "status", "reading data from the user...\n");

    read_double("A = ", coef_a);
    read_double("B = ", coef_b);
    read_double("C = ", coef_c);

    log_printf(STATUS_REPORTS, "status", "finished reading data.\n");
    log_printf(STATUS_REPORTS + 1, "status", "user entered coefficients A = %lg, B = %lg, C = %lg.\n", coef_a, coef_b, coef_c);
}