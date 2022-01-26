#pragma once

/**********************************************************
 * Macros
 **********************************************************/

/**
 * @macroFunc max : return the bigger one
 * @param a       : the first param
 * @param b       : the second param
 * @return result : the bigger one between a and b
 */
#define max(a, b) a > b ? a : b

/**
 * @macroFunc min : return the smaller one
 * @param a       : the first param
 * @param b       : the second param
 * @return result : the smaller one between a and b
 */
#define min(a, b) a < b ? a : b

/**********************************************************
 * Type define
 **********************************************************/

/**
 * @type Matrix  : the basic element in linear algebra
 * @content data : the value of matrix [ double * ]
 * @content size : the size of matrix  [ int *    ]
 * @descript     : vector is also a matrix
 */
typedef struct {
  double *data;
  int size[2];
} Matrix;

/**********************************************************
 * Init the matrix
 **********************************************************/

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
 * @func GetMatrixFromArray : initialize a matrix from an array
 * @param r                 : the row number      [ int      ]
 * @param c                 : the column number   [ int      ]
 * @param len               : the length of array [ int      ]
 * @param arr               : the array           [ double * ]
 * @return mat              : the matrix          [ Matrix * ]
 * @descript                : function will return null for illegal size,
 *                            if size is bigger than array, fill with `0`,
 *                            if size is smaller than array, truncate
 */
Matrix *GetMatrixFromArray(int r, int c, int len, double *arr);

/**
 *
 */

/**********************************************************
 * Matrix tools
 **********************************************************/

/**
 * @func PrintMatrixP : print the matrix
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
