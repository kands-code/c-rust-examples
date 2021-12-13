#include "LinearAlgebra.h"
#include "libs/Eq.h"
#include "libs/TinyThings.h"
#include <stdio.h>

int main(void) {
  double a[] = {1, -1, -1, 2, -1, -3, 3, 2, 5};
  matrix *matA = matrixGetMatrixByArray(3, 3, a);
  // print the original matrix
  matrixPrint(matA);
  puts("============");
  // print the upright-triangle formed matrix
  matrixPrint(matrixToUprightTriangleForm(matA));
  puts("============");
  // print the inverse matrix
  matrixPrint(matrixInverse(matA));
  puts("============");
  // print the determinant of the matrix
  printf("%.3f\n", matrixDeterminant(matA));
  puts("============");

  return 0;
}
