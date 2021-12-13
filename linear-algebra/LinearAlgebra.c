#include "LinearAlgebra.h"

// --- necessary includes

#include "libs/Eq.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// --- some function implementations

// === other part

int getNumberOfInversions(int len, int *arr) {
  int numberOfInversions = 0;
  for (int i = 0; i < len - 1; ++i) {
    for (int j = i; j < len; ++j) {
      if (arr[i] > arr[j])
        ++numberOfInversions;
    }
  }
  return numberOfInversions;
}

// === matrix part

matrix *matrixInit(int i, int j) {
  // get a matrix pointer
  matrix *mat = calloc(1, sizeof(matrix));
  // storage the dimension infomation into dim
  mat->dim = calloc(2, sizeof(int));
  mat->dim[0] = i;
  mat->dim[1] = j;
  // get a space for data
  mat->data = calloc(mat->dim[0] * mat->dim[1], sizeof(double));
  // return the matrix pointer
  return mat;
}

matrix *matrixGetDiagonalMatrix(int len, double *diag) {
  // get a normal matrix
  matrix *diagonalMatrix = matrixInit(len, len);
  // put the element of diag to the diagonal of the matrix
  for (int i = 0; i < len; ++i) {
    diagonalMatrix->data[i * diagonalMatrix->dim[1] + i] = diag[i];
  }
  // return the diagonal matrix
  return diagonalMatrix;
}

matrix *matrixGetIndentityMatrix(int len) {
  matrix *identityMatrix = matrixInit(len, len);
  for (int i = 0; i < len; ++i) {
    identityMatrix->data[i * identityMatrix->dim[1] + i] = 1;
  }

  return identityMatrix;
}

matrix *matrixGetMatrixByArray(int r, int c, double *arr) {
  // get a matrix pointer
  matrix *mat = matrixInit(r, c);
  // traverse the matrix and the array
  for (int i = 0; i < r; ++i) {
    for (int j = 0; j < c; ++j) {
      // assign the value to matrix
      mat->data[i * mat->dim[1] + j] = arr[i * c + j];
    }
  }
  // return the matrix
  return mat;
}

void matrixPrintWithPrecision(matrix *mat, int precision) {
  // traverse the matrix
  for (int i = 0; i < mat->dim[0]; ++i) {
    for (int j = 0; j < mat->dim[1]; ++j) {
      // print each element
      printf("%.*f\t", precision, mat->data[i * mat->dim[1] + j]);
    }
    // get a new line
    putchar('\n');
  }
}

void matrixPrint(matrix *mat) {
  // default precision is 3
  matrixPrintWithPrecision(mat, 3);
}

matrix *matrixTranspose(matrix *mat) {
  matrix *transposedMatrix = matrixInit(mat->dim[1], mat->dim[0]);
  for (int i = 0; i < transposedMatrix->dim[0]; ++i) {
    for (int j = 0; j < transposedMatrix->dim[1]; ++j) {
      transposedMatrix->data[i * transposedMatrix->dim[1] + j] =
          mat->data[j * mat->dim[1] + i];
    }
  }
  return transposedMatrix;
}

matrix *matrixAdditionWithNum(double num, matrix *mat) {
  // get a matrix as the result
  matrix *res = matrixInit(mat->dim[0], mat->dim[1]);
  // traverse the matrix
  for (int i = 0; i < mat->dim[0]; ++i) {
    for (int j = 0; j < mat->dim[1]; ++j) {
      // add the element and num
      res->data[i * mat->dim[1] + j] = mat->data[i * mat->dim[1] + j] + num;
    }
  }
  // return the result
  return res;
}

matrix *matrixMultiplyWithNum(double num, matrix *mat) {
  // get a matrix as the result
  matrix *res = matrixInit(mat->dim[0], mat->dim[1]);
  // traverse the matrix
  for (int i = 0; i < mat->dim[0]; ++i) {
    for (int j = 0; j < mat->dim[1]; ++j) {
      // multiply the element by num
      res->data[i * mat->dim[1] + j] = mat->data[i * mat->dim[1] + j] * num;
    }
  }
  // return the result
  return res;
}

