/// Linked List

/** ================
    Includes
 ================ */

#include "collections/LinkedList.h"
#include "collections/utils.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

/** ================
    Realization
 ================ */

/**
 * @func InitNode : get a node
 * @param value : value the node hold [ ElemType ]
 * @return      : a node
 */
Node *InitNode(ElemType value) {
  Node *node = calloc(1, sizeof(Node));
  node->val = value;
  node->next = NULL;
  return node;
}

/**
 * @func InitLinkedList : get an empty linked list
 * @return : empty linked list [ LinkedList * ]
 */
LinkedList *InitLinkedList(void) {
  LinkedList *linkedList = calloc(1, sizeof(LinkedList));
  linkedList->head = InitNode(0);
  linkedList->size = 0;
  return linkedList;
}

/**
 * @func InitLinkedListByHead : get an linked list by head insert method
 * @param len : the length of the linked list [ const size_t ]
 * @return    : initialized linked list       [ LinkedList * ]
 */
LinkedList *InitLinkedListByHead(const size_t len) {
  LinkedList *linkedList = InitLinkedList();
  Node *h = linkedList->head;
  for (size_t i = 0; i < len; ++i) {
    ElemType val = 0;
    scanf("%d", &val);
    Node *node = InitNode(val);
    node->next = h->next;
    h->next = node;
    linkedList->size++;
  }
  return linkedList;
}

/**
 * @func InitLinkedListByTail : get an linked list by head tail method
 * @param len : the length of the linked list [ const size_t ]
 * @return    : initialized linked list       [ LinkedList * ]
 */
LinkedList *InitLinkedListByTail(const size_t len) {
  LinkedList *linkedList = InitLinkedList();
  Node *t = linkedList->head;
  for (size_t i = 0; i < len; ++i) {
    ElemType val = 0;
    scanf("%d", &val);
    Node *node = InitNode(val);
    t->next = node;
    t = t->next;
    linkedList->size++;
  }
  return linkedList;
}

/**
 * @func InitLinkedListFromArray : get an linked list which has
 *                                 stored all the element in the array
 * @param len   : length of the array [ const size_t ]
 * @param elems : the array           [ ElemType *   ]
 * @return      : the linked list     [ LinkedList * ]
 */
LinkedList *InitLinkedListFromArray(const size_t len, ElemType elems[len]) {
  LinkedList *linkedList = InitLinkedList();
  Node *rear = linkedList->head;
  for (size_t i = 0; i < len; ++i) {
    rear->next = InitNode(elems[i]);
    linkedList->size += 1;
    rear = rear->next;
  }
  return linkedList;
}

/**
 * @func DestoryLinkedList : destory the linked list
 * @param linkedList : the linked list [ LinkedList * ]
 */
void DestoryLinkedList(LinkedList *linkedList) {
  Node *node = linkedList->head;
  while (node != NULL) {
    Node *temp = node->next;
    free(node);
    node = temp;
  }
  free(linkedList);
}

/**
 * @func GetLinkedListElement : get the element at a specific position
 * @param linkedList : the linked list [ const LinkedList * ]
 * @param position   : the position    [ const size_t       ]
 * @return           : the element     [ ElemType           ]
 * @descript         : function will crash when the position
 *                     is out of the boundary
 */
ElemType GetLinkedListElement(const LinkedList *linkedList,
                              const size_t position) {
  if (linkedList->size < position || position < 1) {
    fprintf(stderr, "Out of the boundary!");
    exit(1);
  }
  Node *h = linkedList->head;
  for (size_t i = 0; i < position; ++i) {
    h = h->next;
  }
  return h->val;
}

/**
 * @func SetLinkedListElement : set the value of a specific position
 * @param linkedList : the linked list [ LinkedList *   ]
 * @param value      : the value       [ const ElemType ]
 * @param position   : the position    [ const size_t   ]
 * @descript         : function will crash when the position
 *                     is out of the boundary
 */
void SetLinkedListElement(LinkedList *linkedList, const ElemType value,
                          const size_t position) {
  if (linkedList->size < position || position < 1) {
    fprintf(stderr, "Out of the boundary!");
    exit(1);
  }
  Node *h = linkedList->head;
  for (size_t i = 0; i < position; ++i) {
    h = h->next;
  }
  h->val = value;
}

