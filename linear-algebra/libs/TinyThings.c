#include "TinyThings.h"

// --- some necessary includes

#include "../LinearAlgebra.h"
#include <stdio.h>
#include <stdlib.h>

// --- some function implementations

double absTT(double num) {
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

double powerNum(double num, int n) {
  double res = 1.0;
  for (int i = 0; i < n; ++i) {
    res *= num;
  }
  return res;
}
