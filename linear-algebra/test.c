#include "LinearAlgebra.h"
#include "libs/TinyThings.h"
#include <stdio.h>

int main(void) {

  double a[] = {1, 0, 0, 2};
  matrix *matA = matrixGetMatrixByArray(2, 2, a);

  printf("%.3f\n", powerTT(10.0, 3));
  matrixPrint(powerTT(matA, 4));

  double b[] = {-1, 1, 1, 1, 0, 2, 1, 1, -1};
  matrix *matB = matrixGetMatrixByArray(3, 3, b);
  printf("%.3f\n", matrixDeterminant(matB));

  return 0;
}
