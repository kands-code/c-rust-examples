#include <stdio.h>

#include "matrix-ext.h"
#include "matrix.h"

int main() {
  Matrix *m = InitMatrixByInput();

  PrintMatrix(MatInverse(m));

  DestroyMatrix(m);

  return 0;
}
