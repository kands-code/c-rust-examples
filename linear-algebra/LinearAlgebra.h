#pragma once

/*
 ** Some Linear Algebra
 */

// --- some includes

#include <stdbool.h>

// --- some definition

// matrix type
// @description : vector is also a matrix
//              which dim is [1, N] or [N, 1]
typedef struct __MATRIX {
  int *dim;
  double *data;
} matrix;

typedef matrix *matp;

// --- some functions

// === other part

// calculate the number of inversions of an array
// @param len : the length of the array
// @param arr : int array, the array
// @return : the number of inversions of the array
int getNumberOfInversions(int len, int *arr);

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

// multiply two matrices
// @param m1 : the first matrix
// @param m2 : the second matrix
// @return : the product
matrix *matrixMultiply(matrix *m1, matrix *m2);

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

// the eigenvalues of a matrix
// @param mat : the matrix
// @return : all the eigenvalues
double *matrixEigenValues(matrix *mat);

// === vector part

// dot product of two vectors
// @param v1 : the first vector
// @param v2 : the second vector
// @return : the dot product value
double vectorDotProduct(matrix *v1, matrix *v2);

// cross product of two vector
// @param v1 : the first vector
// @param v2 : the second vector
// @return : the cross product value
matrix *vectorCrossProduct(matrix *v1, matrix *v2);
