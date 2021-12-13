#include "LinearAlgebra.h"
#include "libs/Eq.h"
#include "libs/TinyThings.h"
#include <stdio.h>

int main(void) {
  double a[] = {2, -1, -1, 1,  2, 1, 1, -2, 1, 4,
                4, -6, 2,  -2, 4, 3, 6, -9, 7, 9};
  matrix *matA = matrixGetMatrixByArray(4, 5, a);

  matrixPrint(matA);

  puts("=============");

  matrixPrint(matrixToUprightTriangleForm(matA));

  return 0;
}
