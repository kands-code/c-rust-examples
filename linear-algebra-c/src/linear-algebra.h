#pragma once

/**********************************************************
 * Includes
 **********************************************************/

/**********************************************************
 * Macros
 **********************************************************/

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
 * @func DestoryMatrix : destory matrix
 * @param mat          : the matrix [ Matrix * ]
 */
void DestoryMatrix(Matrix *mat);

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
