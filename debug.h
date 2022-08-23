/**
 * @file debug.h
 * @author Ilya Kudryashov (kudriashov.it@phystech.edu)
 * @brief Module with debugging information.
 * @version 0.1
 * @date 2022-08-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef DEBUGGING_H
#define DEBUGGING_H

/* NDEBUG should be here-> */
//#define NDEBUG
#include <assert.h>
#include <errno.h>

/**
 * @brief List of error types to put into errno.
 */
enum ERRORS {
    INPUT_ERROR = -1,
    NULLPTR_ERROR = -2,
};

/**
 * @brief Prints [errno] variable if it's value is not zero.
 */
void print_errno();

#endif