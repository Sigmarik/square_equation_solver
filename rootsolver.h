#ifndef ROOTSOLVER_H
#define ROOTSOLVER_H

#include <math.h>

// Debugging
/* NDEBUG should be here-> */ //#define NDEBUG
#include <assert.h>
#include <errno.h>
enum ERRORS {
    INPUT_ERROR = -1,
    NULLPTR_ERROR = -2,
};

// Functional
int i_dcmp(const double d_a, const double d_b);
void solve(const double d_a, const double d_b, const double d_c, double pd_answers[4]);

// Debugging / output
void print_number(const double d_whole, const double d_imaginary);

#endif