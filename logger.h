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

//! TODO: implement log printf that prints name of file and line (very useful for debugging)
//! Impossible without rewriting whole logger subsystems into macros and sh*tting readability of log files.

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
void log_printf(const unsigned int importance, const char* tag, const char* format, ...);

/**
 * @brief Closes all opened logs.
 * 
 * @param error_code (optional) variable to put function execution code in
 */
void log_close(int* error_code = NULL);

#endif