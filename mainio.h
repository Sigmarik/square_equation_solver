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

/**
 * @brief Prints pc_prefix and tries to read double until succeeds.
 * 
 * @param pc_prefix - prefix to print before each request
 * @param pd_variable - pointer to the variable to push the result
 */
void read_double(const char* pc_prefix, double* pd_variable);

/**
 * @brief Prints out the solution of the square equation in the fancy way.
 * 
 * @param pd_answers - pointer to the array of at least 4 doubles with answers 
 * in the shape specified in rootsolver.c/void solve
 * @param b_show_imaginary - 1 if function should consider imaginary solutions, 0 othervise.
 * 
 * @note 
 * Function has no protection from arrays smaller than required, so
 * it is possible for function to crash with segfault.
 * It is still intentional, though, as it may be usefull to
 * print values from the middle of some bigger array.
 */
void print_solution(const double* pd_answers, const int b_show_imaginary);

#endif