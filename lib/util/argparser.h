/**
 * @file argparser.h
 * @author Ilya Kudryashov (kudriashov.it@phystech.edu)
 * @brief Module for parsing command line arguments
 * @version 0.1
 * @date 2022-08-25
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef ARGPARSER_H
#define ARGPARSER_H

#include <cstddef>

/**
 * @brief 
 * 
 */
struct ActionName {
    char short_name = 0;
    const char* long_name = "";
};

struct GenericFunctionCall {
    void** parameters = NULL;
    int parameters_length = 0;
    void (*function)(const int argc, void** argv, const char* argument);
};

/**
 * @brief Structure to store line arguments.
 * 
 * @param short_name
 */
struct ActionTag {
    struct ActionName name;
    struct GenericFunctionCall action;
    const char* description = "no information provided.";
};

/**
 * @brief Parses command line arguments and executes actions.
 * 
 * @param argc number of arguments
 * @param argv arguments
 * @param actions_count number of tags
 * @param actions tags
 */
void parse_args(const int argc, const char** argv, const int actions_count, const struct ActionTag* actions);

/**
 * @brief Sets integer value (first pointer) to parsed value of argument.
 * 
 * @param argc number of arguments
 * @param argv pointers to arguments (1-st element should be int*)
 * @param argument argument as string
 */
void edit_int(const int argc, void** argv, const char* argument);

#endif