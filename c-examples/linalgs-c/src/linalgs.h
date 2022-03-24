#pragma once

/************************************************************
 * Includes
 ************************************************************/

/************************************************************
 * Macros
 ************************************************************/

/**
 * @macroFunc MAX : return the bigger one
 * @param a       : the first value
 * @param b       : the second value
 * @return        : the biggest one
 */
#define MAX(a, b) (a) > (b) ? (a) : (b)

/**
 * @macroFunc MIN : return the smaller one
 * @param a       : the first value
 * @param b       : the second value
 * @return        : the smallest one
 */
#define MIN(a, b) (a) < (b) ? (a) : (b)

/************************************************************
 * Type define
 ************************************************************/

/**
 * @type Matrix  : the basic element in linear algebra
 * @content data : the value of matrix [ double * ]
 * @content size : the size of matrix  [ int *    ]
 * @descript     : a vector is also a matrix
 */
typedef struct {
  double *data;
  int size[2];
} Matrix;

/************************************************************
 * Init the matrix
 ************************************************************/

/**
 * @func InitMatrix : initialize a matrix
 * @param r         : the row number    [ int      ]
 * @param c         : the column number [ int      ]
 * @param d         : the default value [ double   ]
 * @return mat      : the matrix        [ Matrix * ]
 * @descript        : function will return null for illegal size
 */
Matrix *InitMatrix(int r, int c, double d);

/**
 * @func InitElemMatrix : initialize an element matrix
 * @param n             : the size of matrix [ Matrix * ]
 * @return e            : the element matrix [ Matrix * ]
 */
Matrix *InitElemMatrix(int n);

/**
 * @func InitMatrixFromArray : initialize a matrix from an array
 * @param r                  : the row number      [ int      ]
 * @param c                  : the column number   [ int      ]
 * @param len                : the length of array [ int      ]
 * @param arr                : the array           [ double * ]
 * @return mat               : the matrix          [ Matrix * ]
 * @descript                 : function will return null for illegal size,
 *                             if size is bigger than array, fill with `0`,
 *                             if size is smaller than array, truncate
 */
Matrix *InitMatrixFromArray(int r, int c, int len, const double *arr);

/**
 * @func InitMatrixByInput : initialize a matrix by user input
 * @return mat             : the matrix [ Matrix * ]
 * @descript               : input element separate by blank character;
 *                           function will return wrong matrix,
 *                           if user do not follow the correct way of typing
 */
Matrix *InitMatrixByInput();

/**
 * @func DestroyMatrix : destroy matrix
 * @param mat          : the matrix [ Matrix * ]
 */
void DestroyMatrix(Matrix *mat);

/************************************************************
 * Matrix tools
 ************************************************************/

/**
 * @func PrintMatrixP : print the matrix with precision
 * @param mat         : the matrix    [ Matrix * ]
 * @param p           : the precision [ int      ]
 */
void PrintMatrixP(Matrix *mat, int p);

/**
 * @func PrintMatrix : print the matrix
 * @param mat        : the matrix [ Matrix * ]
 * @descript         : default precision is 2
 */
void PrintMatrix(Matrix *mat);

/**
 * @func GetMatrixVal : get the element from the matrix by coordinate
 * @param mat         : the matrix [ Matrix * ]
 * @param r           : the row    [ int      ]
 * @param c           : the column [ int      ]
 * @return val        : the value  [ double   ]
 * @descript          : function will exit when the coordinate is illegal
 */
double GetMatrixVal(Matrix *mat, int r, int c);

/**
 * @func GetMatrixRank : get matrix rank
 * @param m            : the matrix [ Matrix * ]
 * @return r           : the rank   [ int      ]
 */
int GetMatrixRank(Matrix *m);

/**
 * @func SetMatrixVal : get the element from the matrix by coordinate
 * @param mat         : the matrix [ Matrix * ]
 * @param r           : the row    [ int      ]
 * @param c           : the column [ int      ]
 * @param v           : the value  [ double   ]
 * @descript          : function will exit when the coordinate is illegal
 */
void SetMatrixVal(Matrix *mat, int r, int c, double v);

/************************************************************
 * some matrix manipulations
 ************************************************************/

/**
 * @func MatTrans : transpose a matrix
 * @param m       : the matrix            [ Matrix * ]
 * @return mat    : the transposed matrix [ Matrix * ]
 */
Matrix *MatTrans(Matrix *m);

