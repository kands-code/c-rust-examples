#pragma once

/*
 ** Some Linear Algebra
 */

// --- some includes

#include <stdbool.h>

// --- some definition

// the minimum difference
extern double eps;

// matrix type
typedef struct __MATRIX {
  int *dim;
  double *data;
} matrix;

// vector type
typedef struct __VECTOR {
  int dim;
  double *data;
  // only 'r' or 'c'
  char orient;
} vector;

// --- some macros

// === Equals
#define equalsT(m, n)                                                          \
  _Generic((m), \
          char * : equalsForString, \
          matrix * : equalsForMatrix, \
          vector * : equalsForVector, \
          double : equalsForNum, \
          int : equalsForIntegral, \
          default : equalsForIntegral \
        )(m, n)

// === Power
#define powerT(m, n)                                                           \
  _Generic((m), \
          matrix * : powerMatrix, \
          double : powerNum, \
          vector * : powerVector, \
          default : powerNum \
        )(m, n)

// === MIN
#define MIN(a, b) ((a) > (b) ? (b) : (a))
// === MAX
#define MAX(a, b) ((a) > (b) ? (a) : (b))

// --- some functions

// === equals part

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

// judge whether the two integrals are equal
// @param i1 : the first integral
// @param i2 : the second integral
// @return : true for equal and false for unequal
bool equalsForIntegral(int i1, int i2);

// judge whether the two vectors are equal
// @param v1 : the first vector
// @param v2 : the second vector
// @return bool : true for equal, otherwise false
bool equalsForVector(vector *v1, vector *v2);

// === matrix part

// matrix init
// @param i : the first dimension, rows
// @param j : the second dimension, columns
// @return : a matrix pointer
matrix *matrixInit(int i, int j);

// get a diagonal matrix
// @param len : the size of the matrix
// @param diag : the diagonal of the matrix
// @return : a diagonal matrix
matrix *matrixGetDiagonalMatrix(int len, double *diag);

// get an identity matrix
// @param len : the size of the matrix
// @return : the identity matrix
matrix *matrixGetIndentityMatrix(int len);

// init a matrix from an array
// @param r : the first dimension, rows
// @param c : the second dimension, columns
// @param arr : the array
// @return : the matrix
matrix *matrixGetMatrixByArray(int r, int c, double *arr);

// print a matrix with precision
// @param mat : the matrix
// @param precision : the precision
void matrixPrintWithPrecision(matrix *mat, int precision);

// print a matrix
// @param mat : the matrix
void matrixPrint(matrix *mat);

// transpose a matrix
// @param mat : the matrix
// @return : the transposed matrix
matrix *matrixTranspose(matrix *mat);

// add up number and matrix
// @param num : the number
// @param mat : the matrix
// @return : the sum
// @description : add num to each element
matrix *matrixAdditionWithNum(double num, matrix *mat);

// multiply a number and a matrix
// @param num : the number
// @param mat : the matrix
// @return : the product
// @description : multiply each element by num
matrix *matrixMultiplyWithNum(double num, matrix *mat);

// add up two matrices
// @param m1 : the first matrix
// @param m2 : the second matrix
// @return : the sum
matrix *matrixAddition(matrix *m1, matrix *m2);

// subtraction of matrix
// @param m1 : the first matrix
// @param m2 : the second matrix
// @return : the difference of the two matrix
matrix *matrixSubtraction(matrix *m1, matrix *m2);

// multiply two matrices
// @param m1 : the first matrix
// @param m2 : the second matrix
// @return : the product
matrix *matrixMultiply(matrix *m1, matrix *m2);

// division of matrix
// @param m1 : the first matrix
// @param m2 : the second matrix
// @return : the quotient
matrix *matrixDivision(matrix *m1, matrix *m2);

// calculate the determinant of a matrix
// @param mat : the matrix
// @return : the determinant
double matrixDeterminant(matrix *mat);

// transform a matrix to upright-triangle form
// @param mat : the matrix
// @return : a formated matrix
matrix *matrixToUprightTriangleForm(matrix *mat);

// get the algebraic cofactor of a matrix
// @param mat : the matrix
// @param r : the row
// @param c : the column
// @return : the algebraic cofactor A(r, c)
double matrixGetAlgebraicCofactor(matrix *mat, int r, int c);

// get the adjoint matrix of a matrix
// @param mat : the matrix
// @return : the adjoint matrix
matrix *matrixAdjointMatrix(matrix *mat);

// find the inverse of a matrix
// @param mat : the matrix
// @return : the inverse matrix
matrix *matrixInverse(matrix *mat);

// get the rank of a matrix
// @param mat : the matrix
// @return : the rank of the matrix
int matrixGetMatrixRank(matrix *mat);

// get the trace of a matrix
// @param mat : the matrix
// @return : the trace of the matrix
double matrixGetMatrixTrace(matrix *mat);

// === vector part

// init a vector
// @param len : the length of vector
// @param o : the orientation
// @return : the vector
vector *vectorInit(int len, char o);

// init a vector by an array
// @param len : the length of vector
// @param o : the orientation
// @param arr : the array
// @return : the vector
vector *vectorGetVectorByArray(int len, char o, double *arr);

// print vector with precision
// @param vec : the vector
// @param precision : the precision
void vectorPrintWithPrecision(vector *vec, int precision);

// print vector with a default precision
// @param vec : the vector
void vectorPrint(vector *vec);

// addition of vector
// @param v1 : the first vector
// @param v2 : the second vector
// @return : the sum of the two vectors
vector *vectorAddition(vector *v1, vector *v2);

// subtraction of vector
// @param v1 : the first vector
// @param v2 : the second vector
// @return : the difference of the two vectors
vector *vectorSubtraction(vector *v1, vector *v2);

// dot product of two vectors
// @param v1 : the first vector
// @param v2 : the second vector
// @return : the result, vec(3)
// @description : the orientation of vectors must be equal
double vectorDotProduct(vector *v1, vector *v2);

// cross product of two vector
// @param v1 : the first vector
// @param v2 : the second vector
// @return : the cross product value
// @description : the dimension must be 2 or 3
//                the orientation of vectors must be equal
vector *vectorCrossProduct(vector *v1, vector *v2);

// === other part

// return the absolute value of num
// @param num : the num
// @return : the absolute value
double absT(double num);

// return the power of matrix
// @param mat : the matrix
// @param n : the times
// @return : the power product
matrix *powerMatrix(matrix *mat, int n);

// power of vector
// powerT([a, b, c], n) => [a^n, b^n, c^n]
// @param vec : the vector
// @param n : the times
// @return vector : the powered vector
vector *powerVector(vector *vec, int n);

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

// turn a vector into a matrix
// @param vec : the vector
// @return matrix * : the matrix
matrix *vectorToMatrix(vector *vec);

// true a matrix into a vector
// @param mat : the matrix
// @return vector * : the vector
vector *matrixToVector(matrix *mat);
