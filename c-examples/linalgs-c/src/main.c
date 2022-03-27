#include "linalgs.h"
#include <stdio.h>

int main() {
  Matrix *m = InitMatrixByInput();
  PrintMatrix(MatLUD(m)[0]);
  PrintMatrix(MatInverse(MatLUD(m)[1]));

  Matrix *b = InitMatrixByInput();

  PrintMatrix(SolveLinearEqs(m, b));

  return 0;
}
