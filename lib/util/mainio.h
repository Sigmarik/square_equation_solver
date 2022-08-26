/**
 * @file mainio.h
 * @author Ilya Kudryashov (kudriashov.it@phystech.edu)
 * @brief Module for printing specific things required in main.c
 * @version 0.1
 * @date 2022-08-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef MAINIO_H
#define MAINIO_H

#include <cstddef>

/**
 * @brief Prints pc_prefix and tries to read double until succeeds.
 * 
 * @param prefix prefix to print before each request
 * @param variable pointer to the variable to push the result
 * @param error_code pointer to integer to put error code in
 */
void read_double(const char* prefix, double* variable, int* error_code = NULL);

/**
 * @brief Prints out the solution of the square equation in a fancy way.
 * 
 * @param answers pointer to the array of at least 4 doubles with answers 
 * in the shape specified in rootsolver.c/void solve
 * @param show_imaginary 1 if function should consider imaginary solutions, 0 othervise.
 * @param error_code pointer to integer to put error code in
 * 
 * @note 
 * Function has no protection from arrays smaller than required, so
 * it is possible for function to crash with segfault.
 * It is still intentional, though, as it may be usefull to
 * print values from the middle of some bigger array.
 */
void print_solution(const double* answers, const int show_imaginary, int* error_code = NULL);

#endif