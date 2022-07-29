// matrix-ext.h -- extended matrix

#pragma once

/************************************************************
 * Matrix tools
 ************************************************************/

#include "matrix.h"

/**
 * @func InitMatrixByInput : initialize a matrix by user input
 * @return mat             : the matrix [ Matrix * ]
 * @descript               : input element separate by blank character;
 *                           function will return wrong matrix,
 *                           if user do not follow the correct way of typing
 */
Matrix *InitMatrixByInput();

/************************************************************
 * Matrix tools
 ************************************************************/

/**
 * @func PrintMatrixP : print the matrix with precision
 * @param mat         : the matrix    [ Matrix * ]
 * @param p           : the precision [ int      ]
 */
void PrintMatrixP(Matrix *mat, int p);

/************************************************************
 * some matrix manipulations
 ************************************************************/

/**
 * @func MatKronecker : the Kronecker product of m1 and m2
 * @param m1          : the first matrix  [ Matrix * ]
 * @param m2          : the second matrix [ Matrix * ]
 * @return p          : the product       [ Matrix * ]
 */
Matrix *MatKronecker(Matrix *m1, Matrix *m2);

/**
 * @func MatLUD : LU Decomposition
 * @param m     : the matrix [ Matrix * ]
 * @return res  : the result [ LUDR *   ]
 * @descript    : result contains R, L^-1,
 *                matrix must be squared
 */
LUDR *MatLUD(Matrix *m);

/**
 * @func MatAlgCofactor : get the trace of matrix
 * @param mat           : the matrix              [ Matrix * ]
 * @param r             : the row                 [ int      ]
 * @param c             : the column              [ int      ]
 * @return algCofactor  : the algebraic cofactor  [ double   ]
 * @descript            : r and c start from 0
 */
double MatAlgCofactor(Matrix *mat, int r, int c);

/**
 * @func MatAdjugate : get the adjugate of matrix
 * @param m          : the matrix          [ Matrix * ]
 * @return mat       : the adjugate matrix [ Matrix * ]
 * @descript         : the matrix must be squared;
 *                     the function will return NULL,
 *                     if the matrix has no adjugate
 */
Matrix *MatAdjugate(Matrix *m);

/**
 * @func LinearSolver : solve linear equations
 * @param A  : the coefficient matrix [ Matrix * ]
 * @param b  : the vector             [ Matrix * ]
 * @return s : the solution           [ Matrix * ]
 * @descript : b must be col vector
 */
Matrix *LinearSolver(Matrix *A, Matrix *b);

/**
 * @func JacobiLinearSolver : solve linear equations by jacobi iteration
 * @param A  : the coefficient matrix [ Matrix * ]
 * @param b  : the vector             [ Matrix * ]
 * @param k  : number of iterations   [ int      ]
 * @return s : the solution           [ Matrix * ]
 */
Matrix *JacobiLinearSolver(Matrix *A, Matrix *b, int k);

/**
 * TODO
 * @func SolveEigs : solve the eigen system of matrix
 * @param mat      : the matrix       [ Matrix *  ]
 * @return sys     : the eigen system [ Matrix ** ]
 */
Matrix **SolveEigs(Matrix *mat);

// TODO
// Need more decomposition functions
