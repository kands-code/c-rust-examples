#include "ArrayList.h"
#include "utils.h"
#include <stdio.h>

int main(void) {
  ElemType elems[5] = {1, 3, 5, 7, 9};

  ArrayList *al = InitArrayListFromArray(5, elems);
  PrintArrayList(al);

  RemoveElementFromArrayList(al, 1);
  PrintArrayList(al);

  DestoryArrayList(al);

  return 0;
}