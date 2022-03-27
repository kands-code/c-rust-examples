#include "linalgs.h"
#include <stdio.h>

int main() {
  Matrix *m = InitMatrixByInput();
  LUDR *res = MatLUD(m);
  PrintMatrix(res->mats[0]);
  PrintMatrix(res->mats[1]);

  PrintMatrix(SolveLinearEqs(m, InitMatrixByInput()));

  return 0;
}
