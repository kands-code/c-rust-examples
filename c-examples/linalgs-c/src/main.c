#include <stdio.h>

#include "linalgs.h"

int main() {
  Matrix *m = InitMatrixByInput();

  PrintMatrix(MatInverse(m));

  DestroyMatrix(m);

  return 0;
}
