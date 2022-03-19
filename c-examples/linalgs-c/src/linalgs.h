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
Matrix *InitMatrixFromArray(int r, int c, int len, double *arr);

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
 * @func MatMul : multiply m1 and m2
 * @param m1    : the first matrix            [ Matrix * ]
 * @param m2    : the second matrix           [ Matrix * ]
 * @return mat  : the product of two matrices [ Matrix * ]
 * @descript    : the size must be matched
 */
Matrix *MatMul(Matrix *m1, Matrix *m2);

/************************************************************
 * some vector manipulations -- based on matrix manipulations
 ************************************************************/

/**
 * @func VecAdd : add up two vectors
 * @param v1    : the first vector       [ Matrix * ]
 * @param v2    : the second vector      [ Matrix * ]
 * @return vec  : the sum of two vectors [ Matrix * ]
 * @descript    : vectors has orientation
 *                if orientations are not matched
 *                function will exit with failure
 */
Matrix *VecAdd(Matrix *v1, Matrix *v2);
