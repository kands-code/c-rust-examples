#include "LinkedList.h"
#include "utils.h"
#include <stdio.h>

int main(void) {
  ElemType elems[5] = {1, 3, 5, 7, 9};
  LinkedList *ll = InitLinkedListFromArray(5, elems);
  PrintLinkedList(ll);
  reversedLinkedList(ll);
  PrintLinkedList(ll);

  return 0;
}