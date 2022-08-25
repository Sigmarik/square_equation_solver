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

struct ActionTag {
    char short_name = '_';
    const char* long_name = NULL;
    void** parameters = NULL;
    int arg_count = 0;
    void (*action)(const int argc, void** argv, const char* argument);
    const char* description = "no information provided.";
};

/**
 * @brief Parses command line arguments and executes actions.
 * 
 * @param argc number of arguments
 * @param argv arguments
 * @param action_c number of tags
 * @param actions tags
 */
void parse_args(const int argc, const char** argv, const int action_c, const struct ActionTag* actions);

#endif