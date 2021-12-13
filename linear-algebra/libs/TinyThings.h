#pragma once

// TT for TinyThings

// --- some includes
#include "../LinearAlgebra.h"

// --- some definitions

// --- some macros
#define powerTT(m, n)                                                          \
  _Generic((m), matrix * : powerMatrix, default : powerNum)(m, n)

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

// calculate the inversion number of an array
// @param len : the length of the array
// @param arr : int array, the array
// @return : the inversion number of the array
int getInversionNumber(int len, int *arr);

// solve linear functions
// @param argM : the argument matrix
// @param valueV : the value vector
// @return : the solves
matrix *solveLinearFunctions(matrix *argM, matrix *valueV);