matrix *matrixAddition(matrix *m1, matrix *m2) {
  // if the sizes are not equal, then they cannot do addition
  if (m1->dim[0] != m2->dim[0] || m1->dim[1] != m2->dim[1]) {
    printf("Dimensions are not match\n");
    exit(EXIT_FAILURE);
  }
  // get a matrix as the result
  matrix *res = matrixInit(m1->dim[0], m1->dim[1]);
  // traverse the two matrices
  for (int i = 0; i < res->dim[0]; ++i) {
    for (int j = 0; j < res->dim[j]; ++j) {
      // add up the corresponding elements
      res->data[i * res->dim[1] + j] =
          m1->data[i * m1->dim[1] + j] + m2->data[i * m2->dim[1] + j];
    }
  }
  // return the result
  return res;
}

matrix *matrixMultiply(matrix *m1, matrix *m2) {
  // to do multiplication, the matrices must have matched dimensions
  if (m1->dim[1] != m2->dim[0]) {
    printf("Dimensions are not match\n");
    exit(EXIT_FAILURE);
  }
  // get a result matrix
  matrix *res = matrixInit(m1->dim[0], m2->dim[1]);
  // traverse two matrices
  for (int i = 0; i < m1->dim[0]; ++i) {
    for (int j = 0; j < m1->dim[1]; ++j) {
      for (int k = 0; k < m2->dim[1]; ++k) {
        // C[i, k] = sum(A[i, j], B[j, k], j)
        res->data[i * res->dim[1] + k] +=
            m1->data[i * m1->dim[1] + j] * m2->data[j * m2->dim[1] + k];
      }
    }
  }
  // return the result
  return res;
}

double matrixDeterminant(matrix *mat) {
  // the matrix must be squared
  if (mat->dim[0] != mat->dim[1]) {
    printf("The matrix must be squared!\n");
    exit(EXIT_FAILURE);
  }
  // define the determinant variable
  double determinant = 1.0;
  // format the matrix
  matrix *formatedMatrix = matrixToUprightTriangleForm(mat);
  // the determinant is the product
  // of the diagonal of a upright-triangle matrix
  for (int i = 0; i < mat->dim[0]; ++i) {
    determinant *= formatedMatrix->data[i * formatedMatrix->dim[1] + i];
  }
  // free the matrix pointer
  free(formatedMatrix);
  // return the determinant
  return determinant;
}

// exchange two lines of a matrix
void matrixExchangeLine(matrix *mat, int r1, int r2) {
  // temporary variable
  double temp = 0.0;
  for (int i = 0; i < mat->dim[1]; ++i) {
    // swap two lines
    temp = mat->data[r1 * mat->dim[1] + i];
    mat->data[r1 * mat->dim[1] + i] = mat->data[r2 * mat->dim[1] + i];
    mat->data[r2 * mat->dim[1] + i] = temp;
  }
}

matrix *matrixToUprightTriangleForm(matrix *mat) {
  // as a factor
  int factor = 1;
  // get a matrix pointer
  matrix *formatedMatrix = matrixInit(mat->dim[0], mat->dim[1]);
  for (int i = 0; i < mat->dim[0] * mat->dim[1]; ++i) {
    formatedMatrix->data[i] = mat->data[i];
  }

  // traverse the matrix
  for (int i = 0; i < formatedMatrix->dim[1] - 1; ++i) {
    // check the pivot whether a zero
    if (equalsToZero(formatedMatrix->data[i * formatedMatrix->dim[0] + i])) {
      // exchange the line which element in i column is nonzero
      for (int r = i + 1; r < formatedMatrix->dim[0]; ++r) {
        if (formatedMatrix->data[r * formatedMatrix->dim[1] + i] != 0) {
          matrixExchangeLine(formatedMatrix, i, r);
          // use factor to count
          factor *= -1;
          break;
        }
      }
    }
    for (int j = i + 1; j < formatedMatrix->dim[0]; ++j) {
      // if the element in (j, i) is zero, then skip
      if (equalsToZero(formatedMatrix->data[j * formatedMatrix->dim[0] + i]))
        continue;
      // reduce
      double m = formatedMatrix->data[j * formatedMatrix->dim[1] + i] /
                 formatedMatrix->data[i * formatedMatrix->dim[1] + i];
      for (int k = i; k < formatedMatrix->dim[1]; ++k) {
        formatedMatrix->data[j * formatedMatrix->dim[1] + k] -=
            m * formatedMatrix->data[i * formatedMatrix->dim[1] + k];
      }
    }
  }
  // multiply formatedMatrix by factor
  matrix *res = matrixMultiplyWithNum(factor, formatedMatrix);
  // free the matrix pointer
  free(formatedMatrix);
  // return the result
  return res;
}

