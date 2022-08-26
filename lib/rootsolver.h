/**
 * @file rootsolver.h
 * @author Ilya Kudryashov (kudriashov.it@phystech.edu)
 * @brief Module for solving square / linear equations
 * @version 0.1
 * @date 2022-08-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef ROOTSOLVER_H
#define ROOTSOLVER_H

#include <cstddef>

/**
 * @brief Solves linear equation in the form of d_a * x + d_b = 0
 *
 * @param[in] b B coefficient
 * @param[in] a A coefficient
 * @return Solution of the d_a * x + d_b = 0 equation (INF or NAN if infinite or zero roots)
 *
 * @note returns INFINITY if there are infinite roots and NAN if zero
 */
double solve_linear(const double a, const double b);

/**
 * @brief 
 * Solves equation by given coefficients and inserts
 * answers into pd_answers array as if 1-st and 3-rd elements
 * are rational parts of both answers and 2-nd and 4-th elements
 * are imaginary multiplyers.
 *
 * @param[in] a A coefficient
 * @param[in] b B coefficient
 * @param[in] c C coefficient
 * @param[out] answers array to put answers in
 * @param[out] error_code pointer to int to write error code in which function should write code in case of error
 *
 * @note Fills pd_answers with INFINITY if equation has infinite number of solutions and NAN if zero.
 */
void solve_square(const double a, const double b, const double c, double answers[4], int* error_code = NULL);

#endif