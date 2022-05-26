#include "strtools.h"
#include <stdlib.h>
#include <string.h>

char *strSep(char **stringPtr, const char *delim) {
  char *rv = *stringPtr;
  if (rv) {
    *stringPtr += strcspn(*stringPtr, delim);
    if (**stringPtr) {
      *(*stringPtr)++ = '\0';
    } else {
      *stringPtr = 0;
    }
  }
  return rv;
}

char **split(const char *str, char *delim, int *length) {
  char *s = strdup(str);
  char *token;
  int n = 0;
  char **strings = (char **)calloc(0, sizeof(char *));
  for (token = strSep(&s, delim); token != NULL; token = strSep(&s, delim)) {
    size_t len = strlen(token);
    char *tempStr = (char *)calloc(len, sizeof(char));
    strcpy(tempStr, token);
    strings = (char **)realloc(strings, (n + 1) * sizeof(char *));
    strings[n++] = tempStr;
  }
  (*length) = n;
  return strings;
}