#include "LinearAlgebra.h"

// --- necessary includes

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// --- some definitions

double eps = 1e-6;

// --- some function implementations

// === equals part

bool equalsToZero(double num) {
  // use abs and eps instead of "== 0"
  if (absT(num) < eps)
    return true;
  return false;
}

bool equalsForNum(double n1, double n2) { return equalsToZero(n1 - n2); }

bool equalsForString(char *s1, char *s2) {
  int i = 0;
  for (i = 0; *(s1 + i) != '\0' && *(s2 + i) != '\0'; ++i) {
    if (*(s1 + i) != *(s2 + i)) {
      return false;
    }
  }

  if (*(s1 + i) == '\0' && *(s2 + i) == '\0')
    return true;
  return false;
}

bool equalsForMatrix(matrix *m1, matrix *m2) {
  if (!equalsT(m1->dim[0], m2->dim[0]) || !equalsT(m1->dim[1], m2->dim[1]))
    return false;
  for (int i = 1; i < m1->dim[0] * m1->dim[1]; ++i) {
    if (!equalsT(m1->data[i], m2->data[i]))
      return false;
  }
  return true;
}

bool equalsForIntegral(int i1, int i2) { return i1 == i2; }

bool equalsForVector(vector *v1, vector *v2) {
  if (!equalsT(v1->dim, v2->dim) || !equalsT(v1->orient, v2->orient))
    return false;
  for (int i = 0; i < v1->dim; ++i) {
    if (!equalsT(v1->data[i], v2->data[i]))
      return false;
  }
  return true;
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
  puts("matrix |>");
  // traverse the matrix
  for (int i = 0; i < mat->dim[0]; ++i) {
    putchar('[');
    for (int j = 0; j < mat->dim[1]; ++j) {
      // print each element
      printf("%.*f\t", precision,
             equalsToZero(mat->data[i * mat->dim[1] + j])
                 ? 0
                 : mat->data[i * mat->dim[1] + j]);
    }
    // get a new line
    printf("]\n");
  }
  putchar('\n');
}

void matrixPrint(matrix *mat) {
  // default precision is 3
  // can be implementated by "%g"
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
  if (!equalsT(m1->dim[0], m2->dim[0]) || !equalsT(m1->dim[1], m2->dim[1])) {
    printf("Dimensions are not match\n");
    exit(EXIT_FAILURE);
  }
  // get a matrix as the result
  matrix *res = matrixInit(m1->dim[0], m1->dim[1]);
  // traverse the two matrices
  for (int i = 0; i < res->dim[0] * res->dim[1]; ++i) {
    // add up the corresponding elements
    res->data[i] = m1->data[i] + m2->data[i];
  }
  // return the result
  return res;
}

