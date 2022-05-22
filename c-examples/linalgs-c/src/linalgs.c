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
  fflush(stdout);
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
  if (NULL == mat) {
    fputs("The Matrix Is Not Exist!\n", stderr);
    return;
  }
  puts("\n<<Matrix");
  for (int i = 0; i < mat->size[0]; ++i) {
    printf(" [ ");
    fflush(stdout);
    for (int j = 0; j < mat->size[1]; ++j) {
      printf("%-*.*f ", p + 3, p, GetMatrixVal(mat, i, j));
      fflush(stdout);
    }
    printf("]\n");
  }
  puts("Matrix>>\n");
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
 * @func MatKronecker : the Kronecker product of m1 and m2
 * @param m1          : the first matrix  [ Matrix * ]
 * @param m2          : the second matrix [ Matrix * ]
 * @return p          : the product       [ Matrix * ]
 */
Matrix *MatKronecker(Matrix *m1, Matrix *m2) {
  if (NULL == m1 || NULL == m2) {
    fputs("The Matrix Does Not Exist!\n", stderr);
    exit(EXIT_FAILURE);
  }

  Matrix *p =
      InitMatrix(m1->size[0] * m2->size[0], m1->size[1] * m2->size[1], 0);
  for (int i1 = 0; i1 < m1->size[0]; ++i1) {
    for (int j1 = 0; j1 < m1->size[1]; ++j1) {
      for (int i2 = 0; i2 < m2->size[0]; ++i2) {
        for (int j2 = 0; j2 < m2->size[1]; ++j2) {
          SetMatrixVal(p, i2 * m1->size[0] + i1, j2 * m1->size[1] + j1,
                       GetMatrixVal(m1, i1, j1) * GetMatrixVal(m2, i2, j2));
        }
      }
    }
  }

  return p;
}

/**
 * @func MatLUD : LU Decomposition
 * @param m     : the matrix [ Matrix * ]
 * @return res  : the result [ LUDR *   ]
 * @descript    : result contains R, L^-1,
 *                matrix must be squared
 */
