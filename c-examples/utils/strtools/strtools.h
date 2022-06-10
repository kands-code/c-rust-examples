#pragma once

char *strSep(char **stringPtr, const char *delim);
char **strSplit(const char *str, char *delim, int *length);
char *strTrim(const char *str);