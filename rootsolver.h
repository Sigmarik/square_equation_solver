#ifndef ROOTSOLVER_H
#define ROOTSOLVER_H

#include <math.h>

// Debugging
#define NDEBUG
#include <assert.h>
#include <errno.h>

#ifdef NDEBUG
#define ASSERTABLE 0
#else
#define ASSERTABLE 1
#endif

#define INPUT_ERROR -1
#define NULLPTR_ERROR -2

// Functional
int i_dcmp(const double d_a, const double d_b);
void solve(const double d_a, const double d_b, const double d_c, double pd_answers[4]);

// Debugging / output
void print_number(const double d_whole, const double d_imaginary);

#endif