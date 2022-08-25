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
#define _LOG_PRINTF_(importance, tag, ...) {                \
    if (log_file()) {                                       \
        log_prefix(tag, importance);                        \
        fprintf(log_file(importance), __VA_ARGS__);         \
        fflush(log_file(importance));                       \
    }                                                       \
}

/**
 * @brief Opens log file or creates empty one.
 * 
 * @param filename (optional) log file name
 * @param threshold (optional) value, below which porgramm would print log lines into dummy file.
 * @param error_code (optional) variable to put function execution code in
 */
void log_init(const char* filename = "log", const unsigned int threshold = 0, int* error_code = NULL);

/**
 * @brief Prints out log line prefix (time and tag).
 * 
 * @param tag (optional) prefix tag
 * @param importance (optional) message importance
 */
void log_prefix(const char* tag = "status", const unsigned int importance = ABSOLUTE_IMPORTANCE);

/**
 * @brief Writes static message to log file followed by time and tag.
 * 
 * @param tag message tag
 * @param message message text
 * @param importance (optional) message importance
 * @param error_code (optional) variable to put function execution code in
 */
void log_write(const char* tag, const char* message, const unsigned int importance = ABSOLUTE_IMPORTANCE, int* error_code = NULL);

/**
 * @brief Returns currently opened log file by given importance.
 * 
 * @param importance (optional) importance of the message file will be used for.
 * 
 * @return FILE* log file
 */
FILE* log_file(const unsigned int importance = ABSOLUTE_IMPORTANCE);

/**
 * @brief Closes all opened logs.
 * 
 * @param error_code (optional) variable to put function execution code in
 */
void log_close(int* error_code = NULL);

#endif