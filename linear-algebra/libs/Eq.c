#include "Eq.h"

// --- necessary includes

#include "../LinearAlgebra.h"
#include "TinyThings.h"
#include <stdbool.h>
#include <stdlib.h>

// --- some definitions

double eps = 1e-6;

// --- some function implementations

bool equalsToZero(double num) {
  // use abs and eps instead of "== 0"
  if (absTT(num) < eps)
    return true;
  return false;
}

bool equalsForNum(double n1, double n2) { return equalsToZero(n1 - n2); }

bool equalsForString(char *s1, char *s2) {
  int i = 0;
  for (i = 0; *(s1 + i) != '\0' && *(s2 + i) != '\0'; ++i) {
    if (*(s1 + i) != *(s2 + i)) {
      return false;
    }
  }

  if (*(s1 + i) == '\0' && *(s2 + i) == '\0')
    return true;
  return false;
}

bool equalsForMatrix(matrix *m1, matrix *m2) {
  if (m1->dim[0] != m2->dim[0] || m1->dim[1] != m2->dim[1])
    return false;
  for (int i = 1; i < m1->dim[0] * m1->dim[1]; ++i) {
    if (m1->data[i] != m2->data[i])
      return false;
  }
  return true;
}
