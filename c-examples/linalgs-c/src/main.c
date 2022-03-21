#include "linalgs.h"
#include <stdio.h>

int main() {
  printf("Hello, World!\n");
  Matrix *m = InitMatrixByInput();

  Matrix **res = MatToUT(m);
  PrintMatrix(res[0]);
  PrintMatrix(res[1]);

  Matrix * v = InitMatrixByInput();
  PrintMatrix(SolveLinearEqs(m, v));

  return 0;
}
