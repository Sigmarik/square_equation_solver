/**
 * @file main.c
 * @author Ilya Kudryashov (kudriashov.it@phystech.edu)
 * @brief Programm for reading square equation (by coefficients A, B and C) and printing the solution.
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

/**
 * @brief Main function of the programm. Reads 3 doubles from stdio and prints the solution of the equation.
 * 
 * @return exit status (0 if successful)
 */
int main(void) {
    printf("Square equation solver by Ilya Kudryashov.\n");
    printf("Programm solves square equations in the form of A*x*x + B*x + C = 0\n");
    printf("Build from\n%s %s\n", __DATE__, __TIME__);

    FILE* pf_config = fopen("rootsolver.conf", "r");  // pointer to the rootsolver.conf file

    // Config file parsing.
    int b_show_imaginary = -1;
    if (!pf_config || !fscanf(pf_config, "imaginary = %d", &b_show_imaginary)) {
        printf("No config file detected or it was corrupt, terminating.\n");
        exit(EXIT_FAILURE);
    }

    if (fclose(pf_config) == EOF) {
        printf("Failed to close config file.\n");
    };

    double d_a = 0, d_b = 0, d_c = 0;  // equation coefficients

    // Receive data from the user.
    read_double("A = ", &d_a);
    read_double("B = ", &d_b);
    read_double("C = ", &d_c);

    double pd_answers[4] = {};  // equation roots

    // Display equation to the user before major computations.
    printf("Equation:\n%gx2 + %gx + %g = 0\n", d_a, d_b, d_c);
    solve_square(d_a, d_b, d_c, pd_answers);

    printf("Solution:\n");

    // Print solution(s) on the screen.
    print_solution(pd_answers, b_show_imaginary);

    return 0;
}