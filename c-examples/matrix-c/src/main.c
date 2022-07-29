#include <stdio.h>

#include "matrix-ext.h"
#include "matrix.h"

int main() {
  Matrix *A = InitMatrixByInput();
  Matrix *b = InitMatrixByInput();

  Matrix *jbres = JacobiLinearSolver(A, b, 300);

  PrintMatrix(jbres);

  // printf("%f\n", GetMatrixVal(A, 0, 0));

  DestroyMatrix(A);
  DestroyMatrix(b);
  DestroyMatrix(jbres);

  return 0;
}
