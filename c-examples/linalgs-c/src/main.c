#include "linalgs.h"

int main() {
  Matrix *m = InitMatrixByInput();
  PrintMatrix(MatPow(m, 3));
  PrintMatrix(MatPow(m, 0));

  return 0;
}
