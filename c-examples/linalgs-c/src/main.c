#include "linalgs.h"

int main() {
  PrintMatrix(MatKronecker(InitMatrixByInput(), InitMatrixByInput()));
  return 0;
}
