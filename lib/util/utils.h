/**
 * @file utils.h
 * @author Ilya Kudryashov (kudriashov.it@phystech.edu)
 * @brief Utility library for "orphan" functions.
 * @version 0.1
 * @date 2022-08-25
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef UTILS_H
#define UTILS_H

/**
 * @brief Compares two doubles and returns sign(a - b)
 * 
 * @param[in] a first component
 * @param[in] b second component
 * @return 0 if d_a == d_b. Else sign(d_a - d_b)
 * 
 * @note Doubles are considered equal if they are closer then 1e-10
 */
int doublecmp(const double a, const double b);

/**
 * @brief Prints complex numbers containing both normal and imaginary part.
 *
 * @param[in] whole "normal" part of the number
 * @param[in] imaginary imaginary part of the number
 */
void print_number(const double whole, const double imaginary);

#endif