double matrixGetAlgebraicCofactor(matrix *mat, int r, int c) {
  // the dimensions must bigger than 1 and the matrix must be squared
  if (mat->dim[0] != mat->dim[1] || mat->dim[0] == 1) {
    printf("The Dimensions are not appropriate\n");
    exit(EXIT_FAILURE);
  }
  // The row or column must bigger than 0
  if (r < 0 || c < 0) {
    printf("The row or column must bigger than 0\n");
    exit(EXIT_FAILURE);
  }
  // get a submatrix
  matrix *submatrix = matrixInit(mat->dim[0] - 1, mat->dim[1] - 1);
  // set a counter
  int cnt = 0;
  for (int i = 0; i < mat->dim[0]; ++i) {
    if (i == r)
      continue;
    for (int j = 0; j < mat->dim[1]; ++j) {
      if (j == c)
        continue;
      // copy the rest element to submatrix
      submatrix->data[cnt++] = mat->data[i * mat->dim[1] + j];
    }
  }

  // get the algebraic cofactor
  return (((r + c) & 1) ? -1 : 1) * matrixDeterminant(submatrix);
}

matrix *matrixAdjointMatrix(matrix *mat) {
  // get a matrix pointer
  matrix *adjointMatrix = matrixInit(mat->dim[0], mat->dim[1]);
  // traverse the matrix
  for (int i = 0; i < adjointMatrix->dim[0]; ++i) {
    for (int j = 0; j < adjointMatrix->dim[1]; ++j) {
      // use the definition of adjoint matrix
      // Adjm(i, j) = Ac(j, i), Ac is the algebraic cofactor of mat
      adjointMatrix->data[i * adjointMatrix->dim[1] + j] =
          matrixGetAlgebraicCofactor(mat, j, i);
    }
  }
  // return the adjoint matrix
  return adjointMatrix;
}

matrix *matrixInverse(matrix *mat) {
  // inverse matrix is 1/|M| * Adj(M)
  if (mat->dim[0] != mat->dim[1]) {
    printf("The dimensions are not match\n");
    exit(EXIT_FAILURE);
  }
  // the determinant of matrix cannot be zero
  if (equalsToZero(matrixDeterminant(mat))) {
    printf("The matrix is singular!\n");
    exit(EXIT_FAILURE);
  }
  // use the definition
  matrix *adjointMatrix = matrixAdjointMatrix(mat);
  double determinant = matrixDeterminant(mat);
  return matrixMultiplyWithNum(1.0 / determinant, adjointMatrix);
}

// === vector part

double vectorDotProduct(matrix *v1, matrix *v2) {
  // check the definitions
  if (v1->dim[0] != v2->dim[0] || v1->dim[1] != v2->dim[1]) {
    printf("The dimensions are not matched.\n");
    exit(EXIT_FAILURE);
  }
  // the input must be vectors
  if (v1->dim[0] != 1 && v1->dim[1] != 1) {
    printf("The inputs are not vector!");
    exit(EXIT_FAILURE);
  }

  double res = 0;
  for (int i = 0; i < (v1->dim[0] == 1 ? v1->dim[1] : v1->dim[0]); ++i) {
    res += v1->data[i] * v2->data[i];
  }
  return res;
}