/**
 * @func FindLinkedListElement : get the element at a specific position
 * @param linkedList : the linked list      [ LinkedList *   ]
 * @param elem       : value of the element [ const ElemType ]
 * @return           : the position         [ int            ]
 * @descript         : function will return -1 when the element
 *                     cannot find in the linked list
 */
int FindLinkedListElement(const LinkedList *linkedList, const ElemType elem) {
  if (linkedList->size < 1) {
    fprintf(stderr, "Empty Linked List!");
    return -1;
  }
  int pos = 0;
  Node *node = linkedList->head->next;
  while (node != NULL) {
    pos++;
    if (node->val == elem) {
      return pos;
    }
    node = node->next;
  }
  return -1;
}

/**
 * @func InsertElementToLinkedList : insert element to a specific position
 *                                   of the linked list
 * @param linkedList : the linked list                    [ LinkedList *   ]
 * @param value      : the value of element               [ const ElemType ]
 * @param position   : the position the element insert to [ const size_t   ]
 * @descript         : function will crash when the position
 *                     is out of the boundary
 */
void InsertElementToLinkedList(LinkedList *linkedList, const ElemType value,
                               const size_t position) {
  if (linkedList->size + 1 < position || position < 1) {
    fprintf(stderr, "Out of the boundary!");
    exit(1);
  }
  Node *h = linkedList->head;
  for (size_t i = 0; i < position - 1; ++i) {
    h = h->next;
  }
  Node *node = InitNode(value);
  node->next = h->next;
  h->next = node;
  linkedList->size++;
}

/**
 * @func RemoveElementFromLinkedList : remove the element at
 *                                     a specific position
 * @param linkedList : the linked list     [ LinkedList * ]
 * @param position   : the position        [ const size_t ]
 * @return           : the removed element [ ElemType     ]
 * @descript         : function will crash when the position
 *                     is out of the boundary
 */
ElemType RemoveElementFromLinkedList(LinkedList *linkedList,
                                     const size_t position) {
  if (linkedList->size < 1) {
    fprintf(stderr, "Empty Linked List!");
    exit(1);
  } else if (linkedList->size + 1 < position || position < 1) {
    fprintf(stderr, "Out of the boundary!");
    exit(1);
  }
  Node *h = linkedList->head;
  for (size_t i = 0; i < position - 1; ++i) {
    h = h->next;
  }
  Node *node = h->next;
  ElemType val = node->val;
  h->next = h->next->next;
  linkedList->size--;
  node->next = NULL;
  free(node);
  return val;
}

/**
 * @func PrintLinkedList : print elements in linked list
 * @param linkedList : the linked list [ LinkedList * ]
 */
void PrintLinkedList(LinkedList *linkedList) {
  Node *node = linkedList->head->next;
  printf("[");
  for (size_t i = 0; i < linkedList->size; ++i) {
    printf("%d, ", node->val);
    node = node->next;
  }
  printf("\b\b]\n");
}

/**
 * @func reverseLinkedList : reverse a linked list
 * @param linkedList : the linked list          [ const LinkedList * ]
 * @return           : the reversed linked list [ LinkedList *       ]
 */
LinkedList *reverseLinkedList(const LinkedList *linkedList) {
  LinkedList *revLinkedList = InitLinkedList();
  Node *h = revLinkedList->head;
  for (size_t i = 0; i < linkedList->size; ++i) {
    Node *node = InitNode(GetLinkedListElement(linkedList, i + 1));
    node->next = h->next;
    h->next = node;
    revLinkedList->size++;
  }
  return revLinkedList;
}

/**
 * @func reversedLinkedList : reverse original linked list
 * @param linkedList : the linked list [ LinkedList * ]
 */
void reversedLinkedList(LinkedList *linkedList) {
  if (linkedList->size < 1) {
    return;
  }
  Node *prev = linkedList->head->next;
  Node *curr = prev->next;
  prev->next = NULL;
  while (curr->next != NULL) {
    Node *next = curr->next;
    curr->next = prev;
    prev = curr;
    curr = next;
  }
  curr->next = prev;
  linkedList->head->next = curr;
}