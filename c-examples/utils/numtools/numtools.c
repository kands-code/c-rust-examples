#include "numtools.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h> // for debug
#include <stdlib.h>
#include <string.h>

bool isPrime(size_t n) {
  for (size_t i = 2; i * i <= n; ++i) {
    if (n % i == 0) {
      return false;
    }
  }
  return true;
}

char *factors(size_t lst) {
  // barrier, size_t > 0
  if (0 == lst) {
    return "(0)";
  } else if (1 == lst) {
    return "(1)";
  }

  size_t val = lst;
  int len = 0;
  char **exp = (char **)calloc(len, sizeof(char **));
  for (size_t i = 2; i < ((lst / 5) > 3 ? (lst / 5) : 3); ++i) {
    if (isPrime(val)) {
      char *tempStr = (char *)calloc(8, sizeof(char));
      sprintf(tempStr, "(%zu)", val);
      exp[len++] = tempStr;
      break;
    } else if (isPrime(i) && val % i == 0) {
      int times = 0;
      while (val % i == 0) {
        val /= i;
        times++;
      }
      char *tempStr = (char *)calloc(8, sizeof(char));
      if (times > 1) {
        sprintf(tempStr, "(%zu**%d)", i, times);
      } else {
        sprintf(tempStr, "(%zu)", i);
      }
      exp = (char **)realloc(exp, (len + 1) * sizeof(char *));
      exp[len++] = tempStr;
    } else if (val < 2) {
      break;
    }
  }
  // concat strings
  char *finalExp = (char *)calloc(len * 8 + 1, sizeof(char));
  for (int i = 0; i < len; ++i) {
    strncat(finalExp, exp[i], strlen(exp[i]));
  }
  // do free
  for (int i = 0; i < len; ++i) {
    free(exp[i]);
  }
  free(exp);
  return finalExp;
}