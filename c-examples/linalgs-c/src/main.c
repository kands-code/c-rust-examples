#include "linalgs.h"
#include <stdio.h>

int main() {
  Matrix *m = InitMatrixByInput();
  Matrix **res = MatLUD(m);
  PrintMatrix(res[0]);
  PrintMatrix(res[1]);

  PrintMatrix(MatMul(res[1], res[0]));

  return 0;
}
