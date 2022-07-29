/**
 * matrix.c -- matrix operations
 */

/************************************************************
 * Includes
 ************************************************************/

#include "matrix.h"

#include <stdio.h>
#include <stdlib.h>

#include "matrix-ext.h"

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
Matrix *InitMatrix(int r, int c, double d) {
  if (r < 1 || c < 1) {  // size must greater equal than [1, 1]
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
 * @func InitElemMatrix : initialize an element matrix
 * @param n             : the size of matrix [ Matrix * ]
 * @return e            : the element matrix [ Matrix * ]
 */
Matrix *InitElemMatrix(int n) {
  Matrix *e = InitMatrix(n, n, 0);
  for (int i = 0; i < e->size[0]; ++i) {
    SetMatrixVal(e, i, i, 1);
  }

  return e;
}

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
Matrix *InitMatrixFromArray(int r, int c, int len, const double *arr) {
  if (r < 1 || c < 1) {  // size must greater equal than [1, 1]
    return NULL;
  }

  Matrix *mat = calloc(1, sizeof(Matrix));
  mat->data = calloc(r * c, sizeof(double));

  mat->size[0] = r;
  mat->size[1] = c;

  int m = len < r * c ? len : r * c;
  for (int i = 0; i < m; ++i) {
    mat->data[i] = arr[i];
  }

  if (len < r * c) {
    for (int i = len; i < r * c; ++i) {
      mat->data[i] = 0.0;
    }
  }

  return mat;
}

/**
 * @func DestroyMatrix : destroy matrix
 * @param mat          : the matrix [ Matrix * ]
 */
void DestroyMatrix(Matrix *mat) {
  free(mat->data);
  free(mat);
}

/************************************************************
 * Matrix tools
 ************************************************************/

/**
 * @func PrintMatrix : print the matrix
 * @param mat        : the matrix [ Matrix * ]
 * @descript         : default precision is 2
 */
void PrintMatrix(Matrix *mat) { PrintMatrixP(mat, 2); }

/**
 * @func GetMatrixVal : get the element from the matrix by coordinate
 * @param mat         : the matrix [ Matrix * ]
 * @param r           : the row    [ int      ]
 * @param c           : the column [ int      ]
 * @return val        : the value  [ double   ]
 * @descript          : function will exit when the coordinate is illegal
 */
double GetMatrixVal(Matrix *mat, int r, int c) {
  if (r < 0 || r >= mat->size[0] || c < 0 || c >= mat->size[1]) {
    fputs("Get Wrong Position!\n", stderr);
    exit(EXIT_FAILURE);
  }
  return mat->data[r * mat->size[1] + c];
}

/**
 * @func GetMatrixRank : get matrix rank
 * @param m            : the matrix [ Matrix * ]
 * @return r           : the rank   [ int      ]
 */
int GetMatrixRank(Matrix *m) {
  int r = 0;
  LUDR *res = MatLUD(m);
  int l = MIN(m->size[0], m->size[1]);
  for (int i = 0; i < l; ++i) {
    if (0 == GetMatrixVal(res->mats[0], i, i)) {
      break;
    }
    r++;
  }

  DestroyMatrix(res->mats[0]);
  DestroyMatrix(res->mats[1]);
  free(res);

  return r;
}

/**
 * @func SetMatrixVal : get the element from the matrix by coordinate
 * @param mat         : the matrix [ Matrix * ]
 * @param r           : the row    [ int      ]
 * @param c           : the column [ int      ]
 * @param v           : the value  [ double   ]
 * @descript          : function will exit when the coordinate is illegal
 */
void SetMatrixVal(Matrix *mat, int r, int c, double v) {
  if (r < 0 || r >= mat->size[0] || c < 0 || c >= mat->size[1]) {
    fputs("Set Wrong Position!\n", stderr);
    exit(EXIT_FAILURE);
  }

  mat->data[r * mat->size[1] + c] = v;
}

/************************************************************
 * some matrix manipulations
 ************************************************************/

/**
 * @func MatTrans : transpose a matrix
 * @param m       : the matrix            [ Matrix * ]
 * @return mat    : the transposed matrix [ Matrix * ]
 */
Matrix *MatTrans(Matrix *m) {
  if (m == NULL) {
    fputs("Null Pointer Error!\n", stderr);
    exit(EXIT_FAILURE);
  }

  Matrix *mat = InitMatrix(m->size[1], m->size[0], 0);
  for (int i = 0; i < mat->size[0]; ++i) {
    for (int j = 0; j < mat->size[1]; ++j) {
      SetMatrixVal(mat, i, j, GetMatrixVal(m, j, i));
    }
  }

  return mat;
}

/**
 * @func MatAdd : add up two matrices
 * @param m1    : the first matrix        [ Matrix * ]
 * @param m2    : the second matrix       [ Matrix * ]
 * @return mat  : the sum of two matrices [ Matrix * ]
 * @descript    : the size must be matched
 */
Matrix *MatAdd(Matrix *m1, Matrix *m2) {
  if (m1->size[0] != m2->size[0] || m1->size[1] != m2->size[1]) {
    fputs("The Sizes Are Not Matched\n", stderr);
    exit(EXIT_FAILURE);
  }

  Matrix *mat = InitMatrix(m1->size[0], m2->size[1], 0);

  for (int i = 0; i < m1->size[0]; ++i) {
    for (int j = 0; j < m2->size[1]; ++j) {
      SetMatrixVal(mat, i, j, GetMatrixVal(m1, i, j) + GetMatrixVal(m2, i, j));
    }
  }

  return mat;
}

/**
 * @func MatSub : subtract m2 from m1
 * @param m1    : the first matrix        [ Matrix * ]
 * @param m2    : the second matrix       [ Matrix * ]
 * @return mat  : the diff of two matrices [ Matrix * ]
 * @descript    : the size must be matched
 */
Matrix *MatSub(Matrix *m1, Matrix *m2) {
  if (m1->size[0] != m2->size[0] || m1->size[1] != m2->size[1]) {
    fputs("The Sizes Are Not Matched\n", stderr);
    exit(EXIT_FAILURE);
  }

  Matrix *mat = InitMatrix(m1->size[0], m2->size[1], 0);

  for (int i = 0; i < m1->size[0]; ++i) {
    for (int j = 0; j < m2->size[1]; ++j) {
      SetMatrixVal(mat, i, j, GetMatrixVal(m1, i, j) - GetMatrixVal(m2, i, j));
    }
  }

  return mat;
}

/**
 * @func MatMul : multiply scalar with matrix
 * @param n     : the scalar  [ int      ]
 * @param m     : the matrix  [ Matrix * ]
 * @return mat  : the product [ Matrix * ]
 */
Matrix *MatScalarMul(double n, Matrix *m) {
  if (m == NULL) {
    fputs("Null Pointer Error!\n", stderr);
    exit(EXIT_FAILURE);
  }

  Matrix *mat = InitMatrix(m->size[0], m->size[1], 0);
  for (int i = 0; i < mat->size[0]; ++i) {
    for (int j = 0; j < mat->size[1]; ++j) {
      SetMatrixVal(mat, i, j, GetMatrixVal(m, i, j) * n);
    }
  }

  return mat;
}

/**
 * @func MatDiv : matrix divided by scalar
 * @param n     : the scalar   [ double   ]
 * @param m     : the matrix   [ Matrix * ]
 * @return mat  : the quotient [ Matrix * ]
 */
Matrix *MatScalarDiv(Matrix *m, double n) {
  const double ESP = 1E-7;
  if (m == NULL) {
    fputs("Null Pointer Error!\n", stderr);
    exit(EXIT_FAILURE);
  } else if (n < ESP) {
    fputs("Divided By Zero!\n", stderr);
    exit(EXIT_FAILURE);
  }

  Matrix *mat = InitMatrix(m->size[0], m->size[1], 0);
  for (int i = 0; i < mat->size[0]; ++i) {
    for (int j = 0; j < mat->size[1]; ++j) {
      SetMatrixVal(mat, i, j, GetMatrixVal(m, i, j) / n);
    }
  }

  return mat;
}

/**
 * @func MatMul : multiply m1 and m2
 * @param m1    : the first matrix            [ Matrix * ]
 * @param m2    : the second matrix           [ Matrix * ]
 * @return mat  : the product of two matrices [ Matrix * ]
 * @descript    : the size must be matched
 */
Matrix *MatMul(Matrix *m1, Matrix *m2) {
  if (m1->size[1] != m2->size[0]) {
    fputs("The Sizes Are Not Matched\n", stderr);
    exit(EXIT_FAILURE);
  }

  Matrix *mat = InitMatrix(m1->size[0], m2->size[1], 0);

  for (int i = 0; i < m1->size[0]; ++i) {
    for (int j = 0; j < m2->size[1]; ++j) {
      double sum = 0;
      for (int k = 0; k < m1->size[1]; ++k) {
        sum += GetMatrixVal(m1, i, k) * GetMatrixVal(m2, k, j);
      }
      SetMatrixVal(mat, i, j, sum);
    }
  }

  return mat;
}

/**
 * @func MatPow : the power of matrix
 * @param m     : the matrix  [ Matrix *     ]
 * @param n     : the power   [ unsigned int ]
 * @return mat  : the result  [ Matrix *     ]
 * @descript    : the matrix must be squared
 */
Matrix *MatPow(Matrix *m, int n) {
  Matrix *mat = InitElemMatrix(m->size[0]);
  if (n < 0) {
    Matrix *inv = MatInverse(m);
    for (int i = n; i < 0; ++i) {
      Matrix *tempM = mat;
      mat = MatMul(inv, mat);
      DestroyMatrix(tempM);
    }
    DestroyMatrix(inv);
  } else {
    for (int i = 0; i < n; ++i) {
      Matrix *tempM = mat;
      mat = MatMul(m, mat);
      DestroyMatrix(tempM);
    }
  }

  return mat;
}

/**
 * @func MatTrace : get the trace of matrix
 * @param mat     : the matrix [ Matrix * ]
 * @return trace  : the trace  [ Matrix * ]
 * @descript      : the matrix must be squared;
 *                  the function will return NULL,
 *                  if the matrix has no inverse
 */
Matrix *MatTrace(Matrix *mat) {
  if (mat->size[0] != mat->size[1]) {
    fputs("The Matrix Is Not Squared!\n", stderr);
    exit(EXIT_FAILURE);
  }

  Matrix *trace = InitMatrix(mat->size[0], 1, 0);
  for (int i = 0; i < mat->size[0]; ++i) {
    SetMatrixVal(trace, i, 0, GetMatrixVal(mat, i, i));
  }

  return trace;
}

/**
 * @func MatDeterminant : get the determinant of matrix
 * @param m             : the matrix      [ Matrix * ]
 * @return det          : the determinant [ double   ]
 * @descript            : the matrix must be squared
 */
double MatDeterminant(Matrix *m) {
  if (m->size[0] != m->size[1]) {
    fputs("The Matrix Is Not Squared!\n", stderr);
    exit(EXIT_FAILURE);
  }

  LUDR *res = MatLUD(m);
  double det = 1;
  for (int i = 0; i < res->mats[0]->size[0]; ++i) {
    det *= GetMatrixVal(res->mats[0], i, i);
  }
  det *= res->fac;

  DestroyMatrix(res->mats[0]);
  DestroyMatrix(res->mats[1]);
  free(res);

  return det;
}

/**
 * @func MatInverse : get the inverse of matrix
 * @param m         : the matrix         [ Matrix * ]
 * @return mat      : the inverse matrix [ Matrix * ]
 * @descript        : the matrix must be squared;
 *                    the function will return NULL,
 *                    if the matrix has no inverse
 */
Matrix *MatInverse(Matrix *m) {
  return MatScalarDiv(MatAdjugate(m), MatDeterminant(m));
}
