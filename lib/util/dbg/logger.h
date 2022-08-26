/**
 * @file logger.h
 * @author Ilya Kudryashov (kudriashov.it@phystech.edu)
 * @brief Module for creating program logs.
 * @version 0.1
 * @date 2022-08-24
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>

enum IMPORTANCES {
    STATUS_REPORTS = 0,
    AUTOMATIC_CORRECTIONS = 2,
    WARNINGS = 3,
    ERROR_REPORTS = 5,
    TERMINATE_REPORTS = 6,
    ABSOLUTE_IMPORTANCE = 1000,
};

/**
 * @brief Runs fprintf() in logs.
 * 
 * @param importance message importance
 * @param tag message tag
 * @param __VA_ARGS__ arguments for fprintf()
 */

#include <stdarg.h>

#ifndef NLOG_PRINT_LINE
/**
 * @brief Print message to logs followed by call information.
 */
#define log_printf(importance, tag, ...) do {                                   \
    _log_printf(importance, tag, "Call on line %d of file %s.\n", __LINE__, __FILE__);  \
    _log_printf(importance, tag, __VA_ARGS__);                                  \
} while(0)
#else
/**
 * @brief Print message to logs.
 */
#define log_printf(importance, tag, ...) do { \
    _log_printf(importance, tag, __VA_ARGS__);\
} while(0)
#endif

// One macro isn't that bad considering it can be very useful for debugging

/**
 * @brief Opens log file or creates empty one.
 * 
 * @param filename (optional) log file name
 * @param threshold (optional) value, below which porgramm would print log lines into dummy file.
 * @param error_code (optional) variable to put function execution code in
 */
void log_init(const char* filename = "log", const unsigned int threshold = 0, int* error_code = NULL);

/**
 * @brief Prints line to logs with automatic prefix.
 * 
 * @param importance importance of the message
 * @param tag message tag
 * @param format format string for printf()
 * @param ... arguments for printf()
 */
void _log_printf(const unsigned int importance, const char* tag, const char* format, ...);

/**
 * @brief Closes all opened logs.
 * 
 * @param error_code (optional) variable to put function execution code in
 */
void log_close(int* error_code = NULL);

#endif