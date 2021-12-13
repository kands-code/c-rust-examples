#pragma once

// --- some includes

#include "../LinearAlgebra.h"
#include <stdbool.h>

// --- some definition
typedef char *str;

// --- some macros

#define equals(arg1, arg2)                                                     \
  _Generic((arg1), \
          char * : equalsForString, \
          matrix * : equalsForMatrix, \
          double : equalsForNum, \
          default : equalsForNum\
        )(arg1, arg2)

// the minimum difference
extern double eps;

// -- some functions

// judge whether num is equal to zero
// @param num : the number
// @return : true for zero, false for nonzero
bool equalsToZero(double num);

// judge whether the two numbers are equal
// @param n1 : the first number
// @param n2 : the second number
// @return : true for equal, false for unequal
bool equalsForNum(double n1, double n2);

// judge whether the two strings are equal
// @param s1 : the first strings
// @param s2 : the second strings
// @return : true for equal, false for unequal
bool equalsForString(char *s1, char *s2);

// judge whether the two matrix are equal
// @param m1 : the first matrix
// @param m2 : the second matrix
// @return bool : true for equal, otherwise false
bool equalsForMatrix(matrix *m1, matrix *m2);
