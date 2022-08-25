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

#include "logger.h"

/**
 * @brief List of error types to put into errno.
 */
enum ERRORS {
    INPUT_ERROR = -1,
    NULLPTR_ERROR = -2,
    FILE_ERROR = -3,
};

/**
 * @brief prints description to log file if equation fails.
 * 
 */
#ifndef NDEBUG
#define _LOG_FAIL_CHECK_(equation, tag, importance, action, errcode, errtype)                                           \
do {                                                                                                                    \
    if (!(equation)) {                                                                                                  \
        if (errcode) *(errcode) = (errtype);                                                                            \
        _LOG_PRINTF_(importance, "error", "Equation %s in file %s at line %d failed.\n", #equation, __FILE__, __LINE__);\
        action                                                                                                          \
    }                                                                                                                   \
} while(0)
#else
#define _LOG_FAIL_CHECK_(...) ((void) 0)
#endif

/**
 * @brief Prints [errno] variable if it's value is not zero.
 */
void end_program();

#endif