/**
 * @func MatAdd : add up two matrices
 * @param m1    : the first matrix        [ Matrix * ]
 * @param m2    : the second matrix       [ Matrix * ]
 * @return mat  : the sum of two matrices [ Matrix * ]
 * @descript    : the size must be matched
 */
Matrix *MatAdd(Matrix *m1, Matrix *m2);

/**
 * @func MatSub : subtract m2 from m1
 * @param m1    : the first matrix         [ Matrix * ]
 * @param m2    : the second matrix        [ Matrix * ]
 * @return mat  : the diff of two matrices [ Matrix * ]
 * @descript    : the size must be matched
 */
Matrix *MatSub(Matrix *m1, Matrix *m2);

/**
 * @func MatMul : multiply scalar with matrix
 * @param n     : the scalar  [ int      ]
 * @param m     : the matrix  [ Matrix * ]
 * @return mat  : the product [ Matrix * ]
 */
Matrix *MatScalarMul(double n, Matrix *m);

/**
 * @func MatDiv : Divide scalar with matrix
 * @param n     : the scalar  [ int      ]
 * @param m     : the matrix  [ Matrix * ]
 * @return mat  : the quotient [ Matrix * ]
 */
Matrix *MatScalarDiv(double n, Matrix *m);

/**
 * @func MatMul : multiply m1 and m2
 * @param m1    : the first matrix            [ Matrix * ]
 * @param m2    : the second matrix           [ Matrix * ]
 * @return mat  : the product of two matrices [ Matrix * ]
 * @descript    : the size must be matched
 */
Matrix *MatMul(Matrix *m1, Matrix *m2);

/**
 * @func MatPow : the power of matrix
 * @param m     : the matrix  [ Matrix *     ]
 * @param n     : the power   [ unsigned int ]
 * @return mat  : the result  [ Matrix *     ]
 * @descript    : the matrix must be squared
 */
Matrix *MatPow(Matrix *m, unsigned int n);

/**
 * @func MatKronecker : the Kronecker product of m1 and m2
 * @param m1          : the first matrix  [ Matrix * ]
 * @param m2          : the second matrix [ Matrix * ]
 * @return p          : the product       [ Matrix * ]
 */
Matrix *MatKronecker(Matrix *m1, Matrix *m2);

/**
 * @func MatToUT : transform a matrix to upper triangle form
 * @param m      : the matrix [ Matrix *  ]
 * @return res   : the result [ Matrix ** ]
 * @descript     : result contains R, m,
 *                 matrix must be squared
 */
Matrix **MatToUT(Matrix *m);

/**
 * @func MatTrace : get the trace of matrix
 * @param mat     : the matrix [ Matrix * ]
 * @return trace  : the trace  [ Matrix * ]
 * @descript      : the matrix must be squared;
 *                  the function will return NULL,
 *                  if the matrix has no inverse
 */
Matrix *MatTrace(Matrix *mat);

/**
 * @func MatDeterminant : get the determinant of matrix
 * @param m             : the matrix      [ Matrix * ]
 * @return det          : the determinant [ double   ]
 * @descript            : the matrix must be squared
 */
double MatDeterminant(Matrix *m);

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
 * @func MatInverse : get the inverse of matrix
 * @param m         : the matrix         [ Matrix * ]
 * @return mat      : the inverse matrix [ Matrix * ]
 * @descript        : the matrix must be squared;
 *                    the function will return NULL,
 *                    if the matrix has no inverse
 */
Matrix *MatInverse(Matrix *m);

/**
 * @func SolveLinearEqs : solve linear equations
 * @param A             : the coefficient matrix [ Matrix * ]
 * @param b             : the vector             [ Matrix * ]
 * @return s            : the solution           [ Matrix * ]
 * @descript            : b must be col vector
 */
Matrix *SolveLinearEqs(Matrix *A, Matrix *b);

/**
 * TODO
 * @func SolveEigs : solve the eigen system of matrix
 * @param mat      : the matrix       [ Matrix *  ]
 * @return sys     : the eigen system [ Matrix ** ]
 */
 Matrix **SolveEigs(Matrix *mat);

/************************************************************
 * some vector manipulations -- based on matrix manipulations
 ************************************************************/

/**
 * @func VecAdd : add up two vectors
 * @param v1    : the first vector       [ Matrix * ]
 * @param v2    : the second vector      [ Matrix * ]
 * @return vec  : the sum of two vectors [ Matrix * ]
 * @descript    : vectors has orientation,
 *                if orientations are not matched,
 *                function will exit with failure
 */
Matrix *VecAdd(Matrix *v1, Matrix *v2);
