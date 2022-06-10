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

char **strSplit(const char *str, char *delim, int *length) {
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

char *strTrim(const char *str) {
  if (NULL == str) {
    return NULL;
  } else if (strlen(str) == 0) {
    return "";
  }

  size_t strLen = strlen(str);
  size_t start = 0;
  while (start < strLen - 1 && isspace(str[start])) {
    start++;
  }
  size_t end = strLen - 1;
  while (end >= start && isspace(str[end])) {
    end--;
  }
  char *res = (char *)calloc(end - start + 2, sizeof(char));
  strncpy(res, str + start, end - start + 1);
  res[end - start + 1] = '\0';

  return res;
}