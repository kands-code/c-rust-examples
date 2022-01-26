#include "src/linear-algebra.h"
#include <stdio.h>

int main(void) {
  double arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  Matrix *mat = InitMatrixFromArray(3, 3, 9, arr);
  PrintMatrix(mat);

  printf("%.2f\n", GetMatrixVal(mat, 1, 2));

  printf("Input: ");
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      double d;
      scanf("%lf", &d);
      SetMatrixVal(mat, i, j, d);
    }
  }

  PrintMatrix(mat);

  return 0;
}
