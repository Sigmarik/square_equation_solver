/**
 * @file logger.h
 * @author Ilya Kudryashov (kudriashov.it@phystech.edu)
 * @brief Module for creating programm logs.
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
    ERROR_REPORTS = 5,
    WARNINGS = 3,
    AUTOMATIC_CORRECTIONS = 2,
    TERMINATE_REPORTS = 6,
};

/**
 * @brief Opens log file or creates empty one.
 * 
 * @param pc_filename (optional) log file name
 * @param i_threshold (optional) value, below which porgramm would print log lines into dummy file.
 * @param pi_error_code (optional) variable to put function execution code in
 */
void log_init(const char* pc_filename = "log", const unsigned int i_threshold = 0, int* pi_error_code = NULL);

/**
 * @brief Prints out log line prefix (time and tag).
 * 
 * @param tag (optional) prefix tag
 * @param i_importance (optional) message importance
 */
void log_prefix(const char* tag = "status", const unsigned int i_importance = 1000);

/**
 * @brief Writes static message to log file followed by time and tag.
 * 
 * @param tag message tag
 * @param message message text
 * @param importance (optional) message importance
 * @param pi_error_code (optional) variable to put function execution code in
 */
void log_write(const char* tag, const char* message, const unsigned int importance = 1000, int* pi_error_code = NULL);

/**
 * @brief Returns currently opened log file by given importance.
 * 
 * @param i_importance (optional) importance of the message file will be used for.
 * 
 * @return FILE* log file
 */
FILE* log_file(const unsigned int i_importance = 1000);

/**
 * @brief Closes all opened logs.
 * 
 * @param pi_error_code (optional) variable to put function execution code in
 */
void log_close(int* pi_error_code = NULL);

#endif