LUDR *MatLUD(Matrix *m) {
  if (m == NULL) {
    fputs("Null Pointer Error!\n", stderr);
    exit(EXIT_FAILURE);
  }

  // the result
  LUDR *res = calloc(1, sizeof(LUDR));
  res->fac = 1;
  res->mats = calloc(2, sizeof(Matrix *));
  res->mats[1] = InitElemMatrix(m->size[0]);

  // copy the matrix
  res->mats[0] = InitMatrix(m->size[0], m->size[1], 0);
  for (int i = 0; i < m->size[0]; ++i) {
    for (int j = 0; j < m->size[1]; ++j) {
      SetMatrixVal(res->mats[0], i, j, GetMatrixVal(m, i, j));
    }
  }

  for (int i = 0; i < res->mats[0]->size[0] - 1; ++i) {
    // check pivot
    // if pivot is zero, then change rows
    if (0 == GetMatrixVal(res->mats[0], i, i)) {
      Matrix *tempE = InitElemMatrix(m->size[0]);
      for (int j = i + 1; j < res->mats[0]->size[0]; ++j) {
        // change the row with non-zero row
        if (0 != GetMatrixVal(res->mats[0], j, i)) {
          for (int k = 0; k < res->mats[0]->size[1]; ++k) {
            double temp = GetMatrixVal(res->mats[0], i, k);
            SetMatrixVal(res->mats[0], i, k, GetMatrixVal(res->mats[0], j, k));
            SetMatrixVal(res->mats[0], j, k, temp);
          }
          SetMatrixVal(tempE, i, i, 0);
          SetMatrixVal(tempE, j, j, 0);
          SetMatrixVal(tempE, i, j, 1);
          SetMatrixVal(tempE, j, i, 1);
          res->mats[1] = MatMul(tempE, res->mats[1]);
          DestroyMatrix(tempE);
          res->fac *= -1;
          break;
        }

        if (j == res->mats[0]->size[0] - 1) {
          return res;
        }
      }
    }

    // if pivot is non-zero, then do reduce
    Matrix *tempE = InitElemMatrix(res->mats[0]->size[0]);
    for (int j = i + 1; j < res->mats[0]->size[0]; ++j) {
      double v =
          GetMatrixVal(res->mats[0], j, i) / GetMatrixVal(res->mats[0], i, i);
      for (int k = i; k < res->mats[0]->size[1]; ++k) {
        SetMatrixVal(res->mats[0], j, k,
                     GetMatrixVal(res->mats[0], j, k) -
                         v * GetMatrixVal(res->mats[0], i, k));
      }
      SetMatrixVal(tempE, j, i, -v);
    }
    res->mats[1] = MatMul(tempE, res->mats[1]);
    DestroyMatrix(tempE);
  }

  return res;
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
 * @func MatAlgCofactor : get the algebraic cofactor of matrix
 * @param mat           : the matrix              [ Matrix * ]
 * @param r             : the row                 [ int      ]
 * @param c             : the column              [ int      ]
 * @return algCofactor  : the algebraic cofactor  [ double   ]
 * @descript            : r and c start from 0
 */
double MatAlgCofactor(Matrix *mat, int r, int c) {
  if (mat->size[0] < 2 || mat->size[1] < 2) {
    fputs("The Matrix So Small!\n", stderr);
    exit(EXIT_FAILURE);
  } else if (r >= mat->size[0] || r < 0 || c >= mat->size[1] || c < 0) {
    fputs("The Position Is Wrong!\n", stderr);
  }

  Matrix *subMatrix = InitMatrix(mat->size[0] - 1, mat->size[1] - 1, 0);
  int rc = 0;
  for (int i = 0; i < mat->size[0]; ++i) {
    int cc = 0;
    if (i == r) {
      rc = 1;
      continue;
    }
    for (int j = 0; j < mat->size[1]; ++j) {
      if (j == c) {
        cc = 1;
        continue;
      }
      SetMatrixVal(subMatrix, i - rc, j - cc, GetMatrixVal(mat, i, j));
    }
  }

  int f = r + c & 1 ? -1 : 1;
  double algCofactor = f * MatDeterminant(subMatrix);
  DestroyMatrix(subMatrix);

  return algCofactor;
}

/**
 * @func MatAdjugate : get the adjugate of matrix
 * @param m          : the matrix          [ Matrix * ]
 * @return mat       : the adjugate matrix [ Matrix * ]
 * @descript         : the matrix must be squared;
 *                     the function will return NULL,
 *                     if the matrix has no adjugate
 */
Matrix *MatAdjugate(Matrix *m) {
  if (m->size[0] != m->size[1]) {
    fputs("The Matrix Is Not Squared!\n", stderr);
    exit(EXIT_FAILURE);
  }
  if (MatDeterminant(m) == 0) {
    fputs("The Matrix Has No Inverse!\n", stderr);
    return NULL;
  }

  Matrix *mat = InitMatrix(m->size[0], m->size[1], 0);
  for (int i = 0; i < mat->size[0]; ++i) {
    for (int j = 0; j < mat->size[1]; ++j) {
      SetMatrixVal(mat, i, j, MatAlgCofactor(m, j, i));
    }
  }

  return mat;
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

/**
 * @func SolveLinearEqs : solve linear equations
 * @param A             : the coefficient matrix [ Matrix * ]
 * @param b             : the vector             [ Matrix * ]
 * @return s            : the solution           [ Matrix * ]
 * @descript            : b must be col vector
 */
Matrix *SolveLinearEqs(Matrix *A, Matrix *b) {
  return MatMul(MatInverse(A), b);
}

/**
 * TODO
 * @func SolveEigs : solve the eigen system of matrix
 * @param mat      : the matrix       [ Matrix *  ]
 * @return sys     : the eigen system [ Matrix ** ]
 */
Matrix **SolveEigs(Matrix *mat) { return NULL; }

// TODO
// Need more decomposition functions

// Vector is matrix! No need more functions
