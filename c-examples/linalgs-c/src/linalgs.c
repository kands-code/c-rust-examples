/**
 * linear-algebra.c -- function realization
 */

/************************************************************
 * Includes
 ************************************************************/

#include "linalgs.h"
#include <stdio.h>
#include <stdlib.h>

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
  if (r < 1 || c < 1) { // size must greater equal than [1, 1]
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
 * @func InitMatrixByInput : initialize a matrix by user input
 * @return mat             : the matrix [ Matrix * ]
 * @descript               : input element separate by blank character;
 *                           function will return wrong matrix,
 *                           if user do not follow the correct way of typing
 */
Matrix *InitMatrixByInput() {
  int r, c;
  printf("Input the Size of Matrix (r, c): ");
  scanf("%d %d", &r, &c);

  Matrix *mat = calloc(1, sizeof(Matrix));

  mat->data = calloc(r * c, sizeof(double));

  mat->size[0] = r;
  mat->size[1] = c;

  puts("Input the Elements: ");
  for (int i = 0; i < r; ++i) {
    for (int j = 0; j < c; ++j) {
      scanf("%lf", &(mat->data[i * c + j]));
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
 * @func PrintMatrixP : print the matrix with precision
 * @param mat         : the matrix    [ Matrix * ]
 * @param p           : the precision [ int      ]
 */
void PrintMatrixP(Matrix *mat, int p) {
  puts("<<Matrix");
  for (int i = 0; i < mat->size[0]; ++i) {
    printf(" [ ");
    for (int j = 0; j < mat->size[1]; ++j) {
      printf("%-*.*f ", p + 3, p, mat->data[mat->size[1] * i + j]);
    }
    printf("]\n");
  }
  puts("Matrix>>");
}

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
    fputs("Wrong Position!\n", stderr);
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
  Matrix **res = MatToUT(m);
  int l = MIN(m->size[0], m->size[1]);
  for (int i = 0; i < l; ++i) {
    if (0 == GetMatrixVal(res[0], i, i)) {
      break;
    }
    r++;
  }

  DestroyMatrix(res[0]);
  DestroyMatrix(res[1]);

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
    fputs("Wrong Position!\n", stderr);
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
Matrix *MatScalarMul(int n, Matrix *m) {
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
 * @func MatToUT : transform a matrix to upper triangle form
 * @param m      : the matrix [ Matrix *  ]
 * @return res   : the result [ Matrix ** ]
 * @descript     : result contains R, m,
 *                 matrix must be squared
 */
Matrix **MatToUT(Matrix *m) {
  if (m == NULL) {
    fputs("Null Pointer Error!\n", stderr);
    exit(EXIT_FAILURE);
  }

  // the factor, count the number of row changes
  int factor = 1;
  Matrix **res = calloc(2, sizeof(Matrix *));
  res[1] = InitElemMatrix(m->size[0]);

  // copy the matrix
  Matrix *mat = InitMatrix(m->size[0], m->size[1], 0);
  for (int i = 0; i < m->size[0]; ++i) {
    for (int j = 0; j < m->size[1]; ++j) {
      SetMatrixVal(mat, i, j, GetMatrixVal(m, i, j));
    }
  }

  for (int i = 0; i < mat->size[0] - 1; ++i) {
    // check pivot
    // if pivot is zero, then change rows
    if (0 == GetMatrixVal(mat, i, i)) {
      Matrix *tempE = InitElemMatrix(m->size[0]);
      for (int j = i + 1; j < mat->size[0]; ++j) {
        // change the row with non-zero row
        if (0 != GetMatrixVal(mat, j, i)) {
          for (int k = 0; k < mat->size[1]; ++k) {
            double temp = GetMatrixVal(mat, i, k);
            SetMatrixVal(mat, i, k, GetMatrixVal(mat, j, k));
            SetMatrixVal(mat, j, k, temp);
          }
          SetMatrixVal(tempE, i, i, 0);
          SetMatrixVal(tempE, j, j, 0);
          SetMatrixVal(tempE, i, j, 1);
          SetMatrixVal(tempE, j, i, 1);
          res[1] = MatMul(tempE, res[1]);
          DestroyMatrix(tempE);
          factor *= -1;
          break;
        }

        if (j == mat->size[0] - 1) {
          res[0] = MatScalarMul(factor, mat);
          DestroyMatrix(mat);
          return res;
        }
      }
    }

    // if pivot is non-zero, then do reduce
    Matrix *tempE = InitElemMatrix(mat->size[0]);
    for (int j = i + 1; j < mat->size[0]; ++j) {
      double v = GetMatrixVal(mat, j, i) / GetMatrixVal(mat, i, i);
      for (int k = i; k < mat->size[1]; ++k) {
        SetMatrixVal(mat, j, k,
                     GetMatrixVal(mat, j, k) - v * GetMatrixVal(mat, i, k));
      }
      SetMatrixVal(tempE, j, i, -v);
      // PrintMatrix(mat); // for debug, print the matrix
    }
    res[1] = MatMul(tempE, res[1]);
    DestroyMatrix(tempE);
  }

  res[0] = MatScalarMul(factor, mat);
  DestroyMatrix(mat);
  return res;
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

  Matrix **res = MatToUT(m);
  double det = 1;
  for (int i = 0; i < res[0]->size[0]; ++i) {
    det *= GetMatrixVal(res[0], i, i);
  }

  DestroyMatrix(res[0]);
  DestroyMatrix(res[1]);

  return det;
}

/**
 * @func SolveLinearEqs : solve linear equations
 * @param A             : the coefficient matrix [ Matrix * ]
 * @param b             : the vector             [ Matrix * ]
 * @return s            : the solution           [ Matrix * ]
 * @descript            : b must be col vector;
 *                        if no solution, function will return NULL
 */
Matrix *SolveLinearEqs(Matrix *A, Matrix *b) {
  if (b->size[1] != 1) {
    fputs("b Is Not A Vector!\n", stderr);
    exit(EXIT_FAILURE);
  } else if (b->size[0] != A->size[0]) {
    fputs("Size Not Matched!\n", stderr);
    exit(EXIT_FAILURE);
  } else if (A->size[0] != A->size[1] || GetMatrixRank(A) < A->size[0]) {
    fputs("No Numeric Solution!\n", stderr);
    return NULL;
  }

  Matrix **RS = MatToUT(A);
  Matrix *v = MatMul(RS[1], b);
  Matrix *s = InitMatrix(A->size[1], 1, 0);

  PrintMatrix(v); // for debug

  for (int i = A->size[0] - 1; i >= 0; --i) {
    double d = GetMatrixVal(v, i, 0);
    for (int j = A->size[1] - 1; j > i; --j) {
      d -= GetMatrixVal(s, j, 0) * GetMatrixVal(RS[0], i, j);
    }
    SetMatrixVal(s, i, 0, d / GetMatrixVal(RS[0], i, i));
  }

  return s;
}

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
Matrix *VecAdd(Matrix *v1, Matrix *v2) {
  if ((v1->size[0] != 1 && v1->size[1] != 1) ||
      (v2->size[0] != 1 && v2->size[1] != 1)) {
    fputs("The Function Is for Vectors!\n", stderr);
    exit(EXIT_FAILURE);
  }

  return MatAdd(v1, v2);
}
