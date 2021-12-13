#pragma once

// TT for TinyThings

// --- some includes
#include "../LinearAlgebra.h"

// --- some definitions

// --- some macros
#define powerTT(m, n)                                                          \
  _Generic((m), matp : powerMatrix, double : powerNum, default : powerNum)(m, n)

// --- some functions

// return the absolute value of num
// @param num : the num
// @return : the absolute value
double absTT(double num);

// return the power of matrix
// @param mat : the matrix
// @param n : the times
// @return : the power product
matrix *powerMatrix(matrix *mat, int n);

// return the power of number
// @param num : the number
// @param n : the times
// @return : the power product
double powerNum(double num, int n);
