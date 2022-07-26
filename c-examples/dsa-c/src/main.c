#include <collections/LinkedList.h>
#include <collections/utils.h>

int main(void) {
  ElemType elems[5] = {1, 3, 5, 7, 9};

  LinkedList *al = InitLinkedListFromArray(5, elems);
  PrintLinkedList(al);

  reversedLinkedList(al);
  PrintLinkedList(al);

  SetLinkedListElement(al, 12, 3);
  PrintLinkedList(al);

  InsertElementToLinkedList(al, 19, 3);
  PrintLinkedList(al);

  DestroyLinkedList(al);

  return 0;
}