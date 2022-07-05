#include "linalgs.h"
#include <stdio.h>

int main() {
  Matrix *m = InitMatrixByInput();

  PrintMatrix(MatInverse(m));

  return 0;
}
