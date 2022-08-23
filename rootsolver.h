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

/**
 * @brief Compares two doubles and returns sign(a - b)
 * 
 * @param[in] d_a - first component
 * @param[in] d_b - second component
 * @return 0 if d_a == d_b. Else sign(d_a - d_b)
 * 
 * @note Doubles are considered equal if they are closer then 1e-10
 */
int i_dcmp(const double d_a, const double d_b);

/**
 * @brief Solves linear equation in the form of d_a * x + d_b = 0
 *
 * @param[in] d_a - A coefficient
 * @param[in] d_b - B coefficient
 * @return Solution of the d_a * x + d_b = 0 equation (INF or NAN if infinite or zero roots)
 *
 * @note returns INFINITY if there are infinite roots and NAN if zero
 */
double d_solve_linear(const double d_a, const double d_b);

/**
 * @brief 
 * Solves equation by given coefficients and inserts
 * answers into pd_answers array as if 1-st and 3-rd elements
 * are rational parts of both answers and 2-nd and 4-th elements
 * are imaginary multiplyers.
 *
 * @param[in] d_a - A coefficient
 * @param[in] d_b - B coefficient
 * @param[in] d_c - C coefficient
 * @param[out] pd_answers - array to put answers in
 *
 * @note Fills pd_answers with INFINITY if equation has infinite number of solutions and NAN if zero.
 */
void solve_square(const double d_a, const double d_b, const double d_c, double pd_answers[4]);

/**
 * @brief Prints complex numbers containing both normal and imaginary part.
 *
 * @param[in] d_whole - "normal" part of the number
 * @param[in] d_imaginary - imaginary part of the number
 */
void print_number(const double d_whole, const double d_imaginary);

#endif