/* 
main.c receves 3 floating point parameters (A, B and C) and prints
solution of equation x * x * A + x * B + x * C = 0.
*/

#include "rootsolver.c"
#include <stdio.h>
#include <stdlib.h>

// Tries to read 3 doubles corresponding to A, B and C equation coefficients.
// argc - argument count (including program name)
// argv - pointers to arguments
int main(int argc, char **argv) {
    double pd_coefficients[3];  // equation coefficients
    double pd_answers[4];  // equation roots
    int i_argument_iterator = -1;  // iterator
    int b_wrong_input = 0;  // was wrong input detected

    if (argc != 4) {
        printf("Wrong argument count, 3 floating point values expected.\n");
        return 1;
    }
    while (++i_argument_iterator < 3) {
        char* pc_break_char;  // pointer to the character where strtof() stopped execution

        pd_coefficients[i_argument_iterator] = strtof(argv[i_argument_iterator + 1], &pc_break_char);
        b_wrong_input = b_wrong_input || *pc_break_char != 0;
    }
    if (b_wrong_input) {
        printf("Wrong characters detected, terminating.\n");
        return 1;
    }

    solve(pd_coefficients, pd_answers);

    if (isnan(pd_answers[1])) {
        if (pd_coefficients[2] == 0) {
            printf("Equation is always true.\n");
        } else {
            printf("Equation has no roots.\n");
        }
    } else if (pd_answers[0] == pd_answers[2] && pd_answers[1] == pd_answers[3]) {
        printf("X = %g + %gi\n", pd_answers[0], pd_answers[1]);
    } else {
        printf("X1 = %g + %gi\n", pd_answers[0], pd_answers[1]);
        printf("X2 = %g + %gi\n", pd_answers[2], pd_answers[3]);
    }

    return 0;
}