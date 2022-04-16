#include "linalgs.h"
#include <stdio.h>

int main() {
  Matrix *m1 = InitMatrixByInput();
  Matrix *m2 = InitMatrixByInput();

  PrintMatrix(MatMul(m1, m2));

  return 0;
}
