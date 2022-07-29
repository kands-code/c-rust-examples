/**
 * matrix-ext.c -- matrix operations (extended)
 */

/************************************************************
 * Includes
 ************************************************************/

#include "matrix-ext.h"

#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"

/************************************************************
 * Init the matrix
 ************************************************************/

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

/************************************************************
 * some matrix manipulations
 ************************************************************/

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
 * @param m    : the matrix          [ Matrix * ]
 * @return mat : the adjugate matrix [ Matrix * ]
 * @descript   : the matrix must be squared;
 *               the function will return NULL,
 *               if the matrix has no adjugate
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
 * @func LinearSolver : solve linear equations
 * @param A  : the coefficient matrix [ Matrix * ]
 * @param b  : the vector             [ Matrix * ]
 * @return s : the solution           [ Matrix * ]
 * @descript : b must be col vector
 */
Matrix *LinearSolver(Matrix *A, Matrix *b) { return MatMul(MatInverse(A), b); }

/**
 * @func JacobiLinearSolver : solve linear equations by jacobi iteration
 * @param A  : the coefficient matrix [ Matrix * ]
 * @param b  : the vector             [ Matrix * ]
 * @param k  : number of iterations   [ int      ]
 * @return s : the solution           [ Matrix * ]
 */
Matrix *JacobiLinearSolver(Matrix *A, Matrix *b, int k) {
  Matrix *s = InitMatrix(A->size[0], 1, 0);
  // x_i^{k+1} = -\sum_{n=1, n \ne m}^r (D_{m m}^{-1} R_{m n} x_n^{k})
  //             + D_{m m }^{-1} b_m
  for (int i = 0; i < k; ++i) {
    for (int m = 0; m < A->size[0]; ++m) {
      // the sum
      double sum = 0;
      for (int n = 0; n < A->size[1]; ++n) {
        if (n != m) {
          sum += (1 / GetMatrixVal(A, m, m)) * GetMatrixVal(A, m, n) *
                 GetMatrixVal(s, n, 0);
        }
      }
      SetMatrixVal(s, m, 0,
                   -sum + (1 / GetMatrixVal(A, m, m)) * GetMatrixVal(b, m, 0));
    }
  }

  return s;
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