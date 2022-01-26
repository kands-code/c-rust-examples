/**
 * linear-algebra.c -- function realization
 */

#include "linear-algebra.h"
#include <stdio.h>
#include <stdlib.h>

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
Matrix *InitMatrix(int r, int c, double d) {
  if (r < 1 || c < 1) { // size must greater equal than [1, 1]
    return NULL;
  }

  Matrix *mat = calloc(1, sizeof(Matrix));
  mat->data = calloc(r * c, sizeof(double));

  mat->size[0] = r;
  mat->size[1] = c;

  for (int i = 0; i < r * c; ++i) {
    mat->data[i] = d;
  }

  return mat;
}

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
Matrix *GetMatrixFromArray(int r, int c, int len, double *arr) {
  if (r < 1 || c < 1) { // size must greater equal than [1, 1]
    return NULL;
  }

  Matrix *mat = calloc(1, sizeof(Matrix));
  mat->data = calloc(r * c, sizeof(double));

  mat->size[0] = r;
  mat->size[1] = c;

  for (int i = 0; i < min(len, r * c); ++i) {
    mat->data[i] = arr[i];
  }

  if (len < r * c) {
    for (int i = len; i < r * c; ++i) {
      mat->data[i] = 0.0;
    }
  }

  return mat;
}

/**********************************************************
 * Matrix tools
 **********************************************************/

/**
 * @func PrintMatrixP : print the matrix
 * @param mat         : the matrix    [ Matrix * ]
 * @param p           : the precision [ int      ]
 */
void PrintMatrixP(Matrix *mat, int p) {
  puts("<|Matrix");
  for (int i = 0; i < mat->size[0]; ++i) {
    printf("\t[");
    for (int j = 0; j < mat->size[1]; ++j) {
      printf("%.*f, ", p, mat->data[mat->size[1] * i + j]);
    }
    printf("\b\b]\n");
  }
  puts("|>Matrix");
}

/**
 * @func PrintMatrix : print the matrix
 * @param mat        : the matrix [ Matrix * ]
 * @descript         : default precision is 2
 */
void PrintMatrix(Matrix *mat) { PrintMatrixP(mat, 2); }