matrix *matrixSubtraction(matrix *m1, matrix *m2) {
  // if the sizes are not equal, then they cannot do addition
  if (!equalsT(m1->dim[0], m2->dim[0]) || !equalsT(m1->dim[1], m2->dim[1])) {
    printf("Dimensions are not match\n");
    exit(EXIT_FAILURE);
  }
  matrix *res = matrixInit(m1->dim[0], m2->dim[1]);
  for (int i = 0; i < res->dim[0] * res->dim[1]; ++i) {
    res->data[i] = m1->data[i] - m2->data[i];
  }
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

matrix *matrixDivision(matrix *m1, matrix *m2) {
  return matrixMultiply(m1, matrixInverse(m2));
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
  for (int i = 0, bias = 0; i < formatedMatrix->dim[0] - 1; ++i) {
    // check the pivot whether a zero
    if (equalsToZero(
            formatedMatrix->data[i * formatedMatrix->dim[1] + i + bias])) {
      // exchange the line which element in i column is nonzero
      for (int r = i + 1; r < formatedMatrix->dim[0]; ++r) {
        if (!equalsToZero(
                formatedMatrix->data[r * formatedMatrix->dim[1] + i + bias])) {
          matrixExchangeLine(formatedMatrix, i, r);

          /* print steps
            puts("\n=============================");
            printf("r%d <-> r%d\n", i + 1, r + 1);
            matrixPrint(formatedMatrix);
            puts("=============================\n");
          */

          // use factor to count
          factor *= -1;
          break;
        }
        // >> some magic
        if (r == formatedMatrix->dim[0] - 1) {
          --i;
          ++bias;
          continue;
        }
      }
    }
    for (int j = i + 1; j < formatedMatrix->dim[0]; ++j) {
      // if the element in (j, i) is zero, then skip
      if (equalsToZero(
              formatedMatrix->data[j * formatedMatrix->dim[1] + i + bias]))
        continue;
      // reduce
      double m = formatedMatrix->data[j * formatedMatrix->dim[1] + i + bias] /
                 formatedMatrix->data[i * formatedMatrix->dim[1] + i + bias];
      for (int k = i + bias; k < formatedMatrix->dim[1]; ++k) {
        formatedMatrix->data[j * formatedMatrix->dim[1] + k] -=
            m * formatedMatrix->data[i * formatedMatrix->dim[1] + k];
      }

      /* print steps
        puts("\n=============================");
        printf("r%d - r%d * %.3f\n", j + 1, i + 1, m);
        matrixPrint(formatedMatrix);
        puts("=============================\n");
      */
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

int matrixGetMatrixRank(matrix *mat) {
  int rank = 0;
  matrix *formatedMatrix = matrixToUprightTriangleForm(mat);
  for (int i = 0; i < formatedMatrix->dim[0]; ++i) {
    for (int j = 0; j < formatedMatrix->dim[1]; ++j) {
      if (!equalsToZero(formatedMatrix->data[i * formatedMatrix->dim[1] + j])) {
        ++rank;
        break;
      }
    }
  }
  return rank;
}

double matrixGetMatrixTrace(matrix *mat) {
  double trace = 0.0;
  int len = MIN(mat->dim[0], mat->dim[1]);
  for (int i = 0; i < len; ++i) {
    trace += mat->data[i * mat->dim[1] + i];
  }
  return trace;
}

// === vector part

vector *vectorInit(int len, char o) {
  if (!equalsT(o, 'r') && !equalsT(o, 'c')) {
    printf("The orientation can only be Row(r) or Column(c)!\n");
    exit(EXIT_FAILURE);
  }
  // get a vector pointer
  vector *vec = calloc(1, sizeof(vector));
  // init some attributes
  vec->dim = len;
  vec->orient = o;
  vec->data = calloc(vec->dim, sizeof(double));
  // return the pointer
  return vec;
}

vector *vectorGetVectorByArray(int len, char o, double *arr) {
  vector *vec = vectorInit(len, o);

  for (int i = 0; i < vec->dim; ++i) {
    vec->data[i] = arr[i];
  }
  return vec;
}

void vectorPrintWithPrecision(vector *vec, int precision) {
  puts("vec |>");
  if (equalsT(vec->orient, 'r')) {
    putchar('[');
    for (int i = 0; i < vec->dim - 1; ++i) {
      printf("%.*f, ", precision, vec->data[i]);
    }
    printf("%.*f]\n\n", precision, vec->data[vec->dim - 1]);
  } else if (equalsT(vec->orient, 'c')) {
    puts("@==");
    for (int i = 0; i < vec->dim; ++i) {
      printf("%.*f\n", precision, vec->data[i]);
    }
    puts("@==\n");
  } else {
    printf("The orientation is illegal");
    exit(EXIT_FAILURE);
  }
}

void vectorPrint(vector *vec) {
  // default precision is 3
  // can be implementated by "%g"
  vectorPrintWithPrecision(vec, 3);
}

vector *vectorAddition(vector *v1, vector *v2) {
  if (!equalsT(v1->dim, v2->dim) && !equalsT(v1->orient, v2->orient)) {
    printf("The dimensions are not equal!\n");
    exit(EXIT_FAILURE);
  }
  vector *res = vectorInit(v1->dim, v1->orient);
  for (int i = 0; i < res->dim; ++i) {
    res->data[i] = v1->data[i] + v2->data[i];
  }
  return res;
}

vector *vectorSubtraction(vector *v1, vector *v2) {
  if (!equalsT(v1->dim, v2->dim) && !equalsT(v1->orient, v2->orient)) {
    printf("The dimensions are not equal!\n");
    exit(EXIT_FAILURE);
  }
  vector *res = vectorInit(v1->dim, v1->orient);
  for (int i = 0; i < res->dim; ++i) {
    res->data[i] = v1->data[i] - v2->data[i];
  }
  return res;
}
double vectorDotProduct(vector *v1, vector *v2) {
  // check the definitions
  if (!equalsT(v1->dim, v2->dim) || !equalsT(v1->orient, v1->orient)) {
    printf("The dimensions are not matched.\n");
    exit(EXIT_FAILURE);
  }

  double res = 0;
  for (int i = 0; i < v1->dim; ++i) {
    res += v1->data[i] * v2->data[i];
  }
  return res;
}

vector *vectorCrossProduct(vector *v1, vector *v2) {
  // for 2D vector such as [a, b]
  // we will expand it to [a, b, 0]
  if ((!equalsT(v1->dim, 2) && !equalsT(v1->dim, 3)) ||
      (!equalsT(v2->dim, 2) && !equalsT(v2->dim, 3))) {
    printf("The length of the vector must be 2 or 3");
    exit(EXIT_FAILURE);
  }

  if (!equalsT(v1->orient, v2->orient)) {
    printf("The orientation of vectors must be equal!\n");
    exit(EXIT_FAILURE);
  }

  vector *crossProduct = vectorInit(3, v1->orient);

#define tryGet(vec, pos) ((vec)->dim > pos ? (vec)->data[pos] : 0)

  crossProduct->data[0] =
      v1->data[1] * tryGet(v2, 2) - v2->data[1] * tryGet(v1, 2);
  crossProduct->data[1] =
      -v1->data[0] * tryGet(v2, 2) + v2->data[0] * tryGet(v1, 2);
  crossProduct->data[2] = v1->data[0] * v2->data[1] - v2->data[0] * v1->data[1];

#undef tryGet

  return crossProduct;
}

// === other part

double absT(double num) {
  // simple implementation
  return num < 0 ? -num : num;
}

matrix *powerMatrix(matrix *mat, int n) {
  if (mat->dim[0] != mat->dim[1]) {
    printf("The matrix must be squared!\n");
    exit(EXIT_FAILURE);
  }
  // M(n, n) ^ 0 = E(n)
  if (n == 0) {
    return matrixGetIndentityMatrix(mat->dim[0]);
  }
  // for result
  matrix *res = matrixGetIndentityMatrix(mat->dim[0]);
  // for temproray variable
  matrix *temp;
  for (int i = 0; i < n; ++i) {
    temp = res;
    res = matrixMultiply(res, mat);
    free(temp);
  }

  return res;
}

vector *powerVector(vector *vec, int n) {
  vector *res = vectorInit(vec->dim, vec->orient);
  for (int i = 0; i < vec->dim; ++i) {
    res->data[i] = powerT(vec->data[i], n);
  }

  return res;
}

double powerNum(double num, int n) {
  double res = 1.0;
  for (int i = 0; i < n; ++i) {
    res *= num;
  }
  return res;
}

int getInversionNumber(int len, int *arr) {
  int inversionNumber = 0;
  for (int i = 0; i < len - 1; ++i) {
    for (int j = i; j < len; ++j) {
      if (arr[i] > arr[j])
        ++inversionNumber;
    }
  }
  return inversionNumber;
}

matrix *solveLinearFunctions(matrix *argM, matrix *valueV) {
  // use x = A^-1 b
  return matrixMultiply(matrixInverse(argM), valueV);
}

matrix *vectorToMatrix(vector *vec) {
  switch (vec->orient) {
  case 'r':
    return matrixGetMatrixByArray(1, vec->dim, vec->data);
  case 'c':
    return matrixGetMatrixByArray(vec->dim, 1, vec->data);
  default:
    printf("ERROR!");
    exit(EXIT_FAILURE);
  }
}

vector *matrixToVector(matrix *mat) {
  if (!equalsT(mat->dim[0], 1) && !equalsT(mat->dim[1], 1)) {
    printf("The dimensions are not matched!\n");
    exit(EXIT_FAILURE);
  }
  if (equalsT(mat->dim[0], 1)) {
    return vectorGetVectorByArray(mat->dim[1], 'r', mat->data);
  } else if (equalsT(mat->dim[1], 1)) {
    return vectorGetVectorByArray(mat->dim[0], 'c', mat->data);
  } else {
    printf("ERROR!\n");
    exit(EXIT_FAILURE);
  }